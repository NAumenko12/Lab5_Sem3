#pragma once
#include "user_menu.h"

class StudentMenu : public UserMenu {
 private:
  void PrintMenu(ostream& output) const override;
  bool RunAction(int action, int actor, GradeBook& book, istream& input, ostream& output) const override;
};
