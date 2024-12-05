//
// Created by firewolf on 03.12.24.
//

#ifndef K_MEANS_CPU_HXX
#define K_MEANS_CPU_HXX

#include "libs.hpp"
#include "points/point.hxx"
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
        float distance (Point & a, Point & b) {
            return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }
        float distance (Point a, Point b) {
            return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }
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
                }
            }
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

        void start(std::vector<Point> & init_centroids) {
            this->centroids = init_centroids;
            start();
        }

        void start() {
            if(this->centroids.empty()) {
                throw std::runtime_error("Centroids are not initialized");
            }
            bool changed = true;
            while (changed) {
                changed = false;

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
                        changed = true;
                    }
                }


                for (int i = 0; i < k; ++i) { // update centroids
                    centroids[i] = calculateCentroid(i);
                }
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

        /*
         * Test values:
         *      distance - vector<float>
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

#endif //K_MEANS_CPU_HXX
