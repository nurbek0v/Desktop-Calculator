#ifndef MAINWINDOWGRAPH_H
#define MAINWINDOWGRAPH_H

#include <QMainWindow>
// #include "mainwindow.h"
#include <string.h>

#include <QDialog>
#include <QDoubleValidator>
#include <QVector>

extern "C" {
#include "../calculator/s21_calculator.h"
}

class MainWindow;

namespace Ui {
class MainWindowGraph;
}

class MainWindowGraph : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindowGraph(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~MainWindowGraph();

 private slots:
  void gBackButton_clicked();

  void gPlotButton_clicked();

  void bind_slots();
  void inputButtons_clicked();
  void clearButton_clicked();
  void equalButton_clicked();

  // void gPlotButton_clicked();

  QString getErrorMessage(error_type error);

  void updateGraph();

 private:
  Ui::MainWindowGraph *ui;
  MainWindow *mainWindow;

  double x_min, x_max, y_min, y_max;
  double h_step, X_temp;
  int N;
  QVector<double> x_vector, y_vector;
  char *math_expression;
  void render_graph();
  // // bool is_set;
  bool can_graph;
  QDoubleValidator m_doubleValidator;
  QDoubleValidator step_doubleValidator;
};

#endif  // MAINWINDOWGRAPH_H
