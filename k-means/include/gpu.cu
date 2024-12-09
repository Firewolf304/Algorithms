//
// Created by firewolf on 05.12.24.
//

#ifndef K_MEANS_GPU_CU
#define K_MEANS_GPU_CU

#include "libs.hpp"
#include "points/point.hxx"
namespace kmeans {
    class kmean_gpu;
     __global__ inline void updateCentroids(Point *points, int nPoints, int cluster, float *summX, float *summY, int *count) {
         extern __shared__ float sharedMemory[];
         float *localSumX = &sharedMemory[0];
         float *localSumY = &sharedMemory[blockDim.x];
         int *localCount = (int *)&sharedMemory[2 * blockDim.x];

         int tid = threadIdx.x + blockIdx.x * blockDim.x;
         int localIdx = threadIdx.x;

         // init local summm
         localSumX[localIdx] = 0;
         localSumY[localIdx] = 0;
         localCount[localIdx] = 0;

         // updates
         if (tid < nPoints) {
             Point p = points[tid];
             if (p.cluster == cluster) {
                 localSumX[localIdx] += p.x;
                 localSumY[localIdx] += p.y;
                 localCount[localIdx] += 1;
             }
         }
         __syncthreads();

         // Редуцируем
         for (int offset = blockDim.x / 2; offset > 0; offset /= 2) {
             if (localIdx < offset) {
                 // magic swap
                 localSumX[localIdx] += localSumX[localIdx + offset];
                 localSumY[localIdx] += localSumY[localIdx + offset];
                 localCount[localIdx] += localCount[localIdx + offset];
             }
             __syncthreads();
         }

         // update summs
         if (localIdx == 0) {
             atomicAdd(summX, localSumX[0]);
             atomicAdd(summY, localSumY[0]);
             atomicAdd(count, localCount[0]);
         }
    }
    __global__ inline void kernel_clusterPoints(Point * raw_points, Point * raw_centroids, int * changed, int nPoints, int k, int test = 0) {
        extern __shared__ Point sharedCentroids[];
        int tid = threadIdx.x + blockIdx.x * blockDim.x;
        if (threadIdx.x < k) {
            sharedCentroids[threadIdx.x] = raw_centroids[threadIdx.x];
        }

        __syncthreads();
        if(tid < nPoints) {
            Point &p = raw_points[tid];
            int nearestCluster = -1;
            float minDist = MAXFLOAT;
            for (int i = 0; i < k; ++i) {
                float dist = (p.x - sharedCentroids[i].x) * (p.x - sharedCentroids[i].x) +
                             (p.y - sharedCentroids[i].y) * (p.y - sharedCentroids[i].y);
                if (dist < minDist) {
                    minDist = dist;
                    nearestCluster = i;
                }
            }
            if (p.cluster != nearestCluster) {
                p.cluster = nearestCluster;
                atomicAdd(changed, 1);
            }
            if (test) {
                printf("tid=%d thread=%d block=%d dim=%d = (%f, %f) cluster=%d changed=%d\n", tid, threadIdx.x, blockIdx.x, blockDim.x, p.x, p.y, p.cluster, *changed);
            }
        }
    }

