#include "glview.h"

namespace s21 {

GLView::GLView(QWidget* parent) : QOpenGLWidget(parent) {
  draw_data_ = nullptr;
  settings_.SetDefault();
  setWindowTitle("Here we go again!");
}

void GLView::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void GLView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLView::SetData(const s21::data& src) { draw_data_ = &src; }

void GLView::paintGL() {
  glClearColor(settings_.back_rgba[0], settings_.back_rgba[1],
               settings_.back_rgba[2], settings_.back_rgba[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (draw_data_ != nullptr && draw_data_->facets_count > 0 &&
      draw_data_->vertexes_count > 0) {
    DrawGL();
  }
}

void GLView::DrawGL() {
  ChangeProjectionType();
  glMatrixMode(GL_MODELVIEW);
  if (settings_.line_width > 0) {
    for (size_t i = 0; i < draw_data_->facets_count; i++) {
      glLineWidth(settings_.line_width);
      if (settings_.is_line_dotted) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(8, 4);
      } else {
        glDisable(GL_LINE_STIPPLE);
      }
      glBegin(GL_LINE_LOOP);
      glColor3f(settings_.facets_rgb[0], settings_.facets_rgb[1],
                settings_.facets_rgb[2]);
      for (size_t j = 0; j < draw_data_->polygons[i].size(); j++) {
        glVertex3f(
            draw_data_->vertexes.matrix(draw_data_->polygons[i].at(j), 0),
            draw_data_->vertexes.matrix(draw_data_->polygons[i].at(j), 1),
            draw_data_->vertexes.matrix(draw_data_->polygons[i].at(j), 2));
      }
      glEnd();
    }
  }
  if (settings_.vertex_style != s21::kDefault && settings_.point_size > 0) {
    if (settings_.vertex_style == s21::kCircle) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(settings_.point_size);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < draw_data_->vertexes_count; i++) {
      glColor3f(settings_.vertexes_rgb[0], settings_.vertexes_rgb[1],
                settings_.vertexes_rgb[2]);
      glVertex3f(draw_data_->vertexes.matrix(i, 0),
                 draw_data_->vertexes.matrix(i, 1),
                 draw_data_->vertexes.matrix(i, 2));
    }
    glEnd();
  }
}

void GLView::SetLineWidth(float width) {
  settings_.line_width = width;
  update();
}

void GLView::SetPointSize(float size) {
  settings_.point_size = size;
  update();
}

void GLView::SetVertexesStyle(s21::VertexesStyle style) {
  settings_.vertex_style = style;
  update();
}

void GLView::SetBackColor(size_t color, float value) {
  settings_.back_rgba[color] = value;
  update();
}

void GLView::SetVertexesOneColor(size_t color, float value) {
  settings_.vertexes_rgb[color] = value;
  update();
}

void GLView::SetFacetsOneColor(size_t color, float value) {
  settings_.facets_rgb[color] = value;
  update();
}

void GLView::SetDottedLine(bool status) {
  settings_.is_line_dotted = status;
  update();
}

void GLView::SetProjectionType(s21::ProjectionType type) {
  settings_.projection_type = type;
}

s21::ProjectionType GLView::GetProjectionType() {
  return settings_.projection_type;
}

s21::VertexesStyle GLView::GetVertexesStyle() { return settings_.vertex_style; }

bool GLView::IsLineDotted() { return settings_.is_line_dotted; }

float GLView::GetBackgroundOneColor(size_t color) {
  return settings_.back_rgba[color];
}

float GLView::GetVertexesOneColor(size_t color) {
  return settings_.vertexes_rgb[color];
}

float GLView::GetFacetsOneColor(size_t color) {
  return settings_.facets_rgb[color];
}

float GLView::GetLineWidth() { return settings_.line_width; }

float GLView::GetPointsSize() { return settings_.point_size; }

void GLView::ChangeProjectionType() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (settings_.projection_type == s21::kParallel) {
    glOrtho(draw_data_->perspective_data[0] * 2,
            draw_data_->perspective_data[1] * 2,
            draw_data_->perspective_data[2] * 2,
            draw_data_->perspective_data[3] * 2,
            draw_data_->perspective_data[4], draw_data_->perspective_data[5]);
  } else {
    glFrustum(draw_data_->perspective_data[0], draw_data_->perspective_data[1],
              draw_data_->perspective_data[2], draw_data_->perspective_data[3],
              draw_data_->perspective_data[4], draw_data_->perspective_data[5]);
  }
  glTranslated(0, 0, -draw_data_->perspective_data[4] * 3);
}
}  // namespace s21
