#include "payroll.h"

PayRoll::PayRoll () {}

PayRoll::PayRoll (const double& hourlyPay, const double& hoursWorked)
  : hourlyPay(hourlyPay),
    hoursWorked(hoursWorked)
{}

void PayRoll::setHourlyPay(const double& hourlyPay)
{
  this->hourlyPay = hourlyPay;
}

void PayRoll::setHoursWorked(const double& hoursWorked)
{
  this->hoursWorked = hoursWorked;
}

double PayRoll::getHourlyPay()
{
  return this->hourlyPay;
}

double PayRoll::getHoursWorked()
{
  return this->hoursWorked;
}

double PayRoll::getGrossPay()
{
  return this->hourlyPay * this->hoursWorked;
}