    using vars_test = std::variant<std::string, int, double, float>;
    using var_test = std::variant<vars_test, std::vector<vars_test>>;
    class kmean_gpu {
        thrust::device_vector<Point> points;
        thrust::device_vector<Point> centroids;
        int k = -1;
        bool test;
    public:
        kmean_gpu(const std::vector<Point> &points, bool test = false) :
                points(points.begin(), points.end()), test(test) {}
        __device__ __host__ double distance (Point & a, Point & b) {
            return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }
        __device__ __host__ double distance (Point a, Point b) {
            return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }
        __device__ __host__ double distance_sqrt (Point & a, Point & b) {
            return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }
        Point calculateCentroid(int cluster) {
            /*float sumX = 0, sumY = 0;
            int count = 0;
            thrust::host_vector<Point> hostCounts = this->points;
            for (auto point : hostCounts) {
                if (point.cluster == cluster) {
                    sumX += point.x;
                    sumY += point.y;
                    ++count;
                    if(this->test) {
                        printf("Included point: (x=%f, y=%f) from cluster %d in centroid calculation.\n", point.x,
                               point.y, cluster);
                    }
                }
            }
            if(this->test) {
                printf("Cluster %d: Total Sum (X=%f, Y=%f), Count=%d.\n", cluster, sumX, sumY, count);
            }
            return count > 0 ? Point(sumX / count, sumY / count) : Point(0, 0);*/
            int nPoints = this->points.size();
            float *d_sumX, *d_sumY;
            int *d_count;
            cudaMalloc(&d_sumX, sizeof(float));
            cudaMalloc(&d_sumY, sizeof(float));
            cudaMalloc(&d_count, sizeof(int));
            cudaMemset(d_sumX, 0, sizeof(float));
            cudaMemset(d_sumY, 0, sizeof(float));
            cudaMemset(d_count, 0, sizeof(int));

            int threadsPerBlock = 256;
            int blocks = (nPoints + threadsPerBlock - 1) / threadsPerBlock;
            size_t sharedMemorySize = 2 * threadsPerBlock * sizeof(float) + threadsPerBlock * sizeof(int);

            updateCentroids<<<blocks, threadsPerBlock, sharedMemorySize>>>(
                    thrust::raw_pointer_cast(this->points.data()),
                    nPoints,
                    cluster,
                    d_sumX,
                    d_sumY,
                    d_count
            );

            float h_sumX, h_sumY;
            int h_count;
            cudaMemcpy(&h_sumX, d_sumX, sizeof(float), cudaMemcpyDeviceToHost);
            cudaMemcpy(&h_sumY, d_sumY, sizeof(float), cudaMemcpyDeviceToHost);
            cudaMemcpy(&h_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

            cudaFree(d_sumX);
            cudaFree(d_sumY);
            cudaFree(d_count);

            if (this->test) {
                printf("Cluster %d: Total Sum (X=%f, Y=%f), Count=%d.\n", cluster, h_sumX, h_sumY, h_count);
            }

            return h_count > 0 ? Point(h_sumX / h_count, h_sumY / h_count) : Point(0, 0);
        }
        // Старт подготовленных центроидов
        void start(int k, std::vector<Point> & init_centroids, bool output = true) {
            this->k = k;
            this->centroids = thrust::device_vector<Point>(init_centroids.begin(), init_centroids.end());
            start(output);
        }
        thrust::device_vector<Point> init_centroids(int k) {
            this->k = k;
            thrust::host_vector<Point> p = this->points;
            std::vector<Point> cent;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, this->points.size());
            for (int i = 0; i < k; ++i) {
                int idx = distrib(gen);
                cent.push_back(p[idx]);
            }
            p.clear();
            return {cent.begin(), cent.end()};
        }
        void start(bool output = true) {
            if(this->centroids.empty()) {
                throw std::runtime_error("Centroids are not initialized");
            }
            int nPoints = this->points.size();
            thrust::device_vector<int> clusterCounts(k);

            std::shared_ptr<int> changed = std::make_shared<int>(1);
            int count = 0;
            auto start = std::chrono::high_resolution_clock::now();

            int threadsPerBlock = 256;
            int blocks = (nPoints + threadsPerBlock - 1) / threadsPerBlock;

            while (*changed > 0) {
                if(this->test) fmt::println("=========== Iter {} ===========", count);
                *changed  = 0;
                // Не нарушаем warp-блоки


                kernel_clusterPoints<<<blocks, threadsPerBlock, this->k * sizeof(Point)>>>(
                        thrust::raw_pointer_cast((this->points.data())),
                        thrust::raw_pointer_cast((this->centroids.data())),
                        thrust::raw_pointer_cast(changed.get()),
                        nPoints,
                        this->k,
                        this->test
                        );

                thrust::fill(clusterCounts.begin(), clusterCounts.end(), 0);

                if(this->test) fmt::println("Centroids:");
                #pragma omp parallel for
                for (int i = 0; i < k; ++i) {
                    centroids[i] = calculateCentroid(i);
                }
                /*fmt::println("Centroids:", count);
                updateCentroids<<<blocks, threadsPerBlock>>>(
                        thrust::raw_pointer_cast(this->points.data()),
                        thrust::raw_pointer_cast(this->centroids.data()),
                        thrust::raw_pointer_cast(clusterCounts.data()),
                        nPoints, k
                );
                std::vector<int> hostCounts(k);
                thrust::copy(clusterCounts.begin(), clusterCounts.end(), hostCounts.begin());

                thrust::host_vector<Point> hostCentroids = this->centroids;
                for (int i = 0; i < k; ++i) {
                    if (hostCounts[i] > 0) {
                        hostCentroids[i].x /= hostCounts[i];
                        hostCentroids[i].y /= hostCounts[i];
                    }
                }
                this->centroids = hostCentroids;*/
                count++;
            }
            if(output) {
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = end - start;
                std::cout << "Execution time: " << duration / std::chrono::milliseconds(1) << " ms" << std::endl;
            }
        }

