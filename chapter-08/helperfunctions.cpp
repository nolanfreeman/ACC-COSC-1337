#include "helperfunctions.h"

#include <iostream>

#if defined(_WIN32) // Running Windows (unfortunately.. :) )
  #include <Windows.h> // needed to access windows filesystem
#else
  #include <dirent.h> // to find files in Unix-like environments
  #include <cstring>
#endif

double promptNum(const char* prompt, const double& defaultValue, const int& rangeMax, const int& rangeMin)
{
  bool validInput{false};
  std::string line;

  double output{defaultValue};

  while(!validInput) {

    std::cout << prompt;
    std::getline(std::cin, line);

    // if user hits enter without typing any characters
    // use default value
    if (line[0] == '\0') {
        validInput = true;
        std::cout << defaultValue;
    } else {
        std::string arg0 {line.substr(0, line.find(' '))};

        // Attempt to cast the inputted text to an integer value
        // if it doesn't work, it is not a number, reprompt
        try {
            output = std::stoi(arg0);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Not a number\n";
            validInput = false;
            continue;
        }

        if ((output <= rangeMax) && (output >= rangeMin)) {
            validInput = true;
        } else {
            validInput = false;
            std::cout << "Not a valid Natural number\n";
        }

        // clear the input stream and ignore up to 100 chars or a newline
        // std::cin.clear();
        // std::cin.ignore(100, '\n');
     }
  }

  return output;
}

bool promptYN(const std::string& prompt)
{
    while (true) {
        std::cout << prompt;

        std::string selection;
        std::getline(std::cin, selection);

        switch (selection[0]) {
            case 'n':
                // [[fallthrough]]; // std=c++17
            case 'N':
                // [[fallthrough]]; // std=c++17
                return false;
                break;
            case 'y':
                // [[fallthrough]]; // std=c++17
            case 'Y':
                // [[fallthrough]]; // std=c++17
            case '\0': // User enters nothing, ie. ENTER
                return true;
            default:
                std::cout << "Please make a selection.";
                break;
        }
    }
}

auto findFiles() -> std::pair<std::vector<std::string>, int>
{
  std::vector<std::string> filenames;
  int numFiles{0};

#if defined(_WIN32) // Running Windows (unfortunately.. :) )

  // NOT my code within this snippet.
  // I do haven't looked dove into how it's implemented either.
  // Only included after I remembered my solution for parsing files is "unix" only.
  // And I have yet to do any C++ targeting windows.
  // Without all of this mess the project would still satisfy the assignment instructions.

  using namespace std;

  // BEGIN SNIPPET
  std::string folder;
  string search_path = folder + "/*.dat";
  WIN32_FIND_DATA fd;
  HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
  if (hFind != INVALID_HANDLE_VALUE) {
      do {
          if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
              filesnames.push_back(fd.cFileName);
              numFiles++;
          }
      } while(::FindNextFile(hFind, &fd));
      ::FindClose(hFind);
  }

  // END SNIPPET

#else // Running Linux or MacOS

  // this bit uses some messy C code.
  // Which unfortunately was the only compatable solution I came across to
  // search a directory for a list of files.
  // There are better solutions, but rely on std=c++14 or std=c++17

  DIR *directory;
  char *token1, *token2;
  int validExt;
  struct dirent *file;
  directory = opendir("."); // use the current directory
  if (directory)
  {
      // run until
      while ((file = readdir(directory)) != NULL)
      {
          // get the string token before the .extension
          token1 = strtok(file->d_name, ".");
          // get the extension of the file
          token2 = strtok(NULL, ".");
          if(token2 != NULL)
          {
              // check if token2 has the extension "dat"
              validExt = strcmp(token2, "dat");
              if(validExt == 0)
              {
                  // add the string token (filename) to the vector of filenames
                  filenames.push_back(token1);
                  filenames.back().append(".dat");
                  numFiles++;
              }
          }
      }
      closedir(directory);
  }
#endif // determine OS
  return { filenames, numFiles };
}
