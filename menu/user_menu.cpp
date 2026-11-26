#include "user_menu.h"

#include <iostream>
#include <stdexcept>

#include "input.h"

using namespace std;

UserMenu::~UserMenu() {}

void UserMenu::Run(int actor, GradeBook& book, const string& filePath,istream& input, ostream& output) const {
  while (input) {
    PrintMenu(output);
    bool changed = false;
    try {
      int action = ReadNumber(input, output, "Действие: ");
      if (action == 0) {
        return;
      }
      changed = RunAction(action, actor, book, input, output);
    } catch (const exception& error) {
      if (!input) {
        return;
      }
      output << "Ошибка: " << error.what() << '\n';
    }
    if (changed) {
      book.Save(filePath);
      output << "Журнал сохранен.\n";
    }
  }
}
