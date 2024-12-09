#include "../include/local.hpp"


auto generate_points = [](int count) {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<Point> points;
    std::ofstream file("points.txt", std::ios::out | std::ios::trunc);
    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(rand() % 10000);
        float y = static_cast<float>(rand() % 10000);
        auto point = Point{x, y};
        points.emplace_back( point );
        file << point.x << " " << point.y<< std::endl;
    }
    file.close();
    return points;
};

auto read_file = [] (const std::string & filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return points;
    }
    std::string line;
    while (std::getline(file, line)) {
        double x, y;
        std::istringstream iss(line);
        if (iss >> x >> y) {
            points.emplace_back(x, y);
        } else {
            std::cerr << "Ошибка при чтении строки: " << line << std::endl;
        }
    }
    file.close();
    return points;
};

int main() {

    /*std::vector<Point> points = {
            {1.0, 2.0}, {1.2, 2.1}, {0.9, 1.8}, {1.1, 2.2},  // Cluster 1
            {6.0, 8.0}, {5.8, 7.9}, {6.2, 8.1}, {5.9, 8.2},  // Cluster 2
            {10.0, 10.0}, {10.2, 10.3}, {9.8, 9.7}, {10.1, 10.1},  // Cluster 3
            {15.0, 2.0}, {14.8, 2.1}, {15.2, 1.9}, {15.1, 2.2},  // Cluster 4
            {20.0, 20.0}, {20.2, 20.3}, {19.9, 19.8}, {20.1, 20.1}  // Cluster 5
    };*/
    //auto points = generate_points(count);
    auto points = read_file("points.txt");
    auto centroids = read_file("centroids.txt");
    int count = points.size();
    int k = centroids.size();
    bool tests = true;
    kmeans::kmean_cpu cpu {points};
    kmeans::kmean_gpu gpu {points};
    //cpu.init_centroids(k);



    /*std::ofstream file("centroids.txt", std::ios::out | std::ios::trunc);
    for (auto i = 0; i < centroids.size(); i++) {
        file << "(" << centroids[i].x << " " << centroids[i].y << ") -> " << i << std::endl;
    }
    file.close();*/
    /*std::cout <<  ("+============ Centroids ============+\n");
    for (auto i = 0; i < centroids.size(); i++) {
        std::printf("(%f,%f) -> %d\n", centroids[i].x, centroids[i].y, i);
    }*/
    std::cout <<  ("+============ CPU ============+\n");

    cpu.start(k, centroids);
    cpu.output_sort_file();
    if(tests) {
        std::cout << ("TESTS:\n");
        std::cout << std::fixed << std::setprecision(20) << "Cophenetic correlation="
                  << cpu.calculateCopheneticCorrelation() << std::endl;
        std::cout << std::fixed << std::setprecision(20) << "Cophenetic error=" << cpu.estimateCopheneticError(30)
                  << std::endl;
    }


    std::cout << ("+============ GPU ============+\n");

    gpu.start(k, centroids);
    gpu.output_sort_file();
    //gpu.output_sort();
    if(tests) {
        std::cout << ("TESTS:\n");
        std::cout << std::fixed << std::setprecision(20) << "Cophenetic correlation="
                  << gpu.calculateCopheneticCorrelation() << std::endl;
        std::cout << std::fixed << std::setprecision(20) << "Cophenetic error=" << gpu.estimateCopheneticError(30)
                  << std::endl;
    }


    return 0;
}
