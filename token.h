#pragma once
#include <iostream>
#include <string>
#include <vector>
std::vector<std::string> keywords = {"begin", "end",  "loop",  "void", "var",
                                     "exit",  "scan", "print", "main", "fork",
                                     "then",  "let",  "data",  "func"};

std::string validChars = "=><:+-*/%.(),{};[]";
std::vector<std::string> operators = {
    "=", ">", "<", "<=", ">=", "==", ":", "++", "--", "+", "-", "*",
    "/", "%", ".", "(",  ")",  ",",  "{", "}",  ";",  "[", "]"};

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
    std::cout << tokenNames[tokenID] << " " << tokenInstance << " "
              << lineNumber + 1 << "\n";
  }
};