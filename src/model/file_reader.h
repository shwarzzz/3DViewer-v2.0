#ifndef FILE_READER_H_

#define FILE_READER_H_

#include <fstream>

#include "../modules/addition.h"
#include "../modules/data_adder.h"

namespace s21 {
class FileReader {
 public:
  static FileReader& GetInstance() {
    static FileReader file_reader_;
    return file_reader_;
  }

  FileReader(const FileReader&) = delete;
  FileReader& operator=(const FileReader&) = delete;

  s21::data WritingDataFromFile(const std::string& path);

 private:
  FileReader(){};
  void ValidateFileExtension(const std::string& path);
  Addition* ChooseAdditionStrategy(const std::string& str);

  const std::string kFileExtension = ".obj";
};

}  // namespace s21

#endif