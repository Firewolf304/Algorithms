#include <iostream>
#include "astar_algos.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<std::vector<int>> way = {{0,0,0,0,0}, {0,0,0,0,0}, {1,1,1,1,0}, {1,0,0,0,0}, {0,0,0,0,0} };
    astar finder({0,0}, {0,4}, way);
    auto f = finder.find_way();

    for(auto i : f) {
        way[std::get<1>(i->position)][std::get<0>(i->position)] = 2;
    }
    for(int y = 0; y < way.size(); y++) {
        for(int x = 0; x < way[y].size(); x++) {
            fmt::print("{}", way[y][x]);
        }
        fmt::print("\n");
    }
    return 0;
}
