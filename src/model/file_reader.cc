#include "file_reader.h"

s21::data s21::FileReader::WritingDataFromFile(const std::string& path) {
  ValidateFileExtension(path);
  std::ifstream file;
  file.open(path);
  s21::data result;
  if (file.is_open()) {
    std::string buffer;
    while (getline(file, buffer)) {
      s21::DataAdder data_adder(ChooseAdditionStrategy(buffer));
      try {
        data_adder.AddData(buffer, result);
      } catch (...) {
        file.close();
        throw;
      }
    }
    file.close();
    if (result.facets_count != 0 && result.vertexes_count != 0) {
      result.vertexes.matrix.SetRows(result.vertexes_count);
    } else {
      throw s21::FileContentError("Status: Empty or broken file!");
    }
  } else {
    throw s21::OpenFileError("Status: Can't open the File!");
  }
  return result;
}

s21::Addition* s21::FileReader::ChooseAdditionStrategy(const std::string& str) {
  Addition* result = nullptr;
  if (str[0] == 'v' && str[1] == ' ') {
    result = new s21::VertexesAddition();
  } else if (str[0] == 'f' && str[1] == ' ') {
    result = new s21::FacetsAddition();
  }
  return result;
}

void s21::FileReader::ValidateFileExtension(const std::string& path) {
  if (path.size() < 5) {
    throw s21::WrongFileExtensionError("Wrong file extension!");
  }
  for (size_t i = path.size() - 4, j = 0; i < path.size(); i++, j++) {
    if (kFileExtension[j] != path[i]) {
      throw s21::WrongFileExtensionError("Wrong file extension!");
    }
  }
}