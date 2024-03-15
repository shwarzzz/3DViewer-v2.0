#ifndef DATA_H_

#define DATA_H_

#include <vector>

#include "s21_matrix_oop.h"

#define AXIS_COUNT 3

namespace s21 {

enum ChangedValueType {
  kScale = 0,
  kXMove = 1,
  kYMove = 2,
  kZMove = 3,
  kXAngle = 4,
  kYAngle = 5,
  kZAngle = 6
};

enum ProjectionType { kParallel = 0, kCenter = 1 };

enum VertexesStyle { kDefault = 0, kCircle = 1, kSquare = 2 };

struct settings {
  float back_rgba[4]{};
  float facets_rgb[3]{};
  float vertexes_rgb[3]{};

  float line_width;
  float point_size;
  bool is_line_dotted;

  ProjectionType projection_type;

  VertexesStyle vertex_style;

  void SetDefault() {
    line_width = 1;
    point_size = 1;
    is_line_dotted = false;
    projection_type = kParallel;
    vertex_style = kDefault;

    for (size_t i = 0; i < 3; i++) {
      back_rgba[i] = 0;
      facets_rgb[i] = 0;
      vertexes_rgb[i] = 0;
    }
    facets_rgb[1] = 1;
    vertexes_rgb[0] = 1;
    back_rgba[3] = 1;
  }
};

struct changes {
  float axis_move[AXIS_COUNT]{};
  double axis_angle[AXIS_COUNT]{};
  double scale;

  void Reset() {
    for (size_t i = 0; i < AXIS_COUNT; i++) {
      axis_move[i] = 0;
      axis_angle[i] = 0;
    }
    scale = 1;
  }
};

struct matrix_t {
  S21Matrix matrix;
  unsigned axis_max[AXIS_COUNT]{};
  unsigned axis_min[AXIS_COUNT]{};
};

using polygon = std::vector<int>;

struct data {
  unsigned vertexes_count = 0;
  unsigned facets_count = 0;

  float perspective_data[6];

  std::vector<polygon> polygons;
  matrix_t vertexes;

  void Reset() {
    vertexes_count = 0;
    facets_count = 0;

    polygons.clear();

    for (size_t i = 0; i < AXIS_COUNT; i++) {
      vertexes.axis_max[0] = 0;
      vertexes.axis_max[1] = 0;
      vertexes.axis_max[2] = 0;

      vertexes.axis_min[0] = 0;
      vertexes.axis_min[1] = 0;
      vertexes.axis_min[2] = 0;
    }
  }
};
}  // namespace s21
#endif