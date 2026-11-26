#pragma once
#include <vector>

#include "json.h"
#include "subjects.h"
#include "user.h"
#include "works.h"

using namespace std;

class Results {
 private:
  Json MakeSubjectResults(const Subject& subject, const User& student,
                          const Works& works) const;

 public:
  Json ForSubject(const Subject& subject, const Works& works,
                  const vector<User>& users) const;
  Json ForStudent(const User& student, const Subjects& subjects,
                  const Works& works) const;
  Json ForAll(const Subjects& subjects, const Works& works,
              const vector<User>& users) const;
};
