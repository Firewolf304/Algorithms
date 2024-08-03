#include <iostream>
#include <toml++/toml.hpp>
#include <fstream>
#include <sstream>
#include <print>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string config = "config.toml";
    std::ifstream file(config);
    std::stringstream buffer;
    buffer << file.rdbuf();
    toml::table tbl = toml::parse(buffer.str());
    auto value = tbl["Server"]["hello"];
    std::cout << value << std::endl;
    return 0;
}
