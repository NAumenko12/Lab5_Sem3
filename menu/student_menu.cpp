#include "student_menu.h"

#include <iostream>
#include <stdexcept>

#include "input.h"

using namespace std;

void StudentMenu::PrintMenu(ostream& output) const {
  output << "\nМеню студента\n"
         << "1. Записаться на доклад\n"
         << "2. Отменить запись на доклад\n"
         << "3. Отправить доклад на проверку\n"
         << "4. Отправить лабораторную на проверку\n"
         << "5. Показать мои работы и оценки по всем предметам\n"
         << "0. Выйти из учетной записи\n";
}

bool StudentMenu::RunAction(int action, int actor, GradeBook& book,istream& input, ostream& output) const {
  switch (action) {
    case 1:
      book.RegisterReport(actor, ReadNumber(input, output, "Номер доклада: "));
      return true;
    case 2:
      book.CancelReport(actor, ReadNumber(input, output, "Номер доклада: "));
      return true;
    case 3:
      book.SubmitWork(actor, ReadNumber(input, output, "Номер доклада: "),"report");
      return true;
    case 4:
      book.SubmitWork(actor, ReadNumber(input, output, "Номер лабораторной: "),"lab");
      return true;
    case 5:
      output << book.StudentResults(actor).ToJson() << '\n';
      return false;
    default:
      throw runtime_error("Нет такого действия");
  }
}
