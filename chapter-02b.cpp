// ACC COSC 1337
// Chapter 02 Lab B
//
// Calculate a players height in feet + inches from only inches.

#include <iostream>

int main() {

  const int ONE_FOOT{12}; // in inches
  int heightOfStarPlayer{75}; // in inches

  std::cout << "A " << heightOfStarPlayer << " inch tall basketball player is " << heightOfStarPlayer / ONE_FOOT << " feet " << heightOfStarPlayer % ONE_FOOT << " inches tall.";

  return 0;
}
