#include "affine_performer.h"

void s21::AffinePerformer::PerformStartTransformations(data& src) {
  CenteringVertexes(src);
  double scale = CalculateScale(src, 1);
  for (size_t i = 0; i < src.vertexes_count; i++) {
    for (size_t j = 0; j < AXIS_COUNT; j++) {
      src.vertexes.matrix(i, j) = ScaleValue(src.vertexes.matrix(i, j), scale);
    }
  }
  CalculateProjectionData(src);
}

void s21::AffinePerformer::CenteringVertexes(data& src) {
  double axis_center[3];
  for (size_t i = 0; i < AXIS_COUNT; i++) {
    axis_center[i] = src.vertexes.matrix(src.vertexes.axis_min[i], i) +
                     (src.vertexes.matrix(src.vertexes.axis_max[i], i) -
                      src.vertexes.matrix(src.vertexes.axis_min[i], i)) /
                         2;
  }
  for (size_t i = 0; i < src.vertexes_count; i++) {
    for (size_t j = 0; j < AXIS_COUNT; j++) {
      src.vertexes.matrix(i, j) -= axis_center[j];
    }
  }
}

double s21::AffinePerformer::CalculateScale(const data& src,
                                            double input_value) {
  double max = src.vertexes.matrix(src.vertexes.axis_max[0], 0) -
               src.vertexes.matrix(src.vertexes.axis_min[0], 0);
  for (size_t i = 1; i < AXIS_COUNT; i++) {
    double tmp = src.vertexes.matrix(src.vertexes.axis_max[i], i) -
                 src.vertexes.matrix(src.vertexes.axis_min[i], i);
    max = std::max(max, tmp);
  }
  double result = (input_value - (input_value * -1)) / max;
  return result;
}

double s21::AffinePerformer::ScaleValue(double value, double scale) {
  return value * scale;
}

double s21::AffinePerformer::MoveValue(double value, double move) {
  return value + move;
}

void s21::AffinePerformer::RotateVertex(data& src, changes& change, size_t i) {
  double angle[3];
  for (size_t j = 0; j < AXIS_COUNT; j++) {
    angle[j] = change.axis_angle[j] * (M_PI / 180.0);
  }
  double first = src.vertexes.matrix(i, 1);
  double second = src.vertexes.matrix(i, 2);
  src.vertexes.matrix(i, 1) = first * cos(angle[0]) - second * sin(angle[0]);
  src.vertexes.matrix(i, 2) = first * sin(angle[0]) + second * cos(angle[0]);

  first = src.vertexes.matrix(i, 0);
  second = src.vertexes.matrix(i, 2);
  src.vertexes.matrix(i, 0) = first * cos(angle[1]) - second * sin(angle[1]);
  src.vertexes.matrix(i, 2) = first * sin(angle[1]) + second * cos(angle[1]);

  first = src.vertexes.matrix(i, 0);
  second = src.vertexes.matrix(i, 1);
  src.vertexes.matrix(i, 0) = first * cos(angle[2]) - second * sin(angle[2]);
  src.vertexes.matrix(i, 1) = first * sin(angle[2]) + second * cos(angle[2]);
}

void s21::AffinePerformer::CalculateProjectionData(data& src) {
  src.perspective_data[0] = src.vertexes.matrix(src.vertexes.axis_min[0], 0);
  src.perspective_data[1] = src.vertexes.matrix(src.vertexes.axis_max[0], 0);
  src.perspective_data[2] = src.vertexes.matrix(src.vertexes.axis_min[1], 1);
  src.perspective_data[3] = src.vertexes.matrix(src.vertexes.axis_max[1], 1);
  float fov = 60 * M_PI / 180;
  src.perspective_data[4] =
      src.vertexes.matrix(src.vertexes.axis_max[1], 1) / (2 * tan(fov / 2));
  src.perspective_data[5] = 5;
}
