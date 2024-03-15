#ifndef VIEWER_CONTROLLER_H_

#define VIEWER_CONTROLLER_H_

#include "../model/viewer_model.h"

namespace s21 {
class ViewerController {
 public:
  ViewerController() = delete;
  ViewerController(ViewerModel* m) : model_(m) {}

  void ReadDataFromFileFile(const std::string& file_path);
  const s21::data& GetDrawData();
  const std::string& GetFileStatus();

  unsigned GetFacetsCount();
  unsigned GetVertexesCount();

  void ChangePosition(ChangedValueType type, double value);

 private:
  ViewerModel* model_;
};
}  // namespace s21

#endif