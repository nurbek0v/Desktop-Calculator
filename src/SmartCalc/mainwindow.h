#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "depositcalcwindow.h"
#include "loancalcwindow.h"
#include "mainwindowgraph.h"

extern "C" {
#include "../calculator/s21_calculator.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void graphButton_clicked();
  void loanButton_clicked();
  void depositButton_clicked();

  void equalButton_clicked();
  void clearButton_clicked();

  void bind_slots();
  void inputButtons_clicked();

  QString getErrorMessage(error_type error);

 private:
  Ui::MainWindow *ui;
  MainWindowGraph *graphWindow;
  LoanCalcWindow *loanWindow;
  DepositCalcWindow *depositWindow;
};
#endif  // MAINWINDOW_H
