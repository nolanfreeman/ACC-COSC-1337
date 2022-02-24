// ACC COSC 1337
// Chapter 07 Lab
//
// Compute a tip based on used inputted bill amount, tax rate and tip percentage.

#include "helperfunctions.h"

#include <iostream>
#include <iomanip>

#include "tips.h"

int main(/*int argc, char* argv[] */)
{

  double taxpct;

  std::cout << "This program will compute a restaurant tip based on a total\n"
            << "bill amount and the % the patron wishes to tip the server.\n\n";

  std::cout << "Tax % for this location: ";
  taxpct = promptForDouble(taxpct, "Tax %");

  while(true) if (!tipHelper(taxpct)) break;
}
