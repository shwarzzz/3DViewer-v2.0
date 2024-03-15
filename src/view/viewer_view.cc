#include "viewer_view.h"

#include "ui_viewer_view.h"

ViewerView::ViewerView(s21::ViewerController* c, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::ViewerView), controller_(c) {
  ui_->setupUi(this);
  SetEventHandler();

  current_settings_ = new QSettings("settings.config");
  LoadSettings();
  frame_count_ = 0;
  gif_ = nullptr;
}

ViewerView::~ViewerView() {
  delete ui_;
  delete current_settings_;
}

void ViewerView::SetEventHandler() {
  connect(ui_->pushButton_openFile, SIGNAL(clicked()), this,
          SLOT(ProcessOpenFileButtonClicked()));

  connect(ui_->doubleSpinBox_scale, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessScaleValueChanged()));

  connect(ui_->doubleSpinBox_xAxis, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessXMoveValueChanged()));
  connect(ui_->doubleSpinBox_yAxis, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessYMoveValueChanged()));
  connect(ui_->doubleSpinBox_zAxis, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessZMoveValueChanged()));

  connect(ui_->doubleSpinBox_xAngle, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessXAngleValueChanged()));
  connect(ui_->doubleSpinBox_yAngle, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessYAngleValueChanged()));
  connect(ui_->doubleSpinBox_zAngle, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessZAngleValueChanged()));

  connect(ui_->pushButton_selectBackColor, SIGNAL(clicked()), this,
          SLOT(ProcessSelectBackgroundColorClicked()));
  connect(ui_->pushButton_selectVertexesColor, SIGNAL(clicked()), this,
          SLOT(ProcessSelectVertexesColorClicked()));
  connect(ui_->pushButton_selectFacetsColor, SIGNAL(clicked()), this,
          SLOT(ProcessSelectFacetsColorClicked()));

  connect(ui_->doubleSpinBox_weightOfLine, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessWeightOfLineValueChanged()));
  connect(ui_->checkBox_dottedLine, SIGNAL(stateChanged(int)), this,
          SLOT(ProcessDottedLineChanged()));
  connect(ui_->doubleSpinBox_sizeOfPoints, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessPointSizeChanged()));

  connect(ui_->doubleSpinBox_backRed, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessBackgroundRedColorChanged()));
  connect(ui_->doubleSpinBox_backGreen, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessBackgroundGreenColorChanged()));
  connect(ui_->doubleSpinBox_backBlue, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessBackgroundBlueColorChanged()));
  connect(ui_->doubleSpinBox_backAlpha, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessBackgroundAlphaChanged()));

  connect(ui_->doubleSpinBox_vertRed, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessVertexesRedColorChanged()));
  connect(ui_->doubleSpinBox_vertGreen, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessVertexesGreenColorChanged()));
  connect(ui_->doubleSpinBox_vertBlue, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessVertexesBlueColorChanged()));

  connect(ui_->doubleSpinBox_facetRed, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessFacetsRedColorChanged()));
  connect(ui_->doubleSpinBox_facetGreen, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessFacetsGreenColorChanged()));
  connect(ui_->doubleSpinBox_facetBlue, SIGNAL(valueChanged(double)), this,
          SLOT(ProcessFacetsBlueColorChanged()));

  connect(ui_->radioButton_noPoints, SIGNAL(clicked()), this,
          SLOT(ProcessNoPointsSelected()));
  connect(ui_->radioButton_circlePoints, SIGNAL(clicked()), this,
          SLOT(ProcessCirclePointsSelected()));
  connect(ui_->radioButton_squarePoints, SIGNAL(clicked()), this,
          SLOT(ProcessSquarePointsSelected()));

  connect(ui_->radioButton_Ortho, SIGNAL(clicked()), this,
          SLOT(ProcessOrthoSelected()));
  connect(ui_->radioButton_Perspective, SIGNAL(clicked()), this,
          SLOT(ProcessPerspectiveSelected()));

  connect(ui_->pushButton_Screencasts, SIGNAL(clicked()), this,
          SLOT(ProcessScreencastButtonClicked()));
}

void ViewerView::ProcessOpenFileButtonClicked() {
  QString file_name = QFileDialog::getOpenFileName(
      this, "Choose object file:", "/~", "OBJ (*.obj)");
  if (!file_name.isNull()) {
    int lastSep = file_name.lastIndexOf('/') + 1;
    ui_->labelFileInfo->setText("File: " + file_name.sliced(lastSep));
    ClearMoveData();
    controller_->ReadDataFromFileFile(file_name.toStdString());
    ui_->labelStatus->setText(
        QString::fromStdString(controller_->GetFileStatus()));
    ui_->labelFacets->setText(
        "Facets: " + QString::number(controller_->GetFacetsCount(), 10));
    ui_->labelVertexes->setText(
        "Vertexes: " + QString::number(controller_->GetVertexesCount(), 10));
    ui_->openGLWidget->SetData(controller_->GetDrawData());
    ui_->openGLWidget->update();
  }
}

void ViewerView::ProcessScaleValueChanged() {
  controller_->ChangePosition(s21::kScale, ui_->doubleSpinBox_scale->value());
  ui_->openGLWidget->update();
}

void ViewerView::ProcessXMoveValueChanged() {
  controller_->ChangePosition(s21::kXMove, ui_->doubleSpinBox_xAxis->value());
  ui_->openGLWidget->update();
}

void ViewerView::ProcessYMoveValueChanged() {
  controller_->ChangePosition(s21::kYMove, ui_->doubleSpinBox_yAxis->value());
  ui_->openGLWidget->update();
}

void ViewerView::ProcessZMoveValueChanged() {
  controller_->ChangePosition(s21::kZMove, ui_->doubleSpinBox_zAxis->value());
  ui_->openGLWidget->update();
}

void ViewerView::ProcessXAngleValueChanged() {
  controller_->ChangePosition(s21::kXAngle, ui_->doubleSpinBox_xAngle->value());
  ui_->openGLWidget->update();
}

void ViewerView::ProcessYAngleValueChanged() {
  controller_->ChangePosition(s21::kYAngle, ui_->doubleSpinBox_yAngle->value());
  ui_->openGLWidget->update();
}

void ViewerView::ProcessZAngleValueChanged() {
  controller_->ChangePosition(s21::kZAngle, ui_->doubleSpinBox_zAngle->value());
  ui_->openGLWidget->update();
}

void ViewerView::ProcessNoPointsSelected() {
  ui_->openGLWidget->SetVertexesStyle(s21::kDefault);
}

void ViewerView::ProcessCirclePointsSelected() {
  ui_->openGLWidget->SetVertexesStyle(s21::kCircle);
}

void ViewerView::ProcessSquarePointsSelected() {
  ui_->openGLWidget->SetVertexesStyle(s21::kSquare);
}

void ViewerView::ProcessSelectBackgroundColorClicked() {
  QColor tmp = QColorDialog::getColor(Qt::black, this);
  float rgb[4];
  tmp.getRgbF(&rgb[0], &rgb[1], &rgb[2], &rgb[3]);

  ui_->doubleSpinBox_backRed->setValue(rgb[0]);
  ui_->doubleSpinBox_backGreen->setValue(rgb[1]);
  ui_->doubleSpinBox_backBlue->setValue(rgb[2]);
  ui_->doubleSpinBox_backAlpha->setValue(rgb[3]);
}

void ViewerView::ProcessSelectVertexesColorClicked() {
  QColor tmp = QColorDialog::getColor(Qt::yellow, this);
  float rgb[3];
  tmp.getRgbF(&rgb[0], &rgb[1], &rgb[2]);

  ui_->doubleSpinBox_vertRed->setValue(rgb[0]);
  ui_->doubleSpinBox_vertGreen->setValue(rgb[1]);
  ui_->doubleSpinBox_vertBlue->setValue(rgb[2]);
}

void ViewerView::ProcessSelectFacetsColorClicked() {
  QColor tmp = QColorDialog::getColor(Qt::red, this);
  float rgb[3];
  tmp.getRgbF(&rgb[0], &rgb[1], &rgb[2]);

  ui_->doubleSpinBox_facetRed->setValue(rgb[0]);
  ui_->doubleSpinBox_facetGreen->setValue(rgb[1]);
  ui_->doubleSpinBox_facetBlue->setValue(rgb[2]);
}

void ViewerView::ProcessWeightOfLineValueChanged() {
  ui_->openGLWidget->SetLineWidth(ui_->doubleSpinBox_weightOfLine->value());
}

void ViewerView::ProcessBackgroundRedColorChanged() {
  ui_->openGLWidget->SetBackColor(0, ui_->doubleSpinBox_backRed->value());
}

void ViewerView::ProcessBackgroundGreenColorChanged() {
  ui_->openGLWidget->SetBackColor(1, ui_->doubleSpinBox_backGreen->value());
}

