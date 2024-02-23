#ifndef DEPOSITCALCWINDOW_H
#define DEPOSITCALCWINDOW_H

#include <QDialog>
#include <QDoubleValidator>
#include <QMainWindow>
#include <QMessageBox>

extern "C" {
#include "../calculator/s21_calculator.h"
}

class MainWindow;

namespace Ui {
class DepositCalcWindow;
}

class DepositCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit DepositCalcWindow(MainWindow *mainWindow, QWidget *parent = nullptr);
  ~DepositCalcWindow();

 private slots:
  void dBackButton_clicked();
  void dCalcButton_clicked();

  void updateButtonVisibility();

 private:
  Ui::DepositCalcWindow *ui;
  MainWindow *mainWindow;

  QDoubleValidator deposit_amount_validator;
  QDoubleValidator term_validator;
  QDoubleValidator rate_validator;
  QDoubleValidator operations_validator;
};

#endif  // DEPOSITCALCWINDOW_H
