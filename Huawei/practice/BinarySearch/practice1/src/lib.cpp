#include "../include/lib.hpp"
#include <string>
#include <format>

std::string firewolf::hello::say_hello(const std::string& name) {
    return std::format("Hello, {}!", name);
}