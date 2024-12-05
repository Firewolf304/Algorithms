//
// Created by firewolf on 05.12.24.
//

#ifndef K_MEANS_GPU_CU
#define K_MEANS_GPU_CU

#include "libs.hpp"
#include "points/point.hxx"
namespace kmeans {
    class kmean_gpu;
     __global__ inline void updateCentroids(Point* raw_points, Point* raw_centroids, int* clusterCounts, int nPoints, int k) {
        int tid = threadIdx.x + blockIdx.x * blockDim.x;

        if (tid < nPoints) {
            Point& p = raw_points[tid];
            atomicAdd(&(raw_centroids[p.cluster].x), p.x);
            atomicAdd(&(raw_centroids[p.cluster].y), p.y);
            atomicAdd(&(clusterCounts[p.cluster]), 1);
        }
    }
    __global__ inline void kernel_clusterPoints(Point * raw_points, Point * raw_centroids, int * changed, int nPoints, int k) {
        extern __shared__ Point sharedCentroids[];
        int tid = threadIdx.x + blockIdx.x * blockDim.x;
        if (threadIdx.x < k) {
            sharedCentroids[threadIdx.x] = raw_centroids[threadIdx.x];
        }
        __syncthreads();

        if(tid < nPoints) {
            Point& p = raw_points[tid];
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

        // Старт подготовленных центроидов
        void start(int k, std::vector<Point> & init_centroids) {
            this->k = k;
            this->centroids = thrust::device_vector<Point>(init_centroids.begin(), init_centroids.end());
            start();
        }

        void start() {
            if(this->centroids.empty()) {
                throw std::runtime_error("Centroids are not initialized");
            }
            int nPoints = this->points.size();
            thrust::device_vector<int> clusterCounts(k);

            std::shared_ptr<int> changed;
            *changed = 1;
            while (*changed > 0) {
                *changed  = 0;
                // Не нарушаем warp-блоки
                int threadsPerBlock = 256;
                int blocks = (nPoints + threadsPerBlock - 1) / threadsPerBlock;
                kernel_clusterPoints<<<blocks, threadsPerBlock, k * sizeof(Point)>>>(
                        thrust::raw_pointer_cast((this->points.data())),
                        thrust::raw_pointer_cast((this->centroids.data())),
                        thrust::raw_pointer_cast(changed.get()),
                        nPoints,
                        this->k
                        );

                thrust::fill(clusterCounts.begin(), clusterCounts.end(), 0);
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
                this->centroids = hostCentroids;

            }
        }

        void output() {
            thrust::host_vector<Point> hostPoints = this->points;
            for(auto point : hostPoints) {
                fmt::print("({},{}) -> {}\n", point.x, point.y, point.cluster);
            }
        }

        /*
         * Test values:
         *      distance - vector<double>
         */
        std::map<std::string, var_test> get_tests() {
            return {
                    {
                            "distance",
                            std::vector<vars_test>{
                                    distance( {0,0}, {1,1}),
                                    distance( {1,1}, {2,2}),
                                    distance( {-1,-1}, {2,2})
                            },
                    },
            };
        }
    };
}

#endif //K_MEANS_GPU_CU
