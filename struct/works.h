#pragma once
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

struct Work {
  int id = 0;
  int subjectId = 0;
  string type = "lab";
  string title;
};

struct Submission {
  int workId = 0;
  int studentId = 0;
  string status = "submitted";
  int grade = 0;
};

class Works {
 private:
  vector<Work> entries;
  vector<Submission> submissions;
  size_t FindSubmissionIndex(int workId, int studentId) const;
  Submission& GetSubmission(int workId, int studentId);
  bool HasReportRegistration(int workId) const;

 public:
  const Work& Get(int workId) const;
  const vector<Work>& GetAll() const;
  const vector<Submission>& GetSubmissions() const;
  const Submission* FindSubmission(int workId, int studentId) const;
  int Add(int subjectId, const string& type, const string& title);
  void RegisterReport(const Work& work, int studentId);
  void CancelReport(const Work& work, int studentId);
  void ApproveReport(const Work& work, int studentId);
  void SubmitWork(const Work& work, int studentId, const string& type);
  void ReviewReport(const Work& work, int studentId, bool passed);
  void ReviewLab(const Work& work, int studentId, int grade);
  void RestoreSubmission(const Work& work, const Submission& submission);
};
