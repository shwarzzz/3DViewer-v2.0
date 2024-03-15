#ifndef VIEWER_MODEL_H_

#define VIEWER_MODEL_H_

#include "affine_performer.h"
#include "file_reader.h"

namespace s21 {
class ViewerModel {
 public:
  ViewerModel();
  ~ViewerModel();

  void ReadDataFromFile();

  void SetPath(const std::string& path);
  void ResetData();

  void UpdateData(s21::ChangedValueType type, double value);

  const std::string& GetStatus();
  const s21::data& GetDrawData();

  unsigned GetFacetsCount();
  unsigned GetVertexesCount();

 private:
  void PerformTransformations();

  AffinePerformer transformer_;

  std::string path_;
  std::string file_status_;

  data object_data_;
  data draw_data_;

  changes data_changes_;

  bool is_file_read_;
};
}  // namespace s21

#endif