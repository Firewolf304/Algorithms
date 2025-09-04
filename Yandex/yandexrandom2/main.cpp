#include <iostream>
#include <unordered_map>
#include <ranges>
#include <algorithm>
#include <vector>

auto splitLine = [](std::string & line) -> std::pair<unsigned long long, std::string> {
    size_t pos = line.find(' ');
    if(pos != std::string::npos) {
        auto dd = line.substr(0, pos);
        auto N = std::stoull( dd.c_str() );
        std::string token = line.substr(pos + 1);
        return std::make_pair(N, token);
    }
    return {};
};

int main() {
    int reit, count;
    std::cin >> reit >> count;
    std::unordered_map<unsigned long long, std::string> mapper;
    std::unordered_map<std::string, unsigned long long> users;
    std::unordered_map<std::string, unsigned long long> usersUsingPeerSecond;
    std::unordered_map<std::string, unsigned long long> usersDelay;
    std::ranges::for_each(std::views::iota(0,count), [&mapper, &reit, &users, &usersDelay, &usersUsingPeerSecond](int i) {
        std::string line;
        std::getline(std::cin >> std::ws, line);
        auto data = splitLine(line);
        double long  second = data.first / 1000.0;
        if(users.contains(data.second)) {
            if(users[data.second] == (int)second) {
                usersUsingPeerSecond[data.second] += 1;
                if(reit >= usersUsingPeerSecond[data.second]) {
                    mapper.insert(data);
                }
            } else {
                users[data.second] = (int)second;
                usersUsingPeerSecond[data.second] = 1;
                mapper.insert(data);
            }
        } else {
            mapper.insert(data);
            usersDelay[data.second] = 0;
            usersUsingPeerSecond[data.second] += 1;
        }
        users[data.second] = second;
        /*unsigned long long delTime ;
        if(users.contains(data.second))
            delTime = (data.first - users[data.second]);
        else
            delTime = -1;
        float get = (usersDelay[data.second] + delTime)  ;
        if(!users.contains(data.second) || reit <= delTime || reit <= get ) {
            mapper.insert(data);
            usersDelay[data.second] = 0;
        } else {
            usersDelay[data.second] += delTime;
        }
        users[data.second] = data.first;*/
    });
    std::vector<std::pair<unsigned long long, std::string>> vec(mapper.begin(), mapper.end());
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    return 0;
}
