#pragma once
#include "token.h"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> inputData;
void readInput() {
  std::string line;
  while (getline(std::cin, line)) {
    inputData.push_back(line);
  }
}

std::vector<Token> tokens;
int lineNumber = 0;
int currentIndex = 0;

char get_next_char() { return inputData[lineNumber][currentIndex++]; }

char curr = '\0';
char nxt = '\0';

int scanner_index = 0;
Token scanner() {
  return tokens[scanner_index++];
}

void testScanner() {
  buildTable();
  curr = get_next_char();
  while (currentIndex <= inputData[lineNumber].size()) {
    std::string value = {curr};
    if (curr == '#') {
      bool isValidComment = false;
      for (int k = currentIndex + 1; k < inputData[lineNumber].size(); k++) {
        value += inputData[lineNumber][k];
        if (inputData[lineNumber][k] == '#') {
          isValidComment = true;
          currentIndex = k + 1;
          nxt = inputData[lineNumber][k + 1];
          break;
        }
      }
      if (!isValidComment) {
        std::cout << "Invalid Comment" << std::endl;
        throw;
      } else {
        tokens.push_back(Token(Comment, value, lineNumber));
      }
    } else if (curr >= 'a' && curr <= 'z') {
      nxt = get_next_char();
      int len = 1;
      while (currentIndex <= inputData[lineNumber].size() &&
             (fsa_table[curr][nxt] != END_STATE || isalpha(nxt))) {
        curr = nxt;
        value += curr;
        nxt = get_next_char();

        len++;
      }
      // make sure it's not a keyword
      if (std::find(keywords.begin(), keywords.end(), value) ==
          keywords.end()) {
        tokens.push_back(Token(Identifier, value, lineNumber));
      
      } else {
        tokens.push_back(Token(Keyword, value, lineNumber));
        
      }

    } else if (curr >= '0' && curr <= '9') {
      nxt = get_next_char();
      int len = 1;
      while (currentIndex <= (int)inputData[lineNumber].size() &&
             fsa_table[curr][nxt] != END_STATE) {
        curr = nxt;
        value += curr;
        nxt = get_next_char();

        len++;
      }
      tokens.push_back(Token(Integer, value, lineNumber));
      
    } else if (operators.find(curr) != std::string::npos) {
      nxt = get_next_char();
      int len = 1;
      while (currentIndex <= inputData[lineNumber].size() &&
             fsa_table[curr][nxt] != END_STATE) {
        len++;

        curr = nxt;
        value += curr;
        nxt = get_next_char();
      }
      if (follow.count(curr) && follow[curr] == nxt) {
        value += nxt;
        nxt = get_next_char();
        curr = nxt;
      }
      tokens.push_back(Token(Operator, value, lineNumber));
      
    } else {
      tokens.push_back(Token(InvalidToken, std::string{curr}, lineNumber));
      nxt = get_next_char();
    
    }
    while (nxt == '\0' || nxt == ' ') {
      nxt = get_next_char();
    }
    curr = nxt;
  }
  currentIndex = 0;
  lineNumber++;
  if (lineNumber < inputData.size()) {
    testScanner();
  } else {
    tokens.push_back(Token(EndOfFile, "End Of File", lineNumber));
   
  }

  Token token = scanner();
  while (true) {
    if (token.tokenID == EndOfFile || token.tokenID == InvalidToken) {
      token.printToken();
      exit(0);
    }
    token.printToken();
    token = scanner();
  }
  
}