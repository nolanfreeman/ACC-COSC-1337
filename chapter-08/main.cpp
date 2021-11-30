// ACC COSC 1337
// Chapter 08 Lab
//
// Compute payroll based on file data or user input.

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "entrymode.h"
#include "payroll.h"
#include "helperfunctions.h"

// uncomment the following preprocessor directive to (attempt to) dynamically find files programically
// works fine on Linux (debian), and should work just as well on MacOS, too.
// but Windows requires a complete different set of logic for std <= c++11,
// and I don't have an active Windows environment to test.
// Still satisfies assignment instructions without it.

#define USE_FIND_FILES_FUNCTION

int main(/* int argc, char* argv[] */)
{

  EntryMode MODE;

  std::string infileName;

// attempt to detect files
// This will run if the Macro USE_FIND_FILES_FUNCTION is defined above
#ifdef USE_FIND_FILES_FUNCTION
  int numFiles;
  std::vector<std::string> foundFiles;

  auto filesPair = findFiles();
  foundFiles = filesPair.first;
  numFiles = filesPair.second;

  if (numFiles == 1 || numFiles == -1) {
    std::cout << "Found \"" << foundFiles[0] << "\". ";
    if (promptYN("\nParse data from this file? (Y/n): ")) {
      MODE = FILE_m;
      infileName = foundFiles[0];
    } else {
      MODE = MANUAL_m;
    }
  } else if (numFiles > 1) {
      std::cout << "Multiple *.dat files found. Please make a selection:\n";

      for (int i = 0; i < numFiles; ++i) {
        std::cout << i+1 << ": " << foundFiles[i] << ((i == 0) ? " (default)" : "") << '\n';
      }
      std::cout << numFiles+1 << ": " << "[Manual Entry]\n";

      int selection = promptNum("Selection: ", 1, numFiles+1, 1);
      if (selection == numFiles+1) {
        MODE = MANUAL_m;
      } else {
        MODE = FILE_m;
        infileName = foundFiles[selection-1];
      }
  } else {
    std::cout << "No *.dat file(s) found in directory.";
    if (promptYN("\nEnter info manually? (Y/n): ")) {
      MODE = MANUAL_m;
    } else {
      std::cout << "Quitting ...\n";
      exit(0);
    }
  }
#endif // USE_FIND_FILES_FUNCTION

// This will run if the Macro USE_FIND_FILES_FUNCTION is NOT defined above
#ifndef USE_FIND_FILES_FUNCTION
  if (promptYN("Search for \"payroll.dat\" file? (Y/n): ")) {
    infileName = "payroll.dat";
    MODE = FILE_m;
  } else {
    if (promptYN("\nEnter info manually? (Y/n): ")) {
      MODE = MANUAL_m;
    } else {
      std::cout << "Quitting ...\n";
      exit(0);
    }
  }
#endif // USE_FIND_FILES_FUNCTION

  std::ifstream infile(infileName);

  if (MODE == FILE_m && !infile) {
    std::cout << "The file \"" << infileName << "\" couldn't be opened or doesn't exist.";
    if (promptYN("\nEnter info manually? (Y/n): ")) {
      MODE = MANUAL_m;
    } else {
      std::cout << "Quitting ...\n";
      exit(0);
    }
  }

  int numEmployees{};
  PayRoll *employees;

  double hoursWorked;
  double hourlyRate;
  const double MINIMUM_WAGE{7.25};

  if (MODE == MANUAL_m) {
    std::cout << "\nManual mode selected ...\n";

    numEmployees = promptNum("How many employees are there? (3): ", 3);
    employees = new PayRoll[numEmployees];

    std::string prompt;
    for (int i{0}; i < numEmployees; ++i) {
      prompt = "\nEmployee " + std::to_string(i+1) + " hours worked: ";
      hoursWorked = promptNum(prompt.c_str(), 0);

      prompt = "\nEmploye " + std::to_string(i+1) + " hourly rate: $ ";
      hourlyRate = promptNum(prompt.c_str(), MINIMUM_WAGE);

      employees[i].setHoursWorked(hoursWorked);
      employees[i].setHourlyPay(hourlyRate);
    }

  } else if (MODE == FILE_m) {
    std::cout << "\nFile mode selected ...\n";
    std::cout << "Continuing with file: \"" << infileName << "\" ...\n";

    std::string line;
    while (std::getline(infile, line)) {
      numEmployees++;
    }
    employees = new PayRoll[numEmployees];

    // clear errors for eof and reset to beginning of file
    infile.clear();
    infile.seekg(0, std::ios::beg);

    for (int i{0}; i < numEmployees; ++i) {
      infile >> hoursWorked;
      infile >> hourlyRate;

      employees[i].setHoursWorked(hoursWorked);
      employees[i].setHourlyPay(hourlyRate);
    }
  }

  infile.close();

  std::cout << "\nEmployee" << " " << std::setw(9) << "Gross Pay" << " " << "Details\n";
  std::cout << "========" << " " << "=========" << " " << "===================\n";

  for (int i = 0; i < numEmployees; i++) {
    std::cout << std::setw(7) << i+1 << ":" << " ";
    std::cout << std::fixed << std::showpoint << std::setprecision(2) << "$" << std::setw(8) << employees[i].getGrossPay();
    std::cout << " [" << employees[i].getHoursWorked() << "h @ $" << std::setw(5) << employees[i].getHourlyPay() << "/h]" << "\n";
  }

  delete[] employees;

  return 0;
}
