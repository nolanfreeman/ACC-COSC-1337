#ifndef COSC_1337_PAYROLL_H
#define COSC_1337_PAYROLL_H

#include "payroll.h"

class PayRoll
{
private:
  double hourlyPay;
  double hoursWorked;

public:
  PayRoll ();
  PayRoll (const double&, const double&);

  void setHourlyPay(const double&);
  void setHoursWorked(const double&);
  double getHourlyPay();
  double getHoursWorked();
  double getGrossPay();

};

#endif // COSC_1337_PAYROLL_H
