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
        std::vector<Point> centroid { };
        bool test;
    public:
        kmean_cpu(const std::vector<Point> &centroid, bool test = false) : centroid(centroid), test(test) {}
        double distance (Point & a, Point & b) {
            return a.distance(b);
        }
        double distance (Point a, Point b) {
            return a.distance(b);
        }
        double distance_sqrt (Point & a, Point & b) {
            return std::sqrt((a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) + (a.get_y() - b.get_y()) * (a.get_y() - b.get_y()));
        }
        Point calculateCentroid(int cluster) {
            double sumX = 0, sumY = 0;
            int count = 0;

            for (auto point : this->centroid) {
                if (point.cluster == cluster) {
                    sumX += point.get_x();
                    sumY += point.get_y();
                    ++count;
                }
            }
            return count > 0 ? Point(sumX / count, sumY / count) : Point(0, 0);
        }

        void start(int k) {
            std::vector<Point> centroids;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, this->centroid.size());

            // Инициализация случайных центроидов
            for (int i = 0; i < k; ++i) {
                int idx = distrib(gen);
                centroids.push_back(this->centroid[idx]);
            }

            bool changed = true;
            while (changed) {
                changed = false;

                // Присвоение точек ближайшему центроиду
                for (auto &point : centroid) {
                    int nearestCluster = -1;
                    double minDist = std::numeric_limits<double>::max();

                    for (int i = 0; i < k; ++i) {
                        double dist = distance_sqrt(point, centroids[i]);
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

                // Обновление центроидов
                for (int i = 0; i < k; ++i) {
                    centroids[i] = calculateCentroid(i);
                }
            }
        }

        void output() {
            for(auto &point : this->centroid) {
                fmt::println("({},{}) -> {}", point.get_x(), point.get_y(), point.cluster);
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

#endif //K_MEANS_CPU_HXX
