#include "mainwindowgraph.h"

#include <float.h>

#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTextEdit>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindowgraph.h"

MainWindowGraph::MainWindowGraph(MainWindow *mainWindow, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindowGraph),
      mainWindow(mainWindow),
      m_doubleValidator(-999999, 999999, 7, this),
      step_doubleValidator(0.1, 20, 1, this) {
  ui->setupUi(this);

  QLocale locale(QLocale::English);
  m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  step_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  m_doubleValidator.setLocale(locale);
  step_doubleValidator.setLocale(locale);

  ui->gPlotButton->hide();
  ui->xEnterFrame->hide();

  ui->xMinLineEdit->setValidator(&m_doubleValidator);
  ui->xMaxLineEdit->setValidator(&m_doubleValidator);
  ui->yMinLineEdit->setValidator(&m_doubleValidator);
  ui->yMaxLineEdit->setValidator(&m_doubleValidator);
  ui->gXLineEdit->setValidator(&m_doubleValidator);
  ui->stepLineEdit->setValidator(&step_doubleValidator);
  // initialize fields
  x_min = ui->xMinLineEdit->text().toDouble();
  x_max = ui->xMaxLineEdit->text().toDouble();
  y_min = ui->yMinLineEdit->text().toDouble();
  y_max = ui->yMaxLineEdit->text().toDouble();
  h_step = ui->stepLineEdit->text().toDouble();
  X_temp = x_min;
  N = (x_max - x_min) / h_step + 2;

  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x_vector, y_vector);
  ui->customPlot->yAxis->setRange(y_min, y_max);
  ui->customPlot->xAxis->setRange(x_min, x_max);
  ui->customPlot->xAxis->setTickLabelColor(QColor(100, 100, 100));
  ui->customPlot->yAxis->setTickLabelColor(QColor(100, 100, 100));
  ui->customPlot->xAxis->setLabel("x");
  ui->customPlot->yAxis->setLabel("y");

  // make zoom
  ui->customPlot->setInteraction(QCP::iRangeZoom, true);
  ui->customPlot->setInteraction(QCP::iRangeDrag, true);
  ui->customPlot->replot();

  connect(ui->gBackButton, &QPushButton::clicked, this,
          &MainWindowGraph::gBackButton_clicked);

  // connect(ui->gPlotButton, &QPushButton::clicked, this,
  // &MainWindowGraph::gPlotButton_clicked);

  bind_slots();
}

MainWindowGraph::~MainWindowGraph()

{
  free(math_expression);
  delete ui;
}
void MainWindowGraph::updateGraph() {
  x_min = ui->xMinLineEdit->text().toDouble();
  x_max = ui->xMaxLineEdit->text().toDouble();
  y_min = ui->yMinLineEdit->text().toDouble();
  y_max = ui->yMaxLineEdit->text().toDouble();
  h_step = ui->stepLineEdit->text().toDouble();
  X_temp = x_min;
  N = (x_max - x_min) / h_step + 2;

  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x_vector, y_vector);
  ui->customPlot->yAxis->setRange(y_min, y_max);
  ui->customPlot->xAxis->setRange(x_min, x_max);
  if (can_graph) {
    render_graph();
  }
  ui->customPlot->replot();
}
void MainWindowGraph::gBackButton_clicked() {
  this->hide();
  mainWindow->show();
}

void MainWindowGraph::gPlotButton_clicked() {
  if (can_graph) {
    render_graph();
  } else {
    ui->resultLineEdit->setText("Cannot draw this function!");
  }
}
void MainWindowGraph::inputButtons_clicked() {
  QPushButton *pressed_btn = (QPushButton *)sender();
  QByteArray btn_text = pressed_btn->text().toLocal8Bit();

  if (ui->inputLineEdit->text() == "0") {
    ui->inputLineEdit->setText(btn_text);
  } else {
    ui->inputLineEdit->setText(ui->inputLineEdit->text() + btn_text);
  }
}
void MainWindowGraph::clearButton_clicked() {
  ui->inputLineEdit->setText("0");
  ui->resultLineEdit->setText("");
  ui->customPlot->clearGraphs();
  can_graph = false;
  for (int g = 0; g < ui->customPlot->graphCount(); g++) {
    ui->customPlot->graph(g)->data().clear();
  }
  ui->customPlot->replot();
}

