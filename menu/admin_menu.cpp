#include "admin_menu.h"

#include <iostream>

#include "staff_actions.h"

using namespace std;

void AdminMenu::PrintMenu(ostream& output) const {
  output << "\nМеню суперпользователя\n";
  PrintStaffMenu(output);
  output << "0. Выйти из учетной записи\n";
}

bool AdminMenu::RunAction(int action, int actor, GradeBook& book,istream& input, ostream& output) const {
  return RunStaffAction(action, actor, book, input, output);
}
