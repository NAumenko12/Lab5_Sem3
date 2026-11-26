#include "session.h"

#include <filesystem>
#include <iostream>

#include "../menu/admin_menu.h"
#include "../menu/input.h"
#include "../menu/student_menu.h"
#include "../menu/teacher_menu.h"

using namespace std;

void RunSession(const string& filePath, istream& input, ostream& output){
  GradeBook book;
  if (filesystem::exists(filePath)) {
    book.Load(filePath);
  } else {
    book.Save(filePath);
  }
  AdminMenu admin;
  TeacherMenu teacher;
  StudentMenu student;
  while (input) {
    output << "\nУчетные записи\n";
    for (const User& user : book.GetUsers()) {
      output << user.id << ". " << user.name << " (" << RoleName(user.role)<< ")\n";
    }
    const UserMenu* menu = nullptr;
    int actor = 0;
    try {
      actor = ReadNumber(input, output, "Номер пользователя (0 для выхода) ");
      if (actor == 0) {
        break;
      }
      const string& role = book.GetUser(actor).role;
      if (role == "admin") {
        menu = &admin;
      } else if (role == "teacher") {
        menu = &teacher;
      } else if (role == "student") {
        menu = &student;
      }
    } catch (const exception& error) {
      if (input) {
        output << "Ошибка: " << error.what() << '\n';
      }
    }
    if (menu != nullptr) {
      menu->Run(actor, book, filePath, input, output);
    }
  }
}
