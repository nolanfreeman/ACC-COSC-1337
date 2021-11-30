#include "helperfunctions.h"

#include <iostream>
#include <iomanip>

// has side-effects
double promptForDouble (double inputVar, const char* reprompt)
{
  bool validInput {false};
  while (!validInput) {
    if (!(std::cin >> inputVar)) {
        std::cout << reprompt << " must be an number. Please re-enter " << reprompt << ": ";
    } else {
        if (inputVar < 0) {
          std::cout << reprompt << " cannot be less that 0. Please re-enter " << reprompt <<  ": ";
        } else {
          validInput = true;
        }
    }

    // clear the input stream and ignore up to 100 chars or a newline
    std::cin.clear();
    std::cin.ignore(100, '\n');

  }
  return inputVar;
}

bool tipHelper (const double& taxpct)
{
  std::cout << "\n********** Tip Helper **********\n";

  std::cout << "\nEnter total bill amount: ";
  double billamt;
  billamt = promptForDouble(billamt, "Bill amount");

  std::cout << "Enter desired tip %: ";
  double tippct;
  tippct = promptForDouble(tippct, "Tip %");

  Tips t (taxpct);

  std::cout << "\nThe tip should be $"
            << std::fixed << std::showpoint << std::setprecision(2)
            << t.computeTip(billamt, tippct);

  bool selectionMade {false};
  bool runAgain {false};
  while (!selectionMade) {

    std::cout << "\nComputer another tip (y/N)? ";

    std::string selection;
    std::getline(std::cin, selection);

    switch (selection[0]) {
      case 'y':
        // [[fallthrough]]; // std=c++17
      case 'Y':
        selectionMade = true;
        runAgain = true;
        break;
      case 'n':
        // [[fallthrough]]; // std=c++17
      case 'N':
        // [[fallthrough]]; // std=c++17
      case '\0': // User enters nothing, ie. ENTER
        selectionMade = true;
        runAgain = false;
        break;
      default:
        selectionMade = false;
        std::cout << "Please make a selection.";
        break;
    }
  }
  return runAgain;
}
