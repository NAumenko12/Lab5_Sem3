#pragma once
#include <string>
#include <vector>

#include "results.h"
#include "subjects.h"
#include "user.h"
#include "works.h"

using namespace std;

class GradeBook {
 private:
  vector<User> users;
  Subjects subjects;
  Works works;
  Results results;

  void CheckTeacher(int actor, const Subject& subject) const;
  void CheckStudent(int actor, const Subject& subject) const;

  void LoadUsers(const Vector<Json>& entries);
  void LoadSubjects(const Vector<Json>& entries);
  void LoadWorks(const Vector<Json>& entries);
  void LoadSubmissions(const Vector<Json>& entries);

 public:
  GradeBook();
  const User& GetUser(int id) const;
  const vector<User>& GetUsers() const;
  const vector<Subject>& GetSubjects() const;
  int AddUser(int actor, const string& role, const string& name);
  int AddSubject(int actor, const string& name);
  void AssignUser(int actor, int subjectId, int userId, const string& role);
  int AddWork(int actor, int subjectId, const string& type, const string& title);
  void RegisterReport(int studentId, int workId);
  void CancelReport(int studentId, int workId);
  void ApproveReport(int teacherId, int workId, int studentId);
  void SubmitWork(int studentId, int workId, const string& type);
  void ReviewReport(int teacherId, int workId, int studentId, bool passed);
  void ReviewLab(int teacherId, int workId, int studentId, int grade);
  Json SubjectResults(int teacherId, int subjectId) const;
  Json StudentResults(int studentId) const;
  Json AllResults() const;
  void Load(const string& filePath);
  void Save(const string& filePath) const;
};
