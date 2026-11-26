#include "grade_book.h"

#include <stdexcept>

using namespace std;

GradeBook::GradeBook() { 
  users.push_back({1, "admin", "Администратор"}); 
}

const User& GradeBook::GetUser(int id) const { 
  return FindUserById(users, id); 
}

const vector<User>& GradeBook::GetUsers() const { 
  return users; 
}

const vector<Subject>& GradeBook::GetSubjects() const {
  return subjects.GetAll();
}

void GradeBook::CheckTeacher(int actor, const Subject& subject) const {
  if (GetUser(actor).role != "teacher" || !subjects.HasTeacher(subject, actor)) {
    throw runtime_error("Преподаватель не назначен на этот предмет");
  }
}

void GradeBook::CheckStudent(int actor, const Subject& subject) const {
  if (GetUser(actor).role != "student" || !subjects.HasStudent(subject, actor)) {
    throw runtime_error("Студент не назначен на этот предмет");
  }
}

int GradeBook::AddUser(int actor, const string& role, const string& name) {
  if (GetUser(actor).role == "student" || (role != "teacher" && role != "student")) {
    throw runtime_error("Недостаточно прав для добавления пользователя");
  }
  int id = users.size() + 1;
  users.push_back({id, role, name});
  return id;
}

int GradeBook::AddSubject(int actor, const string& name) {
  const string& role = GetUser(actor).role;
  if (role == "student") {
    throw runtime_error("Студент не может добавлять предметы");
  }
  int teacherId = 0;
  if (role == "teacher") {
    teacherId = actor;
  }
  return subjects.Add(name, teacherId);
}

void GradeBook::AssignUser(int actor, int subjectId, int userId, const string& role) {
  const Subject& subject = subjects.Get(subjectId);
  if (GetUser(actor).role != "admin") {
    CheckTeacher(actor, subject);
  }
  if (role == "admin" || GetUser(userId).role != role) {
    throw runtime_error("Пользователь имеет другую роль");
  }
  if (role == "teacher") {
    subjects.AssignTeacher(subjectId, userId);
  } else {
    subjects.AssignStudent(subjectId, userId);
  }
}

int GradeBook::AddWork(int actor, int subjectId, const string& type, const string& title) {
  CheckTeacher(actor, subjects.Get(subjectId));
  return works.Add(subjectId, type, title);
}

void GradeBook::RegisterReport(int studentId, int workId) {
  const Work& work = works.Get(workId);
  CheckStudent(studentId, subjects.Get(work.subjectId));
  works.RegisterReport(work, studentId);
}

void GradeBook::CancelReport(int studentId, int workId) {
  const Work& work = works.Get(workId);
  CheckStudent(studentId, subjects.Get(work.subjectId));
  works.CancelReport(work, studentId);
}

void GradeBook::ApproveReport(int teacherId, int workId, int studentId) {
  const Work& work = works.Get(workId);
  CheckTeacher(teacherId, subjects.Get(work.subjectId));
  works.ApproveReport(work, studentId);
}

void GradeBook::SubmitWork(int studentId, int workId, const string& type) {
  const Work& work = works.Get(workId);
  CheckStudent(studentId, subjects.Get(work.subjectId));
  works.SubmitWork(work, studentId, type);
}

void GradeBook::ReviewReport(int teacherId, int workId, int studentId,bool passed) {
  const Work& work = works.Get(workId);
  CheckTeacher(teacherId, subjects.Get(work.subjectId));
  works.ReviewReport(work, studentId, passed);
}

void GradeBook::ReviewLab(int teacherId, int workId, int studentId, int grade) {
  const Work& work = works.Get(workId);
  CheckTeacher(teacherId, subjects.Get(work.subjectId));
  works.ReviewLab(work, studentId, grade);
}

Json GradeBook::SubjectResults(int teacherId, int subjectId) const {
  const Subject& subject = subjects.Get(subjectId);
  CheckTeacher(teacherId, subject);
  return results.ForSubject(subject, works, users);
}

Json GradeBook::StudentResults(int studentId) const {
  const User& student = GetUser(studentId);
  if (student.role != "student") {
    throw runtime_error("Ожидалась учетная запись студента");
  }
  return results.ForStudent(student, subjects, works);
}

Json GradeBook::AllResults() const {
  return results.ForAll(subjects, works, users);
}
