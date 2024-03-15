#ifndef AFFINE_PERFORMER_H_

#define AFFINE_PERFORMER_H_

#include "../modules/data.h"

namespace s21 {

class AffinePerformer {
 public:
  AffinePerformer(){};

  void PerformStartTransformations(data& src);

  double CalculateScale(const data& src, double input_value);
  void CalculateProjectionData(data& src);

  double ScaleValue(double value, double scale);
  double MoveValue(double value, double move);
  void RotateVertex(data& src, changes& change, size_t i);

 private:
  void CenteringVertexes(data& src);
};
}  // namespace s21

#endif
