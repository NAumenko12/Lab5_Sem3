#include "staff_actions.h"

#include <iostream>
#include <stdexcept>

#include "input.h"

using namespace std;

void PrintStaffMenu(ostream& output) {
  output << "\n1. Добавить преподавателя\n"
         << "2. Добавить студента\n"
         << "3. Добавить предмет\n"
         << "4. Назначить преподавателя на предмет\n"
         << "5. Назначить студента на предмет\n"
         << "6. Показать пользователей и предметы\n";
}

void PrintDirectory(const GradeBook& book, ostream& output) {
  output << "\nПользователи\n";
  for (const User& user : book.GetUsers()) {
    output << user.id << ". " << user.name << " (" << RoleName(user.role)<< ")\n";
  }
  output << "\nПредметы\n";
  for (const Subject& subject : book.GetSubjects()) {
    output << subject.id << ". " << subject.name << '\n';
  }
}

bool RunStaffAction(int action, int actor, GradeBook& book, istream& input,ostream& output) {
  switch (action) {
    case 0:
      return false;
    case 1:
    case 2: {
      string role = "teacher";
      if (action == 2) {
        role = "student";
      }
      string name = ReadText(input, output, "Имя пользователя: ");
      int userId = book.AddUser(actor, role, name);
      output << "Номер пользователя: " << userId << '\n';
      return true;
    }
    case 3: {
      string name = ReadText(input, output, "Название предмета: ");
      int subjectId = book.AddSubject(actor, name);
      output << "Номер предмета: " << subjectId << '\n';
      return true;
    }
    case 4:
    case 5: {
      string role = "teacher";
      if (action == 5) {
        role = "student";
      }
      int subjectId = ReadNumber(input, output, "Номер предмета: ");
      int userId = ReadNumber(input, output, "Номер пользователя: ");
      book.AssignUser(actor, subjectId, userId, role);
      return true;
    }
    case 6:
      PrintDirectory(book, output);
      return false;
    default:
      throw runtime_error("Нет такого действия");
  }
}
