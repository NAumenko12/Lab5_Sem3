#pragma once
#include <cstddef>
#include <string>

#include "../struct/json.h"
#include "helper.h"

using namespace std;

class Parser {
 private:
  friend class ObjectHandler;
  friend class ArrayHandler;
  friend class StringHandler;
  friend class NumberHandler;
  friend class WordHandler;
  ParserHelper helper;
  Json ParseValue(const string& text, size_t& curPos) const;
  Json ParseNumber(const string& text, size_t& curPos) const;
  string ParseStr(const string& text, size_t& curPos) const;
  Json ParseObject(const string& text, size_t& curPos) const;
  Json ParseArray(const string& text, size_t& curPos) const;
  void ParseWord(const string& text, size_t& curPos, const string& word) const;

 public:
  Json Parse(const string& text) const;
};