#include "viewer_model.h"

s21::ViewerModel::ViewerModel() { ResetData(); }

s21::ViewerModel::~ViewerModel() = default;

void s21::ViewerModel::PerformTransformations() {
  double scale = transformer_.CalculateScale(object_data_, data_changes_.scale);
  for (size_t i = 0; i < object_data_.vertexes_count; i++) {
    for (size_t j = 0; j < AXIS_COUNT; j++) {
      draw_data_.vertexes.matrix(i, j) = transformer_.MoveValue(
          transformer_.ScaleValue(object_data_.vertexes.matrix(i, j), scale),
          data_changes_.axis_move[j]);
    }
    transformer_.RotateVertex(draw_data_, data_changes_, i);
  }
}

void s21::ViewerModel::ReadDataFromFile() {
  if (is_file_read_ == false) {
    ResetData();
    try {
      object_data_ = s21::FileReader::GetInstance().WritingDataFromFile(path_);
      file_status_ = "Status: Success!";
    } catch (std::runtime_error& e) {
      object_data_.Reset();
      file_status_ = e.what();
    }
    transformer_.PerformStartTransformations(object_data_);
    draw_data_ = object_data_;
    is_file_read_ = true;
  }
}

void s21::ViewerModel::SetPath(const std::string& path) {
  if (path != path_) {
    is_file_read_ = false;
    path_ = path;
  }
}

const std::string& s21::ViewerModel::GetStatus() { return file_status_; }

const s21::data& s21::ViewerModel::GetDrawData() { return draw_data_; }

unsigned s21::ViewerModel::GetFacetsCount() {
  return object_data_.facets_count;
}

unsigned s21::ViewerModel::GetVertexesCount() {
  return object_data_.vertexes_count;
}

void s21::ViewerModel::ResetData() {
  object_data_.Reset();
  draw_data_.Reset();
  data_changes_.Reset();

  file_status_ = "";
}

void s21::ViewerModel::UpdateData(s21::ChangedValueType type, double value) {
  switch (type) {
    case kScale:
      data_changes_.scale = value / 100.0;
      break;
    case kXMove:
      data_changes_.axis_move[0] = value;
      break;
    case kYMove:
      data_changes_.axis_move[1] = value;
      break;
    case kZMove:
      data_changes_.axis_move[2] = value;
      break;
    case kXAngle:
      data_changes_.axis_angle[0] = value;
      break;
    case kYAngle:
      data_changes_.axis_angle[1] = value;
      break;
    case kZAngle:
      data_changes_.axis_angle[2] = value;
      break;
    default:
      break;
  }
  PerformTransformations();
}