#include "mainwindow.h"

#include <float.h>

#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTextEdit>
#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  graphWindow = new MainWindowGraph(this);
  loanWindow = new LoanCalcWindow(this);
  depositWindow = new DepositCalcWindow(this);
  connect(ui->graphButton, &QPushButton::clicked, this,
          &MainWindow::graphButton_clicked);
  connect(ui->loanButton, &QPushButton::clicked, this,
          &MainWindow::loanButton_clicked);
  connect(ui->depositButton, &QPushButton::clicked, this,
          &MainWindow::depositButton_clicked);

  connect(ui->equalButton, &QPushButton::clicked, this,
          &MainWindow::equalButton_clicked);
  connect(ui->clearButton, &QPushButton::clicked, this,
          &MainWindow::clearButton_clicked);

  bind_slots();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::graphButton_clicked() {
  // Переход на окно с отричовкой
  this->hide();
  graphWindow->show();
}

void MainWindow::loanButton_clicked() {
  // Переход на окно кредитного калькулятора
  this->hide();
  loanWindow->show();
}

void MainWindow::depositButton_clicked() {
  // Переход на страницу депозитного калькулятора
  this->hide();
  depositWindow->show();
}
void MainWindow::equalButton_clicked() {
  QString inputText = ui->inputLineEdit->text();

  if (inputText.isEmpty() || inputText == "0") {
    ui->resultLabel->setText("empty");
    return;
  }

  long double result = 0;
  std::string stdInputText = inputText.toStdString();
  const char *cstr = stdInputText.c_str();
  error_type error = calculate_usual(cstr, &result);

  QString errorMessage = getErrorMessage(error);
  if (!errorMessage.isEmpty()) {
    ui->resultLabel->setText(errorMessage);
    return;
  }

  QString res = QString::number(result, 'g', 7);
  ui->resultLabel->setText(res);
}

QString MainWindow::getErrorMessage(error_type error) {
  switch (error) {
    case no_error:
      return "";
    case undef_error:
      return "Undefined error";
    case invalid_input:
      return "Error: Invalid expression";
    case dividing_by_zero:
      return "Error: Trying to divide by zero";
    case negative_ln:
      return "Error: Negative natural logarithm";
    case negative_log:
      return "Error: Negative logarithm";
    default:
      return "Unknown error";
  }
}
void MainWindow::clearButton_clicked() {
  ui->inputLineEdit->setText("0");
  ui->resultLabel->setText("");
  // очистка
}
void MainWindow::bind_slots() {
  connect(ui->oneButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->twoButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->threeButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->fourButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->fiveButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->sixButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->sevenButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->eightButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->nineButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->zeroButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));

  connect(ui->pointButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->plusButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->minusButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->multiplyButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->divideButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->powerButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));

  connect(ui->openBracketButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->closeBracketButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->modButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->asinButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->acosButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->atanButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->sinButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->cosButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->tanButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->logButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->lnButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->sqrtButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
}
void MainWindow::inputButtons_clicked() {
  QPushButton *pressed_btn = (QPushButton *)sender();
  QByteArray btn_text = pressed_btn->text().toLocal8Bit();

  if (ui->inputLineEdit->text() == "0") {
    ui->inputLineEdit->setText(btn_text);
  } else {
    ui->inputLineEdit->setText(ui->inputLineEdit->text() + btn_text);
  }
}
