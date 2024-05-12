//
// Created by firewolf304 on 12.05.24.
//
#include <iostream>
#include <memory>
#include <vector>
#include <fmt/core.h>
#include <algorithm>

#ifndef ASTAR_ASTAR_ALGOS_HPP
#define ASTAR_ASTAR_ALGOS_HPP
class astar {
protected:
    class Node{
    public:
        Node(std::tuple<int, int> const & position, std::shared_ptr<Node> parent = nullptr) : position(position), parent(parent) {

        }
        std::tuple<int,int> position = {};
        double g = 0;
        double h = 0;
        double f = 0;
        std::shared_ptr<Node> parent = nullptr;
        bool operator==(Node other) {
            return this->position == other.position;
        }
        bool operator<(Node other) {
            return this->position < other.position;
        }
    };
    std::vector<std::vector<int>> grid = {};
    std::tuple<int, int> start = {};
    std::tuple<int, int> end = {};

    std::vector<std::shared_ptr<Node>> build_path(std::shared_ptr<Node> current) {
        std::vector<std::shared_ptr<Node>> path;
        while(current != nullptr) {
            path.push_back(current);
            current = current->parent;
        }
        return path;
    }

public:
    astar(std::tuple<int, int> const & start, std::tuple<int, int> const & end, std::vector<std::vector<int>> const & grid) : grid(grid), start(start), end(end) {}

    std::vector<std::shared_ptr<Node>> find_way() {
        Node a(start, nullptr);
        Node b(end, nullptr);
        std::vector<std::shared_ptr<Node>> reachable = { std::make_shared<Node>(a) };
        std::vector<std::shared_ptr<Node>> explored;
        while(!reachable.empty()) {
            auto current = *(--reachable.end());
            reachable.pop_back();
            fmt::print("Current: ({},{})\n", std::get<0>(current->position), std::get<1>(current->position));
            if(*current == b){
                return build_path(current);
            }
            explored.push_back(current);
            fmt::print("Check neighbors:");
            std::vector<int> range(2);
            for(int y = -1; y < 2; y++) {
                for(int x = -1; x < 2; x++) {
                    if((x == 0 && y == 0) || x == y) continue;
                    std::tuple<int, int> neighbor_position = {std::get<0>(current->position) + x, std::get<1>(current->position) + y};
                    if((0 <= std::get<0>(neighbor_position) && std::get<0>(neighbor_position) < this->grid[std::get<1>(neighbor_position)].size()) && (0 <= std::get<1>(neighbor_position) && std::get<1>(neighbor_position) < this->grid.size())) {
                        if(this->grid[std::get<1>(neighbor_position)].empty()) continue;
                        if(this->grid[std::get<1>(neighbor_position)][std::get<0>(neighbor_position)] == 1) continue;

                        auto neighbor_node = Node(neighbor_position, current);

                        if(std::find_if(explored.begin(), explored.end(),
                        [&neighbor_node](auto it1) -> bool {
                                return *it1 == neighbor_node;
                            }) != explored.end()
                        ) continue;

                        fmt::print(" Neighbor ({},{})={}", std::get<0>(neighbor_position), std::get<1>(neighbor_position), this->grid[std::get<1>(neighbor_position)][std::get<0>(neighbor_position)]);
                        neighbor_node.g = current->g + 1;
                        neighbor_node.h = ((std::get<0>(neighbor_position) - std::get<0>(b.position)^2) + (std::get<1>(neighbor_position) - std::get<1>(b.position)^2));  // Euclidean distance as heuristic
                        neighbor_node.f = neighbor_node.g + neighbor_node.h;
                        if(std::find_if(reachable.begin(), reachable.end(),
                                        [&neighbor_node](auto it1) -> bool {
                                            return *it1 == neighbor_node;
                                        }) == reachable.end()) {
                            reachable.push_back(std::make_shared<Node>(neighbor_node));
                        } else {
                            for(auto reachable_node : reachable) {
                                if(*reachable_node == neighbor_node && reachable_node->f > neighbor_node.f) {
                                    reachable_node = std::make_shared<Node>(neighbor_node);
                                    std::sort(reachable.begin(), reachable.end());
                                }
                            }
                        }
                    }
                }
            }
            fmt::print("\n");
        }
        return {};
    }
};
#endif //ASTAR_ASTAR_ALGOS_HPP
