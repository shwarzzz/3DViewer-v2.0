#ifndef VIEWER_VIEW_H_
#define VIEWER_VIEW_H_

#include <QCloseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "../controller/viewer_controller.h"
#include "../modules/picture_maker.h"
#include "../modules/qtgifimage/src/gifimage/qgifimage.h"
#include "glview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewerView;
}
QT_END_NAMESPACE

class ViewerView : public QMainWindow {
  Q_OBJECT

 public:
  ViewerView(s21::ViewerController* c, QWidget* parent = nullptr);
  ~ViewerView();

 private:
  void SetEventHandler();

  Ui::ViewerView* ui_;
  s21::ViewerController* controller_;

  QSettings* current_settings_;

  QGifImage* gif_;
  QImage* gif_frame_;
  QTimer* gif_timer_;
  size_t frame_count_;

  void LoadSettings();
  void SaveSettings();
  void ClearMoveData();
  void MakeGif();

 private slots:
  void ProcessOpenFileButtonClicked();

  void ProcessScaleValueChanged();

  void ProcessXMoveValueChanged();
  void ProcessYMoveValueChanged();
  void ProcessZMoveValueChanged();

  void ProcessXAngleValueChanged();
  void ProcessYAngleValueChanged();
  void ProcessZAngleValueChanged();

  void ProcessSelectBackgroundColorClicked();
  void ProcessSelectVertexesColorClicked();
  void ProcessSelectFacetsColorClicked();

  void ProcessWeightOfLineValueChanged();
  void ProcessPointSizeChanged();
  void ProcessDottedLineChanged();

  void ProcessBackgroundRedColorChanged();
  void ProcessBackgroundGreenColorChanged();
  void ProcessBackgroundBlueColorChanged();
  void ProcessBackgroundAlphaChanged();

  void ProcessVertexesRedColorChanged();
  void ProcessVertexesGreenColorChanged();
  void ProcessVertexesBlueColorChanged();

  void ProcessFacetsRedColorChanged();
  void ProcessFacetsGreenColorChanged();
  void ProcessFacetsBlueColorChanged();

  void ProcessNoPointsSelected();
  void ProcessCirclePointsSelected();
  void ProcessSquarePointsSelected();

  void ProcessOrthoSelected();
  void ProcessPerspectiveSelected();

  void ProcessScreencastButtonClicked();

  void ProcessAddFrameToGif();

  void closeEvent(QCloseEvent* event);
};
#endif  // VIEWER_VIEW_H
