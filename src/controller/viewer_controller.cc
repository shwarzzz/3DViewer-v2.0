#include "viewer_controller.h"

void s21::ViewerController::ReadDataFromFileFile(const std::string& file_path) {
  model_->SetPath(file_path);
  model_->ReadDataFromFile();
}

const s21::data& s21::ViewerController::GetDrawData() {
  return model_->GetDrawData();
}

const std::string& s21::ViewerController::GetFileStatus() {
  return model_->GetStatus();
}

unsigned s21::ViewerController::GetFacetsCount() {
  return model_->GetFacetsCount();
}

unsigned s21::ViewerController::GetVertexesCount() {
  return model_->GetVertexesCount();
}

void s21::ViewerController::ChangePosition(ChangedValueType type,
                                           double value) {
  model_->UpdateData(type, value);
}