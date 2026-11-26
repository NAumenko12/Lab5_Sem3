#include <stdexcept>
#include <utility>

#include "../struct/grade_book.h"
#include "json_file.h"

using namespace std;

const Json& ReadField(const Json& object, const string& name, const string& type) {
  const Json* field = object.FindField(name);
  if (field == nullptr || field->GetType() != type) {
    throw runtime_error("Неверное поле в журнале: " + name);
  }
  return *field;
}

const Vector<Json>& ReadArray(const Json& object, const string& name) {
  return ReadField(object, name, "array").GetElements();
}

int ReadInteger(const Json& value) {
  if (value.GetType() != "number") {
    throw runtime_error("Ожидалось целое число в журнале");
  }
  int number = stoi(value.GetData());
  if (to_string(number) != value.GetData()) {
    throw runtime_error("Ожидалось целое число в журнале");
  }
  return number;
}

int ReadIntField(const Json& object, const string& name) {
  return ReadInteger(ReadField(object, name, "number"));
}

void GradeBook::Load(const string& filePath) {
  Json database = ReadJson(filePath);
  GradeBook loaded;
  loaded.LoadUsers(ReadArray(database, "users"));
  loaded.LoadSubjects(ReadArray(database, "subjects"));
  loaded.LoadWorks(ReadArray(database, "works"));
  loaded.LoadSubmissions(ReadArray(database, "submissions"));
  *this = std::move(loaded);
}

void GradeBook::LoadUsers(const Vector<Json>& entries) {
  users.clear();
  for (size_t i = 0; i < entries.Size(); ++i) {
    const Json& entry = entries[i];
    int id = ReadIntField(entry, "id");
    const string& role = ReadField(entry, "role", "string").GetData();
    if (role != "admin" && role != "teacher" && role != "student") {
      throw runtime_error("Неизвестная роль: " + role);
    }
    int expectedId = i + 1;
    bool firstUserIsNotAdmin = id == 1 && role != "admin";
    bool extraAdmin = id != 1 && role == "admin";
    if (id != expectedId || firstUserIsNotAdmin || extraAdmin) {
      throw runtime_error("Неверный список пользователей журнала");
    }

    const string& name = ReadField(entry, "name", "string").GetData();
    users.push_back({id, role, name});
  }
  if (users.empty()) {
    throw runtime_error("Пользователь не найден");
  }
}

void GradeBook::LoadSubjects(const Vector<Json>& entries) {
  for (size_t i = 0; i < entries.Size(); ++i) {
    const Json& entry = entries[i];
    int id = ReadIntField(entry, "id");
    int expectedId = i + 1;
    if (id != expectedId) {
      throw runtime_error("Неверный номер предмета");
    }
    AddSubject(1, ReadField(entry, "name", "string").GetData());

    const Vector<Json>& teachers = ReadArray(entry, "teachers");
    for (size_t j = 0; j < teachers.Size(); ++j) {
      AssignUser(1, id, ReadInteger(teachers[j]), "teacher");
    }

    const Vector<Json>& students = ReadArray(entry, "students");
    for (size_t j = 0; j < students.Size(); ++j) {
      AssignUser(1, id, ReadInteger(students[j]), "student");
    }
  }
}

void GradeBook::LoadWorks(const Vector<Json>& entries) {
  for (size_t i = 0; i < entries.Size(); ++i) {
    const Json& entry = entries[i];
    int id = ReadIntField(entry, "id");
    int expectedId = i + 1;
    if (id != expectedId) {
      throw runtime_error("Неверный номер работы");
    }

    int subjectId = ReadIntField(entry, "subjectId");
    subjects.Get(subjectId);

    const string& type = ReadField(entry, "type", "string").GetData();

    const string& title = ReadField(entry, "title", "string").GetData();
    works.Add(subjectId, type, title);
  }
}

void GradeBook::LoadSubmissions(const Vector<Json>& entries) {
  for (size_t i = 0; i < entries.Size(); ++i) {
    const Json& entry = entries[i];
    int workId = ReadIntField(entry, "workId");
    int studentId = ReadIntField(entry, "studentId");
    const string& status = ReadField(entry, "status", "string").GetData();
    if (status != "requested" && status != "registered" && status != "submitted" && status != "accepted" && status != "rejected") {
      throw runtime_error("Неизвестный статус: " + status);
    }

    int grade = ReadIntField(entry, "grade");
    Submission submission{workId, studentId, status, grade};
    const Work& work = works.Get(workId);
    CheckStudent(studentId, subjects.Get(work.subjectId));
    works.RestoreSubmission(work, submission);
  }
}
