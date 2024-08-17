#include "debit.h"

#include "ui_debit.h"

Debit::Debit(QWidget *parent) : QDialog(parent), ui(new Ui::Debit) {
  ui->setupUi(this);
}

Debit::~Debit() { delete ui; }

void Debit::on_pushButton_result_clicked() {
  double summ, data, stavka, nalog, plus, minus, result_procent, result_nalog,
      result, fix_summ;
  double result_plus = 0.0;
  double result_minus = 0.0;
  int count_plus, count_p, count_minus, count_m;
  summ = ui->doubleSpinBox_sum->value();
  stavka = ui->doubleSpinBox_stavka->value();
  nalog = ui->doubleSpinBox_nalog->value();
  plus = ui->doubleSpinBox_plus->value();
  minus = ui->doubleSpinBox_min->value();
  data = ui->spinBox_data->value();
  data *= comboBox_data;
  count_plus = data / comboBox_plus;
  count_minus = data / comboBox_minus;

  if (ui->checkBox_kapital->isChecked() && comboBox_period != 0) {
    result = summ * pow((1 + stavka / 100 / (365 / comboBox_period)),
                        data / comboBox_period);

    count_p = count_plus;
    while (count_p > 0) {
      result_plus =
          plus + result_plus * pow((1 + stavka / 100 / (365 / comboBox_period)),
                                   30.4166666666667 / comboBox_period);
      count_p--;
    }
    result_plus = result_plus *
                  pow((1 + stavka / 100 / (365 / comboBox_period)),
                      (data - (comboBox_plus * count_plus)) / comboBox_period);

    count_m = count_minus;
    while (count_m > 0) {
      result_minus =
          minus +
          result_minus * pow((1 + stavka / 100 / (365 / comboBox_period)),
                             30.4166666666667 / comboBox_period);
      count_m--;
    }
    result_minus =
        result_minus *
        pow((1 + stavka / 100 / (365 / comboBox_period)),
            (data - (comboBox_minus * count_minus)) / comboBox_period);

    result = result + result_plus - result_minus;
    result_procent =
        result - summ - (count_plus * plus) + (count_minus * minus);

  } else {
    double result_pp = plus;
    double result_mm = minus;
    count_p = count_plus;
    while (count_p - 1 > 0) {
      result_plus += result_pp * stavka / 100 * 30.4166666666667 / 365;
      count_p--;
      result_pp += plus;
    }
    if (data / comboBox_plus > 1) {
      result_plus += result_pp * stavka / 100 *
                     (data - (comboBox_plus * count_plus)) / 365;
    }

    count_m = count_minus;
    while (count_m - 1 > 0) {
      result_minus += result_mm * stavka / 100 * 30.4166666666667 / 365;
      count_m--;
      result_mm += minus;
    }
    if (data / comboBox_minus > 1) {
      result_minus +=
          minus * stavka / 100 * (data - (comboBox_minus * count_minus)) / 365;
    }

    result_procent =
        (summ * stavka * data / 365) / 100 + result_plus - result_minus;
    result = summ + (plus * count_plus) - (minus * count_minus);
  }
  fix_summ = 1000000 * nalog / 100;
  double year = data / (365);
  result_nalog = (result_procent - (fix_summ * year)) * 0.13;
  ui->doubleSpinBox_result_procent->setValue(result_procent);
  ui->doubleSpinBox_result_sum->setValue(result);
  ui->doubleSpinBox_result_nalog->setValue(result_nalog);
}

void Debit::on_comboBox_data_activated(int index) {
  if (index == 0) {
    comboBox_data = 1;
  } else if (index == 1) {
    comboBox_data = 30.4166666666667;
  } else if (index == 2) {
    comboBox_data = 30.4166666666667 * 12;
  }
}

void Debit::on_comboBox_period_activated(int index) {
  if (index == 0) {
    comboBox_period = 1;
  } else if (index == 1) {
    comboBox_period = 7;
  } else if (index == 2) {
    comboBox_period = 30.4166666666667;
  } else if (index == 3) {
    comboBox_period = 30.4166666666667 * 3;
  } else if (index == 4) {
    comboBox_period = 30.4166666666667 * 6;
  } else if (index == 5) {
    comboBox_period = 30.4166666666667 * 12;
  } else if (index == 6) {
    comboBox_period = 0;
  }
}

void Debit::on_comboBox_plus_activated(int index) {
  if (index == 0) {
    comboBox_plus = 30.4166666666667;
  } else if (index == 1) {
    comboBox_plus = 30.4166666666667 * 3;
  } else if (index == 2) {
    comboBox_plus = 30.4166666666667 * 6;
  } else if (index == 3) {
    comboBox_plus = 30.4166666666667 * 12;
  }
}

void Debit::on_comboBox_minus_activated(int index) {
  if (index == 0) {
    comboBox_minus = 30.4166666666667;
  } else if (index == 1) {
    comboBox_minus = 30.4166666666667 * 3;
  } else if (index == 2) {
    comboBox_minus = 30.4166666666667 * 6;
  } else if (index == 3) {
    comboBox_minus = 30.4166666666667 * 12;
  }
}
