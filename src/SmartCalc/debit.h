#ifndef DEBIT_H
#define DEBIT_H

#include <QDialog>

namespace Ui {
class Debit;
}

class Debit : public QDialog {
  Q_OBJECT

 public:
  explicit Debit(QWidget *parent = nullptr);
  ~Debit();

 private slots:
  void on_pushButton_result_clicked();

  void on_comboBox_data_activated(int index);

  void on_comboBox_period_activated(int index);

  void on_comboBox_plus_activated(int index);

  void on_comboBox_minus_activated(int index);

 private:
  Ui::Debit *ui;
  double comboBox_data = 1;
  double comboBox_period = 1;
  double comboBox_plus = 30.4166666666667;
  double comboBox_minus = 30.4166666666667;
};

#endif  // DEBIT_H
