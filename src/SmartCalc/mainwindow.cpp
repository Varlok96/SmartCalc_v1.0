#include "mainwindow.h"

#include "credit.h"
#include "debit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_X, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->Button_plus, SIGNAL(clicked()), this, SLOT(operand()));
  connect(ui->Button_min, SIGNAL(clicked()), this, SLOT(operand()));
  connect(ui->Button_exponent, SIGNAL(clicked()), this, SLOT(operand()));
  connect(ui->Button_division, SIGNAL(clicked()), this, SLOT(operand()));
  connect(ui->Button_remainder, SIGNAL(clicked()), this, SLOT(operand()));
  connect(ui->Button_multiplication, SIGNAL(clicked()), this, SLOT(operand()));

  connect(ui->Button_radical, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_sin, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_cos, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_tg, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_asin, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_acos, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_atg, SIGNAL(clicked()), this, SLOT(t_metric()));
  connect(ui->Button_log, SIGNAL(clicked()), this, SLOT(t_metric()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_lable;
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  int i = strlen(infix) - 1;
  if (ui->label->text() == "0") {
    new_lable = button->text();
  } else if (button->text() == '0') {
    if (strchr("+-^/%*(", infix[i - 1]) && infix[i] == '0') {
      on_Button_delit_clicked();
    }
    new_lable = (ui->label->text() + button->text());
  } else if (infix[i] == ')') {
    new_lable = ui->label->text();
  } else {
    new_lable = (ui->label->text() + button->text());
  }

  ui->label->setText(new_lable);
}

void MainWindow::on_Button_point_clicked() {
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  int i = strlen(infix) - 1;
  int p_flag = 1;
  while (strlen(infix) >= 0) {
    if ((strchr("+-^/%*(", infix[i])) != NULL) {
      break;
    } else if (infix[i] == '.') {
      p_flag = 0;
      break;
    }
    i--;
  }
  if (p_flag) {
    ui->label->setText(ui->label->text() + ".");
  }
}

void MainWindow::on_Button_clear_clicked() {
  ui->label->setText(ui->label->text() = "0");
}

void MainWindow::on_Button_delit_clicked() {
  QString lebel_str = ui->label->text();
  lebel_str = lebel_str.left(lebel_str.length() - 1);
  ui->label->setText(lebel_str);
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  int i = strlen(infix) - 1;
  if (strchr("sqrtincoagl", infix[i])) {
    on_Button_delit_clicked();
  }
  if (ui->label->text() == "") {
    ui->label->setText("0");
  }
}

void MainWindow::operand() {
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  QPushButton *button = (QPushButton *)sender();
  QString new_lable = "0";
  if (ui->label->text() == "0" && button->text() == '-') {
    new_lable = button->text();
  } else if (ui->label->text() != "0") {
    if ((strchr("+-^*/%", infix[strlen(infix) - 1])) != NULL) {
      on_Button_delit_clicked();
    }
    new_lable = (ui->label->text() + button->text());
  }

  ui->label->setText(new_lable);
}

void MainWindow::on_Button_parenthesis_left_clicked() {
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  int i = strlen(infix) - 1;
  if (strchr("+-^/%*(", infix[i])) {
    ui->label->setText(ui->label->text() + "(");
  } else if (ui->label->text() == "0") {
    ui->label->setText("(");
  }
}

void MainWindow::on_Button_equals_clicked() {
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  double res;
  int err = 0;
  double x = ui->doubleSpinBox->value();
  char postfix[255] = {0};
  pars(infix, postfix);
  err = math_operations(x, postfix, &res);
  QString res_str;
  if (err == 1) {
    res_str = "nan";
  } else {
    res_str = QString::number(res, 'g', 15);
  }

  ui->label->clear();
  ui->label->setText(res_str);
}

void MainWindow::on_Button_parenthesis_right_clicked() {
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  int i = strlen(infix) - 1;
  int left = 0, right = 0;
  while (i >= 0) {
    if (infix[i] == '(') {
      left++;
    }
    if (infix[i] == ')') {
      right++;
    }
    i--;
  }
  if (left > right && strchr("0123456789)x.", infix[strlen(infix) - 1])) {
    ui->label->setText(ui->label->text() + ")");
  }
}

void MainWindow::t_metric() {
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  int i = strlen(infix) - 1;
  QPushButton *button = (QPushButton *)sender();
  QString new_lable;
  if (ui->label->text() == "0") {
    new_lable = button->text() + "(";
    ui->label->setText(new_lable);
  } else if (strchr("+-^/%*(", infix[i])) {
    new_lable = (ui->label->text() + button->text() + "(");
    ui->label->setText(new_lable);
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->widget->clearGraphs();
  ui->widget->clearPlottables();
  ui->widget->replot();
  QString old_string = ui->label->text();
  QByteArray ba = old_string.toUtf8();
  char *infix = ba.data();
  double res = 0;
  char postfix[255] = {0};
  h = 0.05;
  xMin = ui->Xmin->value();
  xMax = ui->Xmax->value();
  double yMin = ui->Xmin->value();
  double yMax = ui->Ymax->value();
  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);

  N = (xMax - xMin) / h + 2;

  for (X = xMin; X <= xMax; X += h) {
    x.push_back(X);
    pars(infix, postfix);
    math_operations(X, postfix, &res);
    y.push_back(res);
    printf("\n res %lf \n", res);
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void MainWindow::on_pushButton_credit_clicked() {
  Credit credit_calc;
  credit_calc.setModal(true);
  credit_calc.exec();
}

void MainWindow::on_pushButton_debit_clicked() {
  Debit window;
  window.setModal(true);
  window.exec();
}
