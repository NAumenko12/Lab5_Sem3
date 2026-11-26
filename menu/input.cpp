#include "input.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

string ReadText(istream& input, ostream& output, const string& prompt) {
  output << prompt << flush;
  string text;
  if (!getline(input, text)) {
    throw runtime_error("Ввод завершен");
  }
  if (text.find_first_not_of(" \t\r") == string::npos) {
    throw runtime_error("Введите значение");
  }
  return text;
}

int ReadNumber(istream& input, ostream& output, const string& prompt) {
  istringstream line(ReadText(input, output, prompt));
  int number;
  char extraChar;
  if (!(line >> number) || (line >> extraChar) || number < 0) {
    throw runtime_error("Введите целое число от 0");
  }
  return number;
}
