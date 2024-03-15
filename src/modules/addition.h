#ifndef ADDITION_H_

#define ADDITION_H_

#include "../model/exceptions.h"
#include "data.h"
#include "string_helper.h"

namespace s21 {

class Addition {
 public:
  virtual ~Addition() {}
  virtual void AddData(const std::string& str, data& dst) = 0;
};

class VertexesAddition : public Addition {
 public:
  void AddData(const std::string& str, data& dst) override {
    int column_count = 0;
    size_t j = 1;
    while (str[j] != EOF && column_count != 3 &&
           (str[j] != '\n' && str[j] != '\0')) {
      bool is_found = false;
      std::string num = "";
      int dot_count = 0;
      int sign = 1;
      while (str[j] != EOF && str[j] != ' ' && str[j] != '\n' &&
             str[j] != '\0') {
        j++;
      }
      if (str[j] == ' ') {
        while (str[j] != EOF) {
          j++;
          if (num.size() == 0 && str[j] == ' ') {
            continue;
          } else if (num.size() == 0 && str[j] == '-') {
            sign = -1;
          } else if (StringHelper::IsDigit(str[j]) || str[j] == '.') {
            num.push_back(str[j]);
            if (str[j] == '.') {
              dot_count++;
            }
          } else {
            if ((num.size() > 0 && num[num.size() - 1] == '.') ||
                dot_count > 1 ||
                (num.size() > 1 && num[0] == '0' && num[1] != '.')) {
              throw s21::FileContentError("Status: Empty or broken file!");
            } else {
              is_found = true;
              break;
            }
          }
        }
        if (is_found) {
          double res = StringHelper::ConvertToDouble(num, sign);
          if ((unsigned long)dst.vertexes.matrix.GetRows() ==
              dst.vertexes_count) {
            dst.vertexes.matrix.SetRows(2 * dst.vertexes_count);
          }
          dst.vertexes.matrix(dst.vertexes_count, column_count) = res;
          CheckMaxAndMin(dst, column_count);
          column_count++;
        }
      }
    }
    if (column_count == 3) {
      dst.vertexes_count++;
    } else {
      throw s21::FileContentError("Status: Empty or broken file!");
    }
  }

 private:
  void CheckMaxAndMin(s21::data& dst, int axis_number) {
    if (dst.vertexes.matrix(dst.vertexes_count, axis_number) >
        dst.vertexes.matrix(dst.vertexes.axis_max[axis_number], axis_number)) {
      dst.vertexes.axis_max[axis_number] = dst.vertexes_count;
    }
    if (dst.vertexes.matrix(dst.vertexes_count, axis_number) <
        dst.vertexes.matrix(dst.vertexes.axis_min[axis_number], axis_number)) {
      dst.vertexes.axis_min[axis_number] = dst.vertexes_count;
    }
  }
};

class FacetsAddition : public Addition {
 public:
  void AddData(const std::string& str, data& dst) override {
    size_t i = 1;
    unsigned points_count = 0;
    while ((str[i] != '\n' && str[i] != '\0') && str[i] != EOF) {
      bool is_found = false;
      std::string num = "";
      int sign = 1;
      while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0' &&
             str[i] != EOF) {
        i++;
      }
      if (str[i] == ' ') {
        while (str[i] != EOF) {
          i++;
          if (num.size() == 0 && str[i] == '-') {
            sign = -1;
          } else if (StringHelper::IsDigit(str[i])) {
            num.push_back(str[i]);
          } else if (num.size() > 0) {
            if ((num.size() > 1 && num[0] == '0') || str[i] == '.') {
              throw s21::FileContentError("Status: Empty or broken file!");

            } else {
              is_found = true;
              break;
            }
          } else {
            break;
          }
        }
        if (is_found) {
          points_count++;
          double res = StringHelper::ConvertToDouble(num, sign);
          if (res < 0) {
            res = res + dst.vertexes_count + 1;
          }
          if (points_count == 1) {
            dst.polygons.push_back(std::vector<int>(1, res - 1));
          } else {
            dst.polygons[dst.polygons.size() - 1].push_back(res - 1);
          }
          if (res - 1 >= dst.vertexes_count) {
            throw s21::FileContentError("Status: Empty or broken file!");
          }
        }
      }
    }
    dst.facets_count = dst.polygons.size();
  }
};
}  // namespace s21

#endif