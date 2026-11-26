#pragma once
#include <string>
#include <vector>

using namespace std;

struct User {
  int id = 0;
  string role = "student";
  string name;
};

const User& FindUserById(const vector<User>& users, int id);
string RoleName(const string& role);