        void output() {
            thrust::host_vector<Point> hostPoints = this->points;
            for(auto point : hostPoints) {
                fmt::print("({},{}) -> {}\n", point.x, point.y, point.cluster);
            }
        }
        void output_sort() {
            thrust::host_vector<Point> hostPoints = this->points;
            std::map<int, std::vector<Point>> mapper{};
            for(auto &point : hostPoints) {
                mapper[point.cluster].push_back(point);

            }
            for(auto cluster : mapper) {
                fmt::println("============= {} =============", cluster.first);
                for(auto & point : cluster.second) {
                    fmt::println("({} {}) -> {}", point.x, point.y, point.cluster);
                }
            }
        }

        void output_sort_file() {
            thrust::host_vector<Point> hostPoints = this->points;
            std::map<int, std::vector<Point>> mapper{};
            for(auto &point : hostPoints) {
                mapper[point.cluster].push_back(point);
            }
            std::ofstream file("output_gpu.txt", std::ios::out | std::ios::trunc);
            for(auto cluster : mapper) {
                //file << "============= " << cluster.first << " =============\n";
                for(auto & point : cluster.second) {
                    file << point.x << " " << point.y << " " << point.cluster << std::endl;
                }
            }
            file.close();
        }
        double calculateCopheneticCorrelation() {
            std::vector<double> dataDistances, clusterDistances;
            thrust::host_vector<Point> centroid = this->points;
            thrust::host_vector<Point> centroiders = this->centroids;
            for (size_t i = 0; i < centroid.size(); ++i) {
                for (size_t j = i + 1; j < centroid.size(); ++j) {
                    dataDistances.push_back(distance_sqrt(centroid[i], centroid[j]));
                }
            }

            for (size_t i = 0; i < centroid.size(); ++i) {
                for (size_t j = i + 1; j < centroid.size(); ++j) {
                    if (centroid[i].cluster == centroid[j].cluster) {
                        clusterDistances.push_back(0.0);
                    } else {
                        clusterDistances.push_back(distance_sqrt(centroiders[centroid[i].cluster], centroiders[centroid[j].cluster]));
                    }
                }
            }

            return pearsonCorrelation(dataDistances, clusterDistances);
        }

        double pearsonCorrelation(const std::vector<double>& x, const std::vector<double>& y) {
            double meanX = std::accumulate(x.begin(), x.end(), 0.0) / x.size();
            double meanY = std::accumulate(y.begin(), y.end(), 0.0) / y.size();

            double numerator = 0.0, denomX = 0.0, denomY = 0.0;

            for (size_t i = 0; i < x.size(); ++i) {
                double diffX = x[i] - meanX;
                double diffY = y[i] - meanY;
                numerator += diffX * diffY;
                denomX += diffX * diffX;
                denomY += diffY * diffY;
            }

            return numerator / std::sqrt(denomX * denomY);
        }
        double estimateCopheneticError(int numIterations) {
            std::vector<double> correlations;
            for (int i = 0; i < numIterations; ++i) {

                this->centroids = init_centroids(this->k);
                start(false);

                correlations.push_back(calculateCopheneticCorrelation());
            }
            double mean = std::accumulate(correlations.begin(), correlations.end(), 0.0) / correlations.size();
            double variance = 0.0;
            for (double corr : correlations) {
                variance += (corr - mean) * (corr - mean);
            }
            variance /= correlations.size();
            return std::sqrt(variance);
        }
    };
}

#endif //K_MEANS_GPU_CU
