module;

#include <memory>
#include <sstream>
#include <string>

export module firewolf.fs.types:vfile;

import :base;

namespace firewolf::fs::types {

export template <typename T> class VFile : public BaseVFile {
private:
  std::string name;
  std::shared_ptr<T> data_model;

public:
  VFile(const std::string &file_name, std::shared_ptr<T> model)
      : name(file_name), data_model(model) {}
  std::string getName() const override { return this->name; }
  std::string getContext() override {
    if (!this->data_model)
      return "";
    std::stringstream ss;
    ss << data_model.get() << "\n";
    return ss.str();
  }
};

} // namespace firewolf::fs::types