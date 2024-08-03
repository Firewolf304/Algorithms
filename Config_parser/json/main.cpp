#include <iostream>
#include <nlohmann/json.hpp>
#include <print>
#include <fstream>

class object;
// "SERVER" / "CONFIG" / "HELLO" / context;
class json_config_parser {
    std::string path_to_file;

public:
    nlohmann::json config;
    json_config_parser() = default;
    json_config_parser(const std::string && path_to_file) : path_to_file(path_to_file) {init();}
    json_config_parser(std::string & path_to_file) : path_to_file(path_to_file) {init();}
    json_config_parser(json_config_parser & parser) = default;
    void init() {
        std::ifstream stream(path_to_file);
        std::stringstream buffer;
        buffer << stream.rdbuf();
        this->config = nlohmann::json::parse(buffer.str());
        buffer.clear();
        stream.close();
    }
    class object {
        json_config_parser & parser;
    public:
        nlohmann::json currect_object;
        object(json_config_parser& parser) : parser(parser), currect_object(parser.config) { }
        object & operator/(const std::string & path) {
            if(currect_object.contains(path)) {
                currect_object = currect_object[path];
            }
            return *this;
        }
        object & operator/(std::string & path) {
            if(currect_object.contains(path)) {
                currect_object = currect_object[path];
            }
            return *this;
        }
    };
    object begin() {
        return object(*this);
    }

    nlohmann::basic_json<> get_config(object & value) {
        return value.currect_object;
    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::filesystem::path cwd = std::filesystem::current_path() / "config.json";
    json_config_parser a(cwd.string());
    auto beg = a.begin();
    std::print("{}\n", a.get_config(beg / "SERVER" / "OBJECT" / "HELLO" ).get<int>() );
    return 0;
}
