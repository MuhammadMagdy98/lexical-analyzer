#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

int fsa_table[1280][1280] = {};
std::string operators = "+-><()[]{};*/%+.:-=,";
std::map<char, char> follow;
std::vector<std::string> keywords = {"begin", "end",  "loop",  "void", "var",
                                     "exit",  "scan", "print", "main", "fork",
                                     "then",  "let",  "data",  "func"};
enum { END_STATE = 1010 };

void buildTable() {
  follow['+'] = '+';
  follow['-'] = '-';
  follow['='] = '=';
  follow['<'] = '=';
  follow['>'] = '=';
  for (char i = 'a'; i <= 'z'; i++) {
    for (char j = 'a'; j <= 'z'; j++) {
      fsa_table[i][j] = j;
    }
    fsa_table[i]['\0'] = END_STATE;
    fsa_table[i][' '] = END_STATE;
    for (char j = '0'; j <= '9'; j++) {
      fsa_table[i][j] = j;
    }
    for (auto x : operators) {
      fsa_table[i][x] = END_STATE;
    }
  }
  for (char i = '0'; i <= '9'; i++) {
    for (char j = '0'; j <= '9'; j++) {
      fsa_table[i][j] = j;
    }
    fsa_table[i]['\0'] = END_STATE;
    fsa_table[i][' '] = END_STATE;
    for (int j = 'a'; j <= 'z'; j++) {
      fsa_table[i][j] = END_STATE;
    }
    for (auto x : operators) {
      fsa_table[i][x] = END_STATE;
    }
  }
  for (char i = 'a'; i <= 'z'; i++) {
    for (char j = 0; j <= 127; j++) {
      if (!isalpha(j) && !isdigit(j)) {
        fsa_table[i][j] = END_STATE;
      }
      // avoid overflow caused by j++
      if (j == 127)
        break;
    }
  }
  for (char i = '0'; i <= '9'; i++) {
    for (char j = 0; j <= 127; j++) {
      if (!isdigit(j)) {
        fsa_table[i][j] = END_STATE;
      }
      // avoid overflow caused by j++
      if (j == 127)
        break;
    }
  }

  fsa_table['+']['+'] = END_STATE;
  fsa_table['-']['-'] = END_STATE;
  fsa_table['=']['='] = END_STATE;
  fsa_table['<']['='] = END_STATE;
  fsa_table['>']['='] = END_STATE;

  for (auto x : operators) {
    for (char i = 'a'; i <= 'z'; i++) {
      fsa_table[x][i] = END_STATE;
    }
    for (char i = '0'; i <= '9'; i++) {
      fsa_table[x][i] = END_STATE;
    }
    for (auto y : operators) {
      fsa_table[x][y] = END_STATE;
    }
    fsa_table[x]['\0'] = END_STATE;
    fsa_table[x][' '] = END_STATE;
  }
}

std::vector<std::string> tokenNames = {"Identifier",   "Integer", "Keyword",
                                       "Operator",     "Comment", "EndOfFile",
                                       "Invalid Token"};

enum tokenID {
  Identifier,
  Integer,
  Keyword,
  Operator,
  Comment,
  EndOfFile,
  InvalidToken
};
struct Token {
  enum tokenID tokenID;
  std::string tokenInstance;
  int lineNumber;

  Token() {}
  Token(enum tokenID tokenID, std::string tokenInstance, int lineNumber)
      : tokenID(tokenID), tokenInstance(tokenInstance), lineNumber(lineNumber) {
  }

  void printToken() {

    std::cout << tokenNames[tokenID] << " \"" << tokenInstance << "\" Line number "
              << lineNumber + 1 << "\n";
    // if (tokenID == InvalidToken) {
    //   throw;
    // }
  }
};