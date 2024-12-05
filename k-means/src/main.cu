#include "../include/local.hpp"

int main() {
    int k = 5;
    std::vector<Point> points = {
            {1.0, 2.0}, {1.2, 2.1}, {0.9, 1.8}, {1.1, 2.2},  // Cluster 1
            {6.0, 8.0}, {5.8, 7.9}, {6.2, 8.1}, {5.9, 8.2},  // Cluster 2
            {10.0, 10.0}, {10.2, 10.3}, {9.8, 9.7}, {10.1, 10.1},  // Cluster 3
            {15.0, 2.0}, {14.8, 2.1}, {15.2, 1.9}, {15.1, 2.2},  // Cluster 4
            {20.0, 20.0}, {20.2, 20.3}, {19.9, 19.8}, {20.1, 20.1}  // Cluster 5
    };
    kmeans::kmean_cpu cpu {points};
    kmeans::kmean_gpu gpu {points};
    auto centroids = cpu.init_centroids(k);
    std::cout <<  ("+============ CPU ============+\n");
    cpu.start(centroids);
    cpu.output_sort();
    std::cout << ("+============ GPU ============+");
    gpu.start(k, centroids);
    gpu.output();
    return 0;
}
