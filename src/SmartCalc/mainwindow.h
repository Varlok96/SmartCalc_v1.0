#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

extern "C" {
#include "../calc.h"
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

 private:
  Ui::MainWindow *ui;
  double xMin, xMax, h, X;
  int N;
  QVector<double> x, y;

 private slots:
  void digits_numbers();
  void operand();
  void t_metric();
  void on_Button_point_clicked();

  void on_Button_clear_clicked();
  void on_Button_delit_clicked();
  void on_Button_parenthesis_left_clicked();
  void on_Button_equals_clicked();
  void on_Button_parenthesis_right_clicked();

  void on_pushButton_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_debit_clicked();
};

#endif  // MAINWINDOW_H
