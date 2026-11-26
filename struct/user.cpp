#include "user.h"

#include <stdexcept>

using namespace std;

const User& FindUserById(const vector<User>& users, int id) {
  for (const User& user : users) {
    if (user.id == id) {
      return user;
    }
  }
  throw runtime_error("Пользователь не найден");
}

string RoleName(const string& role) {
  if (role == "admin") {
    return "Суперпользователь";
  }
  if (role == "teacher") {
    return "Преподаватель";
  }
  if (role == "student") {
    return "Студент";
  }
  throw runtime_error("Неизвестный тип: " + role);
}
