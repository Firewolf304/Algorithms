//
// Created by firewolf on 03.12.24.
//

#ifndef K_MEANS_CPU_HXX
#define K_MEANS_CPU_HXX
#include "libs.hpp"
#include "points/point.hxx"
#include <omp.h>
namespace kmeans {
    using vars_test = std::variant<std::string, int, double, float>;
    using var_test = std::variant<vars_test, std::vector<vars_test>>;
    class kmean_cpu {
        std::vector<Point> centroid;
        std::vector<Point> centroids;
        int k = -1;
        bool test;
    public:
        kmean_cpu(const std::vector<Point> &centroid, bool test = false) : centroid(centroid), test(test) {}
        float distance_sqrt (Point & a, Point & b) {
            return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }
        Point calculateCentroid(int cluster) {
            float sumX = 0, sumY = 0;
            int count = 0;

            for (auto point : this->centroid) {
                if (point.cluster == cluster) {
                    sumX += point.x;
                    sumY += point.y;
                    ++count;
                    if(this->test) printf("Included point: (x=%f, y=%f) from cluster %d in centroid calculation.\n", point.x, point.y, cluster);
                }
            }
            if(this->test) printf("Cluster %d: Total Sum (X=%f, Y=%f), Count=%d.\n", cluster, sumX, sumY, count);
            return count > 0 ? Point(sumX / count, sumY / count) : Point(0, 0);
        }
        std::vector<Point> & init_centroids(int k) {
            this->k = k;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, this->centroid.size());
            for (int i = 0; i < k; ++i) {
                int idx = distrib(gen);
                this->centroids.push_back(this->centroid[idx]);
            }
            return this->centroids;
        }

        void start(int k, std::vector<Point> & init_centroids, bool output = true) {
            this->k = k;
            this->centroids = init_centroids;
            start(output);
         }

        void start(bool output = true) {
            if(this->centroids.empty()) {
                throw std::runtime_error("Centroids are not initialized");
            }
            int count = 0;
            int changed = 1;
            auto start = std::chrono::high_resolution_clock::now();
            while (changed > 0) {
                changed = 0;
                if(this->test) fmt::println("Iter {}", count);
                for (auto &point : centroid) {

                    int nearestCluster = -1;
                    float minDist = std::numeric_limits<float>::max();

                    for (int i = 0; i < k; ++i) {
                        float dist = distance_sqrt(point, centroids[i]);
                        if (dist < minDist) {
                            minDist = dist;
                            nearestCluster = i;
                        }
                    }

                    if (point.cluster != nearestCluster) {
                        point.cluster = nearestCluster;
                        changed++;
                    }
                    if(this->test) printf("(%f, %f) cluster=%d changed=%d\n", point.x, point.y, point.cluster, changed);
                }

                if(this->test) fmt::println("Centroids:");
                for (int i = 0; i < k; ++i) { // update centroids
                    centroids[i] = calculateCentroid(i);
                }
                count++;
            }
            if(output) {
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = end - start;
                std::cout << "Execution time: " << duration / std::chrono::milliseconds(1) << " ms" << std::endl;
            }
        }

        void output() {
            for(auto &point : this->centroid) {
                fmt::println("({},{}) -> {}", point.x, point.y, point.cluster);
            }
        }

        void output_sort() {
            std::map<int, std::vector<Point>> mapper{};
            for(auto &point : this->centroid) {
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
            std::map<int, std::vector<Point>> mapper{};
            for(auto &point : this->centroid) {
                mapper[point.cluster].push_back(point);
            }
            std::ofstream file("output_cpu.txt", std::ios::out | std::ios::trunc);
            for(auto cluster : mapper) {
                //file << "============= " << cluster.first << " =============\n";
                //fmt::println("============= {} =============", cluster.first);
                for(auto & point : cluster.second) {
                    file << point.x << " " << point.y << " " << point.cluster << std::endl;
                    //fmt::println("({} {}) -> {}", point.x, point.y, point.cluster);
                }
            }
            file.close();
        }

        double calculateCopheneticCorrelation() {
            std::vector<double> dataDistances, clusterDistances;

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
                        clusterDistances.push_back(distance_sqrt(centroids[centroid[i].cluster], centroids[centroid[j].cluster]));
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

#endif //K_MEANS_CPU_HXX
