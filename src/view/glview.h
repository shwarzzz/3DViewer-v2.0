#ifndef GLVIEW_H_
#define GLVIEW_H_

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <QtOpenGL>
#include <QtOpenGLWidgets>

#include "../modules/data.h"

namespace s21 {
class GLView : public QOpenGLWidget {
  Q_OBJECT

 public:
  GLView(QWidget* parent = nullptr);

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void SetData(const s21::data& src);

  void SetBackColor(size_t color, float value);
  void SetVertexesOneColor(size_t color, float value);
  void SetFacetsOneColor(size_t color, float value);

  void SetLineWidth(float width);
  void SetPointSize(float size);

  void SetDottedLine(bool status);
  void SetVertexesStyle(s21::VertexesStyle style);

  void SetProjectionType(s21::ProjectionType type);

  s21::ProjectionType GetProjectionType();
  s21::VertexesStyle GetVertexesStyle();

  bool IsLineDotted();
  float GetBackgroundOneColor(size_t color);
  float GetVertexesOneColor(size_t color);
  float GetFacetsOneColor(size_t color);

  float GetLineWidth();
  float GetPointsSize();

 private:
  void ChangeProjectionType();
  void DrawGL();

  const s21::data* draw_data_;
  s21::settings settings_;
};
}  // namespace s21

#endif  // GLVIEW_H
