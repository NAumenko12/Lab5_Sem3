#include "parser.h"

#include <stdexcept>

#include "value_handlers.h"

using namespace std;

Json Parser::Parse(const string& text) const {
  size_t curPos = 0;
  Json value = ParseValue(text, curPos);
  helper.SkipSpaces(text, curPos);
  if (curPos != text.size()) {
    throw runtime_error("Лишние символы json");
  }
  return value;
}

Json Parser::ParseValue(const string& text, size_t& curPos) const {
  helper.SkipSpaces(text, curPos);
  if (curPos >= text.size()) {
    throw runtime_error("Ожидалось значение json");
  }
  ValueChain chain;
  return chain.Handle(*this, text, curPos);
}

string Parser::ParseStr(const string& text, size_t& curPos) const {
  if (curPos >= text.size() || text[curPos] != '"') {
    throw runtime_error("Ожидалась кавычка");
  }
  ++curPos;
  string parsdStr;
  while (curPos < text.size() && text[curPos] != '"') {
    char curChar = text[curPos];
    ++curPos;
    if (curChar >= 0 && curChar < 32) {
      throw runtime_error("Управляющий символ внутри JSON-строки");
    }

    if (curChar == '\\') {
      char parsdChar = helper.ParseEscapeChar(text, curPos);
      parsdStr.push_back(parsdChar);
    } else {
      parsdStr.push_back(curChar);
    }
  }
  if (curPos == text.size()) {
    throw runtime_error("Нет кавычки");
  }
  ++curPos;
  return parsdStr;
}

Json Parser::ParseObject(const string& text, size_t& curPos) const {
  if (!helper.IsReadChar(text, curPos, '{')) {
    throw runtime_error("Ожидалась {");
  }

  Json object("object");
  if (helper.IsReadChar(text, curPos, '}')) {
    return object;
  }

  do {
    helper.SkipSpaces(text, curPos);
    string name = ParseStr(text, curPos);
    if (!helper.IsReadChar(text, curPos, ':')) {
      throw runtime_error("Ожидалось :");
    }
    helper.SkipSpaces(text, curPos);
    Json field = ParseValue(text, curPos);
    field.SetName(name);
    object.AddField(field);
  } while (helper.IsReadChar(text, curPos, ','));

  if (!helper.IsReadChar(text, curPos, '}')) {
    throw runtime_error("Ожидалась }");
  }
  return object;
}

Json Parser::ParseNumber(const string& text, size_t& curPos) const {
  size_t startPos = curPos;
  if (curPos < text.size() && text[curPos] == '-') {
    ++curPos;
  }
  size_t digitStart = curPos;
  while (curPos < text.size() && helper.IsDigit(text[curPos])) {
    ++curPos;
  }
  if (curPos == digitStart) {
    throw runtime_error("Ожидалась цифра");
  }
  if (curPos - digitStart > 1 && text[digitStart] == '0') {
    throw runtime_error("Лишний ноль в начале числа");
  }
  if (curPos < text.size() && text[curPos] == '.') {
    ++curPos;
    if (curPos >= text.size() || !helper.IsDigit(text[curPos])) {
      throw runtime_error("После точки ожидалась цифра");
    }
    while (curPos < text.size() && helper.IsDigit(text[curPos])) {
      ++curPos;
    }
  }
  string data = text.substr(startPos, curPos - startPos);
  return Json("number", "", data);
}

Json Parser::ParseArray(const string& text, size_t& curPos) const {
  if (!helper.IsReadChar(text, curPos, '[')) {
    throw runtime_error("Ожидалась [");
  }
  Json arrayValue("array");
  if (helper.IsReadChar(text, curPos, ']')) {
    return arrayValue;
  }
  do {
    Json element = ParseValue(text, curPos);
    arrayValue.AddElement(element);
  } while (helper.IsReadChar(text, curPos, ','));
  if (!helper.IsReadChar(text, curPos, ']')) {
    throw runtime_error("Ожидалась ]");
  }
  return arrayValue;
}

void Parser::ParseWord(const string& text, size_t& curPos,
                       const string& word) const {
  if (!helper.IsReadWord(text, curPos, word)) {
    throw runtime_error("Ожидалось слово " + word);
  }
}