void MainWindowGraph::equalButton_clicked() {
  QString inputText = ui->inputLineEdit->text();

  if (inputText.isEmpty() || inputText == "0") {
    ui->resultLineEdit->setText("empty");
    can_graph = false;
    return;
  }
  std::string stdInputText = inputText.toStdString();
  const char *cstr = stdInputText.c_str();
  char *modifiedInput = strdup(cstr);

  remove_spaces(modifiedInput);
  if (is_valid_input(modifiedInput)) {
    char *divided_str = divided_by_tokens(modifiedInput);
    stack *initial_stack = parsing_elements(divided_str);
    if (contains_x_val(initial_stack)) {
      can_graph = true;
      math_expression = strdup(cstr);
      ui->resultLineEdit->setText("Function is correct!");
      updateGraph();
      render_graph();

    } else {
      long double result = 0;
      error_type error = calculate_usual(cstr, &result);

      QString errorMessage = getErrorMessage(error);
      if (!errorMessage.isEmpty()) {
        ui->resultLineEdit->setText(errorMessage);
        can_graph = false;
        return;
      }

      QString res = QString::number(result, 'g', 7);
      ui->resultLineEdit->setText(res);
      can_graph = false;
    }

  } else {
    ui->resultLineEdit->setText("not valid");
    can_graph = false;
  }
  free(modifiedInput);

  // error_type error = calculate_usual(cstr, &result);

  // QString errorMessage = getErrorMessage(error);
  // if (!errorMessage.isEmpty()) {
  //     ui->resultLineEdit->setText(errorMessage);
  //     return;
  // }

  // QString res = QString::number(result, 'g', 7);
  // ui->resultLineEdit->setText(res);
}

void MainWindowGraph::render_graph() {
  N = (x_max - x_min) / h_step + 2;
  if (N > 1000000) {
    N = 1000000;
  }
  y_vector.clear();
  x_vector.clear();
  X_temp = x_min;
  // set pen for plot
  QPen my_pen;
  my_pen.setColor(QColor(49, 49, 49));
  my_pen.setWidthF(2);
  // add coords to plot
  for (int i = 0; i < N; i++) {
    long double x_calc = 0;
    calculate_with_x_value(math_expression, (long double)(X_temp + i * h_step),
                           &x_calc);
    if (x_calc > y_min && x_calc < y_max) {
      x_vector.push_back(x_min + i * h_step);
      y_vector.push_back((double)x_calc);
    }
  }
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x_vector, y_vector);
  ui->customPlot->graph(0)->setPen(my_pen);
  ui->customPlot->replot();
}
void MainWindowGraph::bind_slots() {
  connect(ui->g1Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g2Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g3Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g4Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g5Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g6Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g7Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g8Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g9Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->g0Button, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));

  connect(ui->gPointButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gPlusButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gMinusButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gMultiplyButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gDivideButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gPowButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));

  connect(ui->gOpenBrButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gCloseBrButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gModButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gAsinButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gAcosButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gAtanButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gSinButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gCosButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gTanButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gLogButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));
  connect(ui->gLnButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));
  connect(ui->gSqrtButton, SIGNAL(clicked()), this,
          SLOT(inputButtons_clicked()));

  connect(ui->gXButton, SIGNAL(clicked()), this, SLOT(inputButtons_clicked()));

  connect(ui->gClearButton, &QPushButton::clicked, this,
          &MainWindowGraph::clearButton_clicked);
  connect(ui->gEgualButton, &QPushButton::clicked, this,
          &MainWindowGraph::equalButton_clicked);
  connect(ui->gPlotButton, &QPushButton::clicked, this,
          &MainWindowGraph::gPlotButton_clicked);

  connect(ui->xMinLineEdit, &QLineEdit::textChanged, this,
          &MainWindowGraph::updateGraph);
  connect(ui->xMaxLineEdit, &QLineEdit::textChanged, this,
          &MainWindowGraph::updateGraph);
  connect(ui->yMinLineEdit, &QLineEdit::textChanged, this,
          &MainWindowGraph::updateGraph);
  connect(ui->yMaxLineEdit, &QLineEdit::textChanged, this,
          &MainWindowGraph::updateGraph);
  connect(ui->stepLineEdit, &QLineEdit::textChanged, this,
          &MainWindowGraph::updateGraph);
}
QString MainWindowGraph::getErrorMessage(error_type error) {
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
