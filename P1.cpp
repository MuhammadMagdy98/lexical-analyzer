#include "scanner.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {

    if (argc > 2) {
    std::cout << "Invocation error\n";
    std::cout << "Usage:\n";
    std::cout << "./main\n";
    std::cout << "./main < file\n";
    std::cout << "./main file\n";
    return 1;
  }
  if (argc == 2) {
    char *fileName = argv[1];
    std::ifstream inputFile(fileName);
    if (!inputFile.good()) {
      std::cout << "File not found\n";
      return 1;
    }
    freopen(argv[1], "r", stdin);
  }
  readInput();
  testScanner();
}