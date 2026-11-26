#pragma once
#include <cstddef>
#include <string>

using namespace std;

class ParserHelper {
  friend class Parser;

 private:
  void SkipSpaces(const string& text, size_t& curPos) const;
  bool IsReadChar(const string& text, size_t& curPos, char expectedChar) const;
  char ParseEscapeChar(const string& text, size_t& curPos) const;
  bool IsDigit(char curChar) const;
  bool IsReadWord(const string& text, size_t& curPos, const string& word) const;
};