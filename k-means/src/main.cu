#include "../include/local.hpp"

int main() {
    fmt::println("Hello, world!");
    kmeans::kmean_cpu cpu{{
                                  {1.0, 2.0}, {1.5, 1.8}, {5.0, 8.0},
                                  {8.0, 8.0}, {1.0, 0.6}, {9.0, 11.0},
                                  {8.0, 2.0}, {10.0, 2.0}, {9.0, 3.0}
                          }};
    cpu.start(3);
    cpu.output();


    return 0;
}