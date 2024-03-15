#ifndef EXCEPTIONS_H_

#define EXCEPTIONS_H_

#include <stdexcept>

namespace s21 {
class WrongFileExtensionError : public std::runtime_error {
 public:
  explicit WrongFileExtensionError(const char* message)
      : std::runtime_error(message) {}
};

class FileContentError : public std::runtime_error {
 public:
  explicit FileContentError(const char* message)
      : std::runtime_error(message) {}
};

class OpenFileError : public std::runtime_error {
 public:
  explicit OpenFileError(const char* message) : std::runtime_error(message) {}
};

}  // namespace s21

#endif