#include "results.h"

#include <stdexcept>

using namespace std;

string WorkTypeName(const string& type) {
  if (type == "report") {
    return "Доклад";
  }
  if (type == "lab") {
    return "Лабораторная";
  }
  throw runtime_error("Неизвестный тип работы");
}

string StatusName(const string& status) {
  if (status == "requested") {
    return "Ожидает регистрации";
  }
  if (status == "registered") {
    return "Регистрация утверждена";
  }
  if (status == "submitted") {
    return "На проверке";
  }
  if (status == "accepted") {
    return "Принято";
  }
  if (status == "rejected") {
    return "Отклонено";
  }
  throw runtime_error("Неизвестный тип: " + status);
}

Json Results::MakeSubjectResults(const Subject& subject, const User& student, const Works& works) const {
  Json result("object");
  result.AddField(Json("number", "subjectId", to_string(subject.id)));
  result.AddField(Json("string", "subject", subject.name));
  result.AddField(Json("number", "studentId", to_string(student.id)));
  result.AddField(Json("string", "student", student.name));

  int gradeSum = 0;
  int gradeCount = 0;
  Json workResults("array", "works");
  for (const Work& work : works.GetAll()) {
    if (work.subjectId != subject.id) {
      continue;
    }

    Json entry("object");
    entry.AddField(Json("number", "workId", to_string(work.id)));
    entry.AddField(Json("string", "title", work.title));
    entry.AddField(Json("string", "type", WorkTypeName(work.type)));
    const Submission* submission = works.FindSubmission(work.id, student.id);
    if (submission == nullptr) {
      entry.AddField(Json("string", "status", "Нет заявки"));
      entry.AddField(Json("null", "grade"));
    } else {
      entry.AddField(Json("string", "status", StatusName(submission->status)));
      Json grade("null", "grade");
      if (work.type == "lab" && submission->status == "accepted") {
        grade = Json("number", "grade", to_string(submission->grade));
        gradeSum += submission->grade;
        ++gradeCount;
      }
      if (work.type == "report" && submission->status == "accepted") {
        grade = Json("string", "grade", "сдано");
      }
      if (work.type == "report" && submission->status == "rejected") {
        grade = Json("string", "grade", "не сдано");
      }
      entry.AddField(grade);
    }
    workResults.AddElement(entry);
  }

  Json average("null", "labAverage");
  if (gradeCount > 0) {
    double value = gradeSum;
    value /= gradeCount;
    average = Json("number", "labAverage", to_string(value));
  }
  result.AddField(average);
  result.AddField(workResults);
  return result;
}

Json Results::ForSubject(const Subject& subject, const Works& works, const vector<User>& users) const {
  Json results("array");
  for (int studentId : subject.students) {
    const User& student = FindUserById(users, studentId);
    results.AddElement(MakeSubjectResults(subject, student, works));
  }
  return results;
}

Json Results::ForStudent(const User& student, const Subjects& subjects,const Works& works) const {
  Json results("array");
  for (const Subject& subject : subjects.GetAll()) {
    if (subjects.HasStudent(subject, student.id)) {
      results.AddElement(MakeSubjectResults(subject, student, works));
    }
  }
  return results;
}

Json Results::ForAll(const Subjects& subjects, const Works& works, const vector<User>& users) const {
  Json subjectsJson("array", "subjects");
  for (const Subject& subject : subjects.GetAll()) {
    Json subjectJson("object");
    subjectJson.AddField(Json("number", "id", to_string(subject.id)));
    subjectJson.AddField(Json("string", "name", subject.name));
    Json results = ForSubject(subject, works, users);
    results.SetName("results");
    subjectJson.AddField(results);
    subjectsJson.AddElement(subjectJson);
  }
  Json output("object");
  output.AddField(subjectsJson);
  return output;
}
