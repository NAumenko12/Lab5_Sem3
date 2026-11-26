#include "works.h"

#include <stdexcept>

using namespace std;

const Work& Works::Get(int workId) const {
  for (const Work& work : entries) {
    if (work.id == workId) {
      return work;
    }
  }
  throw runtime_error("Работа не найдена");
}

const vector<Work>& Works::GetAll() const { 
  return entries; 
}

const vector<Submission>& Works::GetSubmissions() const { 
  return submissions; 
}

bool Works::HasReportRegistration(int workId) const {
  for (const Submission& submission : submissions) {
    if (submission.workId == workId) {
      return true;
    }
  }
  return false;
}

size_t Works::FindSubmissionIndex(int workId, int studentId) const {
  for (size_t i = 0; i < submissions.size(); ++i) {
    const Submission& submission = submissions[i];
    if (submission.workId == workId && submission.studentId == studentId) {
      return i;
    }
  }
  return submissions.size();
}

const Submission* Works::FindSubmission(int workId, int studentId) const {
  size_t index = FindSubmissionIndex(workId, studentId);
  if (index == submissions.size()) {
    return nullptr;
  }
  return &submissions[index];
}

Submission& Works::GetSubmission(int workId, int studentId) {
  size_t index = FindSubmissionIndex(workId, studentId);
  if (index == submissions.size()) {
    throw runtime_error("Заявка студента не найдена");
  }
  return submissions[index];
}

int Works::Add(int subjectId, const string& type, const string& title) {
  if (type != "report" && type != "lab") {
    throw runtime_error("Неизвестный тип работы: " + type);
  }
  int id = entries.size() + 1;
  entries.push_back({id, subjectId, type, title});
  return id;
}

void Works::RegisterReport(const Work& work, int studentId) {
  if (work.type != "report") {
    throw runtime_error("Укажите номер доклада");
  }
  if (HasReportRegistration(work.id)) {
    throw runtime_error("Доклад уже занят");
  }
  submissions.push_back({work.id, studentId, "requested", 0});
}

void Works::CancelReport(const Work& work, int studentId) {
  size_t index = FindSubmissionIndex(work.id, studentId);
  if (index == submissions.size()) {
    throw runtime_error("Запись на доклад не найдена");
  }
  const Submission& submission = submissions[index];
  if (work.type != "report" || submission.status != "requested") {
    throw runtime_error(
        "Отменить можно только неутвержденную запись на доклад");
  }
  submissions.erase(submissions.begin() + index);
}

void Works::ApproveReport(const Work& work, int studentId) {
  Submission& submission = GetSubmission(work.id, studentId);
  if (work.type != "report" || submission.status != "requested") {
    throw runtime_error("Ожидается заявка на регистрацию доклада");
  }
  submission.status = "registered";
}

void Works::SubmitWork(const Work& work, int studentId, const string& type) {
  if (work.type != type) {
    throw runtime_error("Указан номер работы другого типа");
  }
  size_t index = FindSubmissionIndex(work.id, studentId);
  if (index == submissions.size()) {
    if (type == "report") {
      throw runtime_error("Сначала запишитесь на доклад");
    }
    submissions.push_back({work.id, studentId, "submitted", 0});
    return;
  }
  Submission& submission = submissions[index];
  if (submission.status != "registered" && submission.status != "rejected") {
    throw runtime_error("Работа недоступна для сдачи");
  }
  submission.status = "submitted";
  submission.grade = 0;
}

void Works::ReviewReport(const Work& work, int studentId, bool passed) {
  Submission& submission = GetSubmission(work.id, studentId);
  if (work.type != "report" || submission.status != "submitted") {
    throw runtime_error("Ожидается доклад, отправленный на проверку");
  }
  submission.status = "rejected";
  if (passed) {
    submission.status = "accepted";
  }
}

void Works::ReviewLab(const Work& work, int studentId, int grade) {
  Submission& submission = GetSubmission(work.id, studentId);
  if (work.type != "lab" || submission.status != "submitted") {
    throw runtime_error("Ожидается лабораторная, отправленная на проверку");
  }
  if (grade < 0 || grade > 10) {
    throw runtime_error("Введите балл от 1 до 10 или 0 для отказа");
  }
  submission.status = "rejected";
  if (grade > 0) {
    submission.status = "accepted";
  }
  submission.grade = grade;
}

void Works::RestoreSubmission(const Work& work, const Submission& submission) {
  if (FindSubmission(submission.workId, submission.studentId) != nullptr) {
    throw runtime_error("Повторная запись о сдаче");
  }
  if (work.type == "report" && HasReportRegistration(submission.workId)) {
    throw runtime_error("На доклад записано несколько студентов");
  }
  if (work.type == "lab" &&
      (submission.status == "requested" || submission.status == "registered")) {
    throw runtime_error("Неверный статус лабораторной");
  }

  bool acceptedLab = work.type == "lab" && submission.status == "accepted";
  if (acceptedLab && (submission.grade < 1 || submission.grade > 10)) {
    throw runtime_error("Неверный балл лабораторной");
  }
  if (!acceptedLab && submission.grade != 0) {
    throw runtime_error("Неверный балл работы");
  }
  submissions.push_back(submission);
}
