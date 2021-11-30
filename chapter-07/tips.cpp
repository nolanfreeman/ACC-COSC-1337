#include "tips.h"

Tips::Tips () : taxRate{0.085} { }

Tips::Tips (const double& taxRate) : taxRate{taxRate/100} { }

double Tips::computeTip (const double& billAmount, const double& tipRate)
{
  // return (billAmount * (1.0 - this->taxRate)) * (tipRate / 100);
  return (billAmount / (1.0 + this->taxRate)) * (tipRate/100);
}
