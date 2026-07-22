module;

#include <string>

export module firewolf.fs.types:base;

namespace firewolf::fs::types {

export class BaseVFile {
public:
  virtual ~BaseVFile() = default;
  virtual std::string getName() const = 0;
  virtual std::string getContext() = 0;
};

} // namespace firewolf::fs::types