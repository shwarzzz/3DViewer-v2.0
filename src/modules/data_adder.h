#ifndef DATA_ADDER_H_

#define DATA_ADDER_H_

#include "addition.h"

namespace s21 {
class DataAdder {
 public:
  DataAdder() = delete;

  DataAdder(Addition* addition) : algorithm_(addition) {}

  ~DataAdder() { delete algorithm_; }

  void AddData(const std::string& str, data& dst) {
    if (algorithm_ != nullptr) {
      algorithm_->AddData(str, dst);
    }
  }

 private:
  Addition* algorithm_ = nullptr;
};
}  // namespace s21

#endif