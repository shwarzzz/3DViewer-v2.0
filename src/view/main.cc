#include <QApplication>

#include "viewer_view.h"

int main(int argc, char *argv[]) {
  setenv("LC_NUMERIC", "C", 1);
  QApplication a(argc, argv);
  s21::ViewerModel model;
  s21::ViewerController controller(&model);
  ViewerView view(&controller);
  view.show();
  return a.exec();
}
