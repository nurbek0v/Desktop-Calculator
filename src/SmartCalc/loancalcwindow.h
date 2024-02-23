#ifndef LOANCALCWINDOW_H
#define LOANCALCWINDOW_H

#include <QMainWindow>

extern "C" {
#include "../calculator/s21_calculator.h"
}

class MainWindow;

namespace Ui {
class LoanCalcWindow;
}

class LoanCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit LoanCalcWindow(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~LoanCalcWindow();

 private slots:
  void goBackButton_clicked();
  void loanCalcButton_clicked();

  void updateButtonVisibility();

 private:
  Ui::LoanCalcWindow *ui;
  MainWindow *mainWindow;
};

#endif  // LOANCALCWINDOW_H