void ViewerView::ProcessBackgroundBlueColorChanged() {
  ui_->openGLWidget->SetBackColor(2, ui_->doubleSpinBox_backBlue->value());
}

void ViewerView::ProcessBackgroundAlphaChanged() {
  ui_->openGLWidget->SetBackColor(3, ui_->doubleSpinBox_backAlpha->value());
}

void ViewerView::ProcessVertexesRedColorChanged() {
  ui_->openGLWidget->SetVertexesOneColor(0,
                                         ui_->doubleSpinBox_vertRed->value());
}

void ViewerView::ProcessVertexesGreenColorChanged() {
  ui_->openGLWidget->SetVertexesOneColor(1,
                                         ui_->doubleSpinBox_vertGreen->value());
}

void ViewerView::ProcessVertexesBlueColorChanged() {
  ui_->openGLWidget->SetVertexesOneColor(2,
                                         ui_->doubleSpinBox_vertBlue->value());
}

void ViewerView::ProcessFacetsRedColorChanged() {
  ui_->openGLWidget->SetFacetsOneColor(0, ui_->doubleSpinBox_facetRed->value());
}

void ViewerView::ProcessFacetsGreenColorChanged() {
  ui_->openGLWidget->SetFacetsOneColor(1,
                                       ui_->doubleSpinBox_facetGreen->value());
}
void ViewerView::ProcessFacetsBlueColorChanged() {
  ui_->openGLWidget->SetFacetsOneColor(2,
                                       ui_->doubleSpinBox_facetBlue->value());
}

void ViewerView::ProcessDottedLineChanged() {
  ui_->openGLWidget->SetDottedLine(ui_->checkBox_dottedLine->isChecked());
}

void ViewerView::ProcessPointSizeChanged() {
  ui_->openGLWidget->SetPointSize(ui_->doubleSpinBox_sizeOfPoints->value());
}

void ViewerView::ProcessOrthoSelected() {
  ui_->openGLWidget->SetProjectionType(s21::kParallel);
  ui_->openGLWidget->update();
}

void ViewerView::ProcessPerspectiveSelected() {
  ui_->openGLWidget->SetProjectionType(s21::kCenter);
  ui_->openGLWidget->update();
}

void ViewerView::LoadSettings() {
  if (current_settings_->value("OpenedEarlier").toBool()) {
    if (static_cast<s21::ProjectionType>(
            current_settings_->value("ProjectionType").toInt()) ==
        s21::kCenter) {
      ui_->radioButton_Perspective->setChecked(true);
      ui_->openGLWidget->SetProjectionType(s21::kCenter);
    }

    ui_->doubleSpinBox_vertRed->setValue(
        current_settings_->value("Vertexes/Color/Red").toFloat());
    ui_->doubleSpinBox_vertGreen->setValue(
        current_settings_->value("Vertexes/Color/Green").toFloat());
    ui_->doubleSpinBox_vertBlue->setValue(
        current_settings_->value("Vertexes/Color/Blue").toFloat());

    s21::VertexesStyle tmp = static_cast<s21::VertexesStyle>(
        current_settings_->value("Vertexes/Style").toInt());
    if (tmp == s21::kCircle) {
      ui_->radioButton_circlePoints->setChecked(true);
      ui_->openGLWidget->SetVertexesStyle(s21::kCircle);
    } else if (tmp == s21::kSquare) {
      ui_->radioButton_squarePoints->setChecked(true);
      ui_->openGLWidget->SetVertexesStyle(s21::kSquare);
    }

    ui_->doubleSpinBox_sizeOfPoints->setValue(
        current_settings_->value("Vertexes/Size").toFloat());

    ui_->doubleSpinBox_facetRed->setValue(
        current_settings_->value("Facets/Color/Red").toFloat());
    ui_->doubleSpinBox_facetGreen->setValue(
        current_settings_->value("Facets/Color/Green").toFloat());
    ui_->doubleSpinBox_facetBlue->setValue(
        current_settings_->value("Facets/Color/Blue").toFloat());

    ui_->checkBox_dottedLine->setChecked(
        current_settings_->value("Facets/DottedLine").toBool());
    ui_->doubleSpinBox_weightOfLine->setValue(
        current_settings_->value("Facets/Width").toFloat());

    ui_->doubleSpinBox_backRed->setValue(
        current_settings_->value("BackgroundColor/Red").toFloat());
    ui_->doubleSpinBox_backGreen->setValue(
        current_settings_->value("BackgroundColor/Green").toFloat());
    ui_->doubleSpinBox_backBlue->setValue(
        current_settings_->value("BackgroundColor/Blue").toFloat());
    ui_->doubleSpinBox_backAlpha->setValue(
        current_settings_->value("BackgroundColor/Alpha").toFloat());
  }
}

void ViewerView::SaveSettings() {
  current_settings_->setValue("OpenedEarlier", true);

  current_settings_->setValue(
      "ProjectionType",
      static_cast<int>(ui_->openGLWidget->GetProjectionType()));

  current_settings_->setValue("BackgroundColor/Red",
                              ui_->openGLWidget->GetBackgroundOneColor(0));
  current_settings_->setValue("BackgroundColor/Green",
                              ui_->openGLWidget->GetBackgroundOneColor(1));
  current_settings_->setValue("BackgroundColor/Blue",
                              ui_->openGLWidget->GetBackgroundOneColor(2));
  current_settings_->setValue("BackgroundColor/Alpha",
                              ui_->openGLWidget->GetBackgroundOneColor(3));

  current_settings_->setValue("Vertexes/Color/Red",
                              ui_->openGLWidget->GetVertexesOneColor(0));
  current_settings_->setValue("Vertexes/Color/Green",
                              ui_->openGLWidget->GetVertexesOneColor(1));
  current_settings_->setValue("Vertexes/Color/Blue",
                              ui_->openGLWidget->GetVertexesOneColor(2));
  current_settings_->setValue(
      "Vertexes/Style",
      static_cast<int>(ui_->openGLWidget->GetVertexesStyle()));
  current_settings_->setValue("Vertexes/Size",
                              ui_->openGLWidget->GetPointsSize());

  current_settings_->setValue("Facets/Color/Red",
                              ui_->openGLWidget->GetFacetsOneColor(0));
  current_settings_->setValue("Facets/Color/Green",
                              ui_->openGLWidget->GetFacetsOneColor(1));
  current_settings_->setValue("Facets/Color/Blue",
                              ui_->openGLWidget->GetFacetsOneColor(2));
  current_settings_->setValue("Facets/DottedLine",
                              ui_->openGLWidget->IsLineDotted());
  current_settings_->setValue("Facets/Width",
                              ui_->openGLWidget->GetLineWidth());
}

void ViewerView::closeEvent(QCloseEvent* event) {
  SaveSettings();
  event->accept();
}

void ViewerView::ClearMoveData() {
  ui_->doubleSpinBox_scale->setValue(100);

  ui_->doubleSpinBox_xAxis->setValue(0);
  ui_->doubleSpinBox_yAxis->setValue(0);
  ui_->doubleSpinBox_zAxis->setValue(0);

  ui_->doubleSpinBox_xAngle->setValue(0);
  ui_->doubleSpinBox_yAngle->setValue(0);
  ui_->doubleSpinBox_zAngle->setValue(0);
}

void ViewerView::MakeGif() {
  gif_frame_ = new QImage();
  gif_ = new QGifImage();
  gif_timer_ = new QTimer();
  gif_->setDefaultDelay(100);
  connect(gif_timer_, SIGNAL(timeout()), this, SLOT(ProcessAddFrameToGif()));
  gif_timer_->start(100);
}

void ViewerView::ProcessAddFrameToGif() {
  frame_count_++;
  QSize gifSize(640, 480);
  *gif_frame_ = ui_->openGLWidget->grabFramebuffer().scaled(gifSize);
  gif_->addFrame(*gif_frame_);
  if (frame_count_ == 50) {
    gif_timer_->stop();
    QString file_ = QFileDialog::getSaveFileName(nullptr, "Input file name",
                                                 "/", "GIF (*.gif)");
    if (!file_.isNull()) {
      gif_->save(file_);
    }
    frame_count_ = 0;
    delete gif_frame_;
    delete gif_;
    delete gif_timer_;
    gif_ = nullptr;
  }
}

void ViewerView::ProcessScreencastButtonClicked() {
  s21::PictureMaker* maker_ = nullptr;
  if (ui_->radioButton_BMP->isChecked()) {
    maker_ = new s21::BMPPictureMaker(ui_->openGLWidget);
  } else if (ui_->radioButton_JPEG->isChecked()) {
    maker_ = new s21::JPEGPictureMaker(ui_->openGLWidget);
  } else {
    if (gif_ == nullptr) {
      MakeGif();
    }
  }
  if (maker_ != nullptr) {
    maker_->Screencast();
  }
  delete maker_;
}
