QT       += core gui opengl
include(../modules/qtgifimage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/viewer_model.cc \
    ../model/affine_performer.cc \
    ../model/file_reader.cc \
    ../controller/viewer_controller.cc \
    ../modules/s21_matrix_oop.cc \
    glview.cc \
    main.cc \
    viewer_view.cc

HEADERS += \
    ../model/viewer_model.h \
    ../model/affine_performer.h \
    ../model/file_reader.h \
    ../modules/data.h \
    ../modules/addition.h \
    ../modules/data_adder.h \
    ../modules/picture_maker.h \
    ../modules/string_helper.h \
    ../controller/viewer_controller.h \
    ../modules/s21_matrix_oop.h \
    glview.h \
    viewer_view.h

FORMS += \
    ../ui/viewer_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
