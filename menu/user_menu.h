#pragma once
#include <iosfwd>

#include "../struct/grade_book.h"

using namespace std;

class UserMenu {
 private:
  virtual void PrintMenu(ostream& output) const = 0;
  virtual bool RunAction(int action, int actor, GradeBook& book, istream& input,ostream& output) const = 0;

 public:
  virtual ~UserMenu();
  void Run(int actor, GradeBook& book, const string& filePath, istream& input,ostream& output) const;
};
