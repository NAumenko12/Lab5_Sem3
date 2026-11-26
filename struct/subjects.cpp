#include "subjects.h"

#include <stdexcept>

using namespace std;

size_t Subjects::FindIndex(int subjectId) const {
  for (size_t i = 0; i < entries.size(); ++i) {
    if (entries[i].id == subjectId) {
      return i;
    }
  }
  throw runtime_error("Предмет не найден");
}

const Subject& Subjects::Get(int subjectId) const {
  return entries[FindIndex(subjectId)];
}

const vector<Subject>& Subjects::GetAll() const { return entries; }

int Subjects::Add(const string& name, int teacherId) {
  int id = entries.size() + 1;
  Subject subject{id, name, {}, {}};
  if (teacherId > 0) {
    subject.teachers.push_back(teacherId);
  }
  entries.push_back(subject);
  return id;
}

void Subjects::AssignTeacher(int subjectId, int teacherId) {
  Subject& subject = entries[FindIndex(subjectId)];
  if (HasTeacher(subject, teacherId)) {
    throw runtime_error("Преподаватель уже назначен");
  }
  subject.teachers.push_back(teacherId);
}

void Subjects::AssignStudent(int subjectId, int studentId) {
  Subject& subject = entries[FindIndex(subjectId)];
  if (HasStudent(subject, studentId)) {
    throw runtime_error("Студент уже назначен");
  }
  subject.students.push_back(studentId);
}

bool Subjects::Contains(const vector<int>& ids, int id) const {
  for (int currentId : ids) {
    if (currentId == id) {
      return true;
    }
  }
  return false;
}

bool Subjects::HasTeacher(const Subject& subject, int teacherId) const {
  return Contains(subject.teachers, teacherId);
}

bool Subjects::HasStudent(const Subject& subject, int studentId) const {
  return Contains(subject.students, studentId);
}
