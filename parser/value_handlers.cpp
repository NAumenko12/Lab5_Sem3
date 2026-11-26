#include "value_handlers.h"

#include <stdexcept>

#include "parser.h"

using namespace std;

ValueHandler* ValueHandler::setNext(ValueHandler* nextHandler) {
  next = nextHandler;
  return nextHandler;
}

Json ValueHandler::Handle(const Parser& parser, const string& text,size_t& curPos) const {
  if (next != nullptr) {
    return next->Handle(parser, text, curPos);
  }
  throw runtime_error("Неизвестное значение json");
}

Json ObjectHandler::Handle(const Parser& parser, const string& text, size_t& curPos) const {
  if (text[curPos] == '{') {
    return parser.ParseObject(text, curPos);
  }
  return ValueHandler::Handle(parser, text, curPos);
}

Json ArrayHandler::Handle(const Parser& parser, const string& text,size_t& curPos) const {
  if (text[curPos] == '[') {
    return parser.ParseArray(text, curPos);
  }
  return ValueHandler::Handle(parser, text, curPos);
}

Json StringHandler::Handle(const Parser& parser, const string& text,size_t& curPos) const {
  if (text[curPos] == '"') {
    return Json("string", "", parser.ParseStr(text, curPos));
  }
  return ValueHandler::Handle(parser, text, curPos);
}

Json NumberHandler::Handle(const Parser& parser, const string& text,size_t& curPos) const {
  char curChar = text[curPos];
  if (curChar == '-' || (curChar >= '0' && curChar <= '9')) {
    return parser.ParseNumber(text, curPos);
  }

  return ValueHandler::Handle(parser, text, curPos);
}

WordHandler::WordHandler(const string& wordText, const string& wordType): wordText(wordText), wordType(wordType) {}

Json WordHandler::Handle(const Parser& parser, const string& text,size_t& curPos) const {
  if (text[curPos] != wordText[0]) {
    return ValueHandler::Handle(parser, text, curPos);
  }
  parser.ParseWord(text, curPos, wordText);
  if (wordType == "null") {
    return Json("null");
  }
  return Json(wordType, "", wordText);
}

ValueChain::ValueChain() {
  objectHandler.setNext(&arrayHandler)
      ->setNext(&stringHandler)
      ->setNext(&numberHandler)
      ->setNext(&trueHandler)
      ->setNext(&falseHandler)
      ->setNext(&nullHandler);
}

Json ValueChain::Handle(const Parser& parser, const string& text,size_t& curPos) const {
  return objectHandler.Handle(parser, text, curPos);
}