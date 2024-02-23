QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../calculator/modules/calculation.c \
    ../calculator/modules/loan_calc.c \
    ../calculator/modules/parsing.c \
    ../calculator/modules/stack.c \
    ../calculator/modules/validation.c \
    ../calculator/modules/deposit_calc.c \
    ../calculator/modules/controller.c \
    depositcalcwindow.cpp \
    loancalcwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowgraph.cpp \
    qcustomplot.cpp

HEADERS += \
    ../calculator/s21_calculator.h \
    depositcalcwindow.h \
    loancalcwindow.h \
    mainwindow.h \
    mainwindowgraph.h \
    qcustomplot.h

FORMS += \
    depositcalcwindow.ui \
    loancalcwindow.ui \
    mainwindow.ui \
    mainwindowgraph.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

