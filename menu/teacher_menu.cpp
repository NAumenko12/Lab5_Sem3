#include "teacher_menu.h"

#include <iostream>
#include <stdexcept>

#include "input.h"
#include "staff_actions.h"

using namespace std;

void TeacherMenu::PrintMenu(ostream& output) const {
  output << "\nМеню преподавателя\n"
         << "1. Добавить доклад\n"
         << "2. Добавить лабораторную работу\n"
         << "3. Утвердить запись на доклад\n"
         << "4. Проверить доклад\n"
         << "5. Проверить лабораторную работу\n"
         << "6. Показать оценки по предмету\n"
         << "7. Пользователи и предметы\n"
         << "0. Выйти из учетной записи\n";
}

bool TeacherMenu::RunAction(int action, int actor, GradeBook& book,istream& input, ostream& output) const {
  switch (action) {
    case 1:
    case 2: {
      string type = "report";
      if (action == 2) {
        type = "lab";
      }
      int subjectId = ReadNumber(input, output, "Номер предмета: ");
      string title = ReadText(input, output, "Тема работы: ");
      int workId = book.AddWork(actor, subjectId, type, title);
      output << "Номер работы: " << workId << '\n';
      return true;
    }
    case 3: {
      int workId = ReadNumber(input, output, "Номер доклада: ");
      int studentId = ReadNumber(input, output, "Номер студента: ");
      book.ApproveReport(actor, workId, studentId);
      return true;
    }
    case 4: {
      int workId = ReadNumber(input, output, "Номер доклада: ");
      int studentId = ReadNumber(input, output, "Номер студента: ");
      int grade = ReadNumber(input, output, "1 — сдано, 0 — не сдано: ");
      if (grade > 1) {
        throw runtime_error("Введите 1 или 0");
      }
      book.ReviewReport(actor, workId, studentId, grade == 1);
      return true;
    }
    case 5: {
      int workId = ReadNumber(input, output, "Номер лабораторной работы: ");
      int studentId = ReadNumber(input, output, "Номер студента: ");
      int grade = ReadNumber(input, output, "Балл 1–10 или 0 для отказа: ");
      book.ReviewLab(actor, workId, studentId, grade);
      return true;
    }
    case 6:
      output << book.SubjectResults(actor, ReadNumber(input, output, "Номер предмета: ")).ToJson()
             << '\n';
      return false;
    case 7:
      output << "\nПользователи и предметы\n";
      PrintStaffMenu(output);
      output << "0. Назад\n";
      return RunStaffAction(ReadNumber(input, output, "Действие: "), actor, book, input, output);
    default:
      throw runtime_error("Нет такого действия");
  }
}
