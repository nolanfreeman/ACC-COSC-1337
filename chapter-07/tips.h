#ifndef TIPS_COSC_1337_H
#define TIPS_COSC_1337_H

#include "tips.h"

class Tips {
  private:
    double taxRate;

  public:
    Tips ();
    Tips (const double& taxRate);

    double computeTip (const double&, const double&);
};

#endif // TIPS_COSC_1337_H
