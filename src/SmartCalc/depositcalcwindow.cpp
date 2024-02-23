#include "depositcalcwindow.h"

#include "mainwindow.h"
#include "ui_depositcalcwindow.h"

DepositCalcWindow::DepositCalcWindow(MainWindow *mainWindow, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::DepositCalcWindow),
      mainWindow(mainWindow),
      deposit_amount_validator(0, 100000000, 7, this),
      term_validator(1, 60, 0, this),
      rate_validator(0.1, 1000, 2, this),
      operations_validator(0, 100000000, 7, this) {
  ui->setupUi(this);
  connect(ui->dBackButtom, &QPushButton::clicked, this,
          &DepositCalcWindow::dBackButton_clicked);
  connect(ui->dCalcButton, &QPushButton::clicked, this,
          &DepositCalcWindow::dCalcButton_clicked);

  connect(ui->depositValueAmount, &QLineEdit::textChanged, this,
          &DepositCalcWindow::updateButtonVisibility);
  connect(ui->termLineEdit, &QLineEdit::textChanged, this,
          &DepositCalcWindow::updateButtonVisibility);
  connect(ui->rateLineEdit, &QLineEdit::textChanged, this,
          &DepositCalcWindow::updateButtonVisibility);

  ui->perMonthRadioButton->setChecked(true);
  ui->monthRadioButton->setChecked(true);

  QLocale locale(QLocale::English);
  deposit_amount_validator.setNotation(QDoubleValidator::StandardNotation);
  term_validator.setNotation(QDoubleValidator::StandardNotation);
  rate_validator.setNotation(QDoubleValidator::StandardNotation);
  operations_validator.setNotation(QDoubleValidator::StandardNotation);
  deposit_amount_validator.setLocale(locale);
  term_validator.setLocale(locale);
  rate_validator.setLocale(locale);
  operations_validator.setLocale(locale);
  ui->depositValueAmount->setValidator(&deposit_amount_validator);
  ui->termLineEdit->setValidator(&term_validator);
  ui->rateLineEdit->setValidator(&rate_validator);
  ui->taxLineEdit->setValidator(&rate_validator);
  ui->replanLineEdit->setValidator(&operations_validator);
  ui->withdrawLineEdit->setValidator(&operations_validator);

  updateButtonVisibility();
}

DepositCalcWindow::~DepositCalcWindow() { delete ui; }

void DepositCalcWindow::dBackButton_clicked() {
  this->hide();
  mainWindow->show();
}

void DepositCalcWindow::dCalcButton_clicked() {
  long double deposit_amount = ui->depositValueAmount->text().toDouble();
  double term = ui->termLineEdit->text().toDouble();
  if (ui->yearRadiobutton->isChecked()) {
    term = convert_years_to_month(term);
  }
  long double interest_rate = ui->rateLineEdit->text().toDouble();
  long double tax_rate = ui->taxLineEdit->text().toDouble();
  int mode = ui->perMonthRadioButton->isChecked() ? MONTHLY : YEARLY;
  bool is_capitalization = ui->capitalizationRadioButton->isChecked();
  long double monthly_replenishment = ui->replanLineEdit->text().toDouble();
  long double monthly_withdrawal = ui->withdrawLineEdit->text().toDouble();
  long double total_earned = get_total_earned(
      &deposit_amount, term, interest_rate, mode, is_capitalization,
      monthly_replenishment, monthly_withdrawal);
  long double tax_amount = get_tax_amount(total_earned, tax_rate);
  long double total_amount =
      get_total_amount(deposit_amount, total_earned, tax_amount);
  QString tot_e = QString::number(total_earned, 'f', 3);
  QString tax_a = QString::number(tax_amount, 'f', 3);
  QString tot_a = QString::number(total_amount, 'f', 3);
  ui->earnedLabel->setText(tot_e);
  ui->taxLabel->setText(tax_a);
  ui->totalAmountLabel->setText(tot_a);
}

void DepositCalcWindow::updateButtonVisibility() {
  bool shoulHide = ui->depositValueAmount->text().isEmpty() ||
                   ui->termLineEdit->text().isEmpty() ||
                   ui->rateLineEdit->text().isEmpty();
  // ui->rateSpinBox->value() == 0.0 ||
  // ui->termSpinBox->value() == 0;
  ui->dCalcButton->setVisible(!shoulHide);
}
