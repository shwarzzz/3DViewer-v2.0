#ifndef STRING_HELPER_H_

#define STRING_HELPER_H_

#include <cmath>
#include <string>

namespace s21 {
class StringHelper {
 public:
  static bool IsDigit(char c) noexcept { return c >= 48 && c <= 57; }

  static double ConvertToDouble(std::string str, int sign = 1) {
    bool has_dot = false;
    double count = 1;
    double result = 0;
    for (size_t i = 0; i < str.size(); i++) {
      if (str[i] == '.') {
        has_dot = true;
        count = 0;
      } else {
        result = result * 10 + (str[i] - '0');
        count++;
      }
    }
    if (has_dot) {
      result /= std::pow(10, count);
    }
    result *= sign;
    return result;
  }
};
}  // namespace s21

#endif
