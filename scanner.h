#pragma once
#include "token.h"
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>


std::vector<std::string> inputData;
void readInput() {
  std::string line;
  while (getline(std::cin, line)) {
    inputData.push_back(line);
  }
}

int lineNumber = 0;
int currentIndex = 0;

std::pair<bool, std::string> isIdentifier(std::string line) {

  int now = currentIndex;
  // must begin with a lowercase letter
  if (!islower(line[now]))
    return {false, ""};
  std::string currentValue;
  while (now < line.size()) {
    if (!isdigit(line[now]) && !isalpha(line[now])) {
      currentIndex = now;
      return {true, currentValue};
    }
    currentValue += line[now];
    auto it = std::find(keywords.begin(), keywords.end(), currentValue);
    // make sure the identifier value is not in keywords list
    if (it != keywords.end() && now + 1 < line.size() && line[now + 1] == ' ') {
      return {false, ""};
    }
    now++;
  }

  auto it = std::find(keywords.begin(), keywords.end(), currentValue);
  if (it == keywords.end()) {
    currentIndex = now;
    return {true, currentValue};
  }
  return {false, currentValue};
}

std::pair<bool, std::string> isKeyWord(std::string line) {
  const int MAX_KEY_WORD_SIZE = 5;
  int now = currentIndex;
  // must begin with a lowercase letter
  if (!islower(line[now]))
    return {false, ""};
  std::string currentValue;
  while (now < line.size()) {
    if (!isdigit(line[now]) && !isalpha(line[now])) {
      return {false, ""};
    }
    currentValue += line[now];
    auto it = std::find(keywords.begin(), keywords.end(), currentValue);
    // make sure the identifier value is not in keywords list
    if (it != keywords.end() && now + 1 < line.size() && line[now + 1] == ' ') {
      currentIndex = now + 1;
      return {true, currentValue};
    }
    now++;
  }
  auto it = std::find(keywords.begin(), keywords.end(), currentValue);
  if (it != keywords.end()) {
    currentIndex = now;
    return {true, currentValue};
  }
  return {false, currentValue};
}

std::pair<bool, std::string> isInteger(std::string line) {
  int now = currentIndex;
  if (!isdigit(line[now]))
    return {false, ""};
  std::string currentValue;
  while (now < line.size() && isdigit(line[now])) {
    currentValue += line[now++];
  }
  currentIndex = now;
  return {true, currentValue};
}

std::pair<bool, std::string> isOperator(std::string line) {
  std::string second = {line[currentIndex], line[currentIndex + 1]};
  auto it = std::find(operators.begin(), operators.end(), second);
  if (it != operators.end()) {
    currentIndex += 2;
    return {true, second};
  }
  std::string first = {line[currentIndex]};
  it = std::find(operators.begin(), operators.end(), first);
  if (it != operators.end()) {
    currentIndex++;
    return {true, first};
  }
  return {false, ""};
}

std::pair<bool, std::string> isComment(std::string line) {
  int now = currentIndex;
  if (line[now] != '#') {
    return {false, ""};
  }
  std::string currentValue = {line[now]};
  now++;
  while (now < line.size() && line[now] != '#') {
    currentValue += line[now++];
  }
  currentValue += "#";
  if (now < line.size()) {
    now++;
    currentIndex = now;
    return {true, currentValue};
  }
  return {false, currentValue};
}

Token scanner() {
  if (lineNumber >= inputData.size()) {
    return Token(tokenID::EndOfFile, tokenNames[tokenID::EndOfFile],
                 lineNumber);
  }
  if (currentIndex >= inputData[lineNumber].size()) {
    currentIndex = 0;
    lineNumber++;
    return scanner();
  }
  while (currentIndex < inputData[lineNumber].size() &&
         inputData[lineNumber][currentIndex] == ' ') {
    currentIndex++;
  }
  if (currentIndex >= inputData[lineNumber].size()) {
    currentIndex = 0;
    lineNumber++;
    return scanner();
  }
  auto identifierPair = isIdentifier(inputData[lineNumber]);
  if (identifierPair.first) {
    return Token(tokenID::Identifier, identifierPair.second, lineNumber);
  }
  auto keyWordPair = isKeyWord(inputData[lineNumber]);
  if (keyWordPair.first) {
    return Token(tokenID::Keyword, keyWordPair.second, lineNumber);
  }
  auto integerPair = isInteger(inputData[lineNumber]);
  if (integerPair.first) {
    return Token(tokenID::Integer, integerPair.second, lineNumber);
  }
  auto operatorPair = isOperator(inputData[lineNumber]);
  if (operatorPair.first) {
    return Token(tokenID::Operator, operatorPair.second, lineNumber);
  }
  auto commentPair = isComment(inputData[lineNumber]);
  if (commentPair.first) {
    return Token(tokenID::Comment, commentPair.second, lineNumber);
  }
  if (isupper(inputData[lineNumber][currentIndex])) {
    throw std::runtime_error("Invalid token! Identifier must start with a lowercase letter\n");
  }
  if (validChars.find(inputData[lineNumber][currentIndex]) == std::string::npos) {
    std::string msg = "\"";
    msg += inputData[lineNumber][currentIndex];
    msg += "\" is invalid character\n";
    throw std::runtime_error(msg);
  }
  currentIndex++;
  return Token(tokenID::InvalidToken, "", lineNumber);
}


void testScanner() {
  Token token = scanner();
  token.printToken();
  while (true) {
    token = scanner();
    if (token.tokenID == tokenID::EndOfFile) {
      token.printToken();
      break;
    }
    token.printToken();
  }
}