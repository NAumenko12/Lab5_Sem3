
#pragma once
#include <cstddef>
#include <string>

#include "../struct/json.h"
#include "parser.h"

using namespace std;

class ValueHandler {
 private:
  ValueHandler* next = nullptr;

 public:
  ValueHandler* setNext(ValueHandler* nextHandler);
  virtual Json Handle(const Parser& parser, const string& text, size_t& curPos) const;
};

class ObjectHandler : public ValueHandler {
 public:
  Json Handle(const Parser& parser, const string& text, size_t& curPos) const override;
};

class ArrayHandler : public ValueHandler {
 public:
  Json Handle(const Parser& parser, const string& text,size_t& curPos) const override;
};

class StringHandler : public ValueHandler {
 public:
  Json Handle(const Parser& parser, const string& text,size_t& curPos) const override;
};

class NumberHandler : public ValueHandler {
 public:
  Json Handle(const Parser& parser, const string& text,size_t& curPos) const override;
};

class WordHandler : public ValueHandler {
 private:
  string wordText;
  string wordType;

 public:
  WordHandler(const string& wordText, const string& wordType);
  Json Handle(const Parser& parser, const string& text,size_t& curPos) const override;
};

class ValueChain {
 private:
  ObjectHandler objectHandler;
  ArrayHandler arrayHandler;
  StringHandler stringHandler;
  NumberHandler numberHandler;
  WordHandler trueHandler{"true", "boolean"};
  WordHandler falseHandler{"false", "boolean"};
  WordHandler nullHandler{"null", "null"};

 public:
  ValueChain();
  Json Handle(const Parser& parser, const string& text, size_t& curPos) const;
};