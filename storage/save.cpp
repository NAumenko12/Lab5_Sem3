#include "../struct/grade_book.h"
#include "json_file.h"

Json MakeIds(const string& name, const vector<int>& ids) {
  Json value("array", name);
  for (int id : ids) {
    value.AddElement(Json("number", "", to_string(id)));
  }
  return value;
}

void GradeBook::Save(const string& filePath) const {
  Json usersJson("array", "users");
  for (const User& user : users) {
    Json entry("object");
    entry.AddField(Json("number", "id", to_string(user.id)));
    entry.AddField(Json("string", "name", user.name));
    entry.AddField(Json("string", "role", user.role));
    usersJson.AddElement(entry);
  }
  Json subjectsJson("array", "subjects");
  for (const Subject& subject : subjects.GetAll()) {
    Json entry("object");
    entry.AddField(Json("number", "id", to_string(subject.id)));
    entry.AddField(Json("string", "name", subject.name));
    entry.AddField(MakeIds("teachers", subject.teachers));
    entry.AddField(MakeIds("students", subject.students));
    subjectsJson.AddElement(entry);
  }
  Json worksJson("array", "works");
  for (const Work& work : works.GetAll()) {
    Json entry("object");
    entry.AddField(Json("number", "id", to_string(work.id)));
    entry.AddField(Json("number", "subjectId", to_string(work.subjectId)));
    entry.AddField(Json("string", "type", work.type));
    entry.AddField(Json("string", "title", work.title));
    worksJson.AddElement(entry);
  }
  Json submissionsJson("array", "submissions");
  for (const Submission& submission : works.GetSubmissions()) {
    Json entry("object");
    entry.AddField(Json("number", "workId", to_string(submission.workId)));
    entry.AddField(
        Json("number", "studentId", to_string(submission.studentId)));
    entry.AddField(Json("string", "status", submission.status));
    entry.AddField(Json("number", "grade", to_string(submission.grade)));
    submissionsJson.AddElement(entry);
  }

  Json database("object");
  database.AddField(usersJson);
  database.AddField(subjectsJson);
  database.AddField(worksJson);
  database.AddField(submissionsJson);
  WriteJson(filePath, database);
}
