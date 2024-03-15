#ifndef PICTURE_MAKER_H_

#define PICTURE_MAKER_H_

#include <QFileDialog>
#include <QImage>
#include <QString>

#include "../view/glview.h"

namespace s21 {
class PictureMaker {
 public:
  PictureMaker() = default;
  virtual ~PictureMaker() = default;

  void Screencast() {
    ProcessScreencast();
    GetFileName();
    SaveScreencast();
  }

 protected:
  virtual void ProcessScreencast() = 0;
  virtual void GetFileName() = 0;
  virtual void SaveScreencast() = 0;
};

class BMPPictureMaker : public PictureMaker {
 public:
  BMPPictureMaker(GLView* view) : view_(view) {}

  ~BMPPictureMaker() { delete current_frame_; }

 private:
  void ProcessScreencast() override {
    current_frame_ = new QImage();
    *current_frame_ = view_->grabFramebuffer();
  }

  void GetFileName() override {
    file_ = QFileDialog::getSaveFileName(nullptr, "Input file name", "/",
                                         "BMP (*.bmp)");
  }

  void SaveScreencast() override {
    if (!file_.isNull()) {
      current_frame_->save(file_, "BMP");
    }
  }

  GLView* view_;
  QImage* current_frame_;
  QString file_;
};

class JPEGPictureMaker : public PictureMaker {
 public:
  JPEGPictureMaker(GLView* view) : view_(view) {}

  ~JPEGPictureMaker() { delete current_frame_; }

 private:
  void ProcessScreencast() override {
    current_frame_ = new QImage();
    *current_frame_ = view_->grabFramebuffer();
  }

  void GetFileName() override {
    file_ = QFileDialog::getSaveFileName(nullptr, "Input file name", "/",
                                         "JPEG (*.jpeg)");
  }

  void SaveScreencast() override {
    if (!file_.isNull()) {
      current_frame_->save(file_, "JPEG");
    }
  }

  GLView* view_;
  QImage* current_frame_;
  QString file_;
};
}  // namespace s21

#endif  // SCREENCAST_MAKER_H
