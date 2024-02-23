#include "loancalcwindow.h"

#include "mainwindow.h"
#include "ui_loancalcwindow.h"

LoanCalcWindow::LoanCalcWindow(MainWindow *mainWindow, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoanCalcWindow), mainWindow(mainWindow) {
  ui->setupUi(this);
  ui->loanTypeCmBox->addItem("Аннуитетный", QVariant(1));
  ui->loanTypeCmBox->addItem("Дифференцированный", QVariant(2));

  connect(ui->goBackButton, &QPushButton::clicked, this,
          &LoanCalcWindow::goBackButton_clicked);
  connect(ui->loanCalcButton, &QPushButton::clicked, this,
          &LoanCalcWindow::loanCalcButton_clicked);

  connect(ui->amountLineEdit, &QLineEdit::textChanged, this,
          &LoanCalcWindow::updateButtonVisibility);
  connect(ui->rateSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &LoanCalcWindow::updateButtonVisibility);
  connect(ui->termSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &LoanCalcWindow::updateButtonVisibility);

  updateButtonVisibility();
}

LoanCalcWindow::~LoanCalcWindow() { delete ui; }

void LoanCalcWindow::goBackButton_clicked() {
  this->hide();
  mainWindow->show();
}
void LoanCalcWindow::loanCalcButton_clicked() {
  QString amount = ui->amountLineEdit->text();
  bool ok;
  long double value = amount.toDouble(&ok);
  if (ok) {
    long double rate = ui->rateSpinBox->value();
    int termYear = ui->termSpinBox->value();
    double termYearD = termYear;
    double termMonth = convert_years_to_month(termYearD);

    QString loanTypeString = ui->loanTypeCmBox->currentText();

    if (!loanTypeString.isEmpty()) {
      if (loanTypeString == "Аннуитетный") {
        long double monthlyPayResult = monthly_payment_annuity(
            (double)value, (double)rate, (int)termMonth);
        long double totalPayResult =
            total_payment_annuity((double)monthlyPayResult, (int)termMonth);
        long double overPayResult =
            overpayment((double)value, (double)totalPayResult);

        QString mp = QString::number(monthlyPayResult, 'f', 3);
        QString tp = QString::number(totalPayResult, 'f', 3);
        QString ovp = QString::number(overPayResult, 'f', 3);

        ui->monthlyResultLabel->setText(mp);
        ui->overpaymentResultLabel->setText(ovp);
        ui->totalPaymentResultLabel->setText(tp);
      } else {
        long double totalPayResult =
            total_payment_differentiated(value, termMonth, rate);
        long double monthlyPayResult =
            monthly_payment_differentiated(totalPayResult, termMonth);
        long double overPayResult = overpayment(value, totalPayResult);

        QString mp = QString::number(monthlyPayResult, 'f', 3);
        QString tp = QString::number(totalPayResult, 'f', 3);
        QString ovp = QString::number(overPayResult, 'f', 3);

        ui->monthlyResultLabel->setText(mp);
        ui->overpaymentResultLabel->setText(ovp);
        ui->totalPaymentResultLabel->setText(tp);
      }

    } else {
      ui->monthlyResultLabel->setText("Invalid input of loan type! Try again");
      ui->overpaymentResultLabel->setText(
          "Invalid input of loan type! Try again");
      ui->totalPaymentResultLabel->setText(
          "Invalid input of loan type! Try again");
    }

  } else {
    ui->monthlyResultLabel->setText("Invalid input of amount! Try again");
    ui->overpaymentResultLabel->setText("Invalid input of amount! Try again");
    ui->totalPaymentResultLabel->setText("Invalid input of amount! Try again");
  }
}

void LoanCalcWindow::updateButtonVisibility() {
  bool shoulHide = ui->amountLineEdit->text().isEmpty() ||
                   ui->rateSpinBox->value() == 0.0 ||
                   ui->termSpinBox->value() == 0;
  ui->loanCalcButton->setVisible(!shoulHide);
}
