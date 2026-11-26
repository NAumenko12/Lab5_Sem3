#include "helper.h"

#include <stdexcept>
using namespace std;

void ParserHelper::SkipSpaces(const string& text, size_t& curPos) const {
  while (curPos < text.size() &&(text[curPos] == ' ' || text[curPos] == '\n' || text[curPos] == '\t' || text[curPos] == '\r')) {
    ++curPos;
  }
}
bool ParserHelper::IsReadChar(const string& text, size_t& curPos, char expectedChar) const {
  SkipSpaces(text, curPos);
  if (curPos >= text.size() || text[curPos] != expectedChar) {
    return false;
  }
  ++curPos;
  return true;
}

char ParserHelper::ParseEscapeChar(const string& text, size_t& curPos) const {
  if (curPos >= text.size()) {
    throw runtime_error("После обратного слеша ожидался символ");
  }
  char escChar = text[curPos];
  ++curPos;
  switch (escChar) {
    case '"':
    case '\\':
    case '/':
      return escChar;  // ? под вопросом
    case 'n':
      return '\n';
    case 'r':
      return '\r';
    case 't':
      return '\t';
    case 'b':
      return '\b';
    case 'f':
      return '\f';
    default:
      throw runtime_error(
          "Неизвестная последовательность после обратного слеша");
  }
}

bool ParserHelper::IsDigit(char curChar) const {
  return curChar >= '0' && curChar <= '9';
}

bool ParserHelper::IsReadWord(const string& text, size_t& curPos, const string& word) const {
  if (text.compare(curPos, word.size(), word) != 0) {
    return false;
  }
  curPos += word.size();
  return true;
}