#pragma once
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

struct Subject {
  int id = 0;
  string name;
  vector<int> teachers;
  vector<int> students;
};

class Subjects {
 private:
  vector<Subject> entries;
  size_t FindIndex(int subjectId) const;
  bool Contains(const vector<int>& ids, int id) const;

 public:
  const Subject& Get(int subjectId) const;
  const vector<Subject>& GetAll() const;
  int Add(const string& name, int teacherId);
  void AssignTeacher(int subjectId, int teacherId);
  void AssignStudent(int subjectId, int studentId);
  bool HasTeacher(const Subject& subject, int teacherId) const;
  bool HasStudent(const Subject& subject, int studentId) const;
};
