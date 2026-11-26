#pragma once
#include <iosfwd>

#include "../struct/grade_book.h"

using namespace std;

void PrintStaffMenu(ostream& output);
bool RunStaffAction(int action, int actor, GradeBook& book, istream& input,ostream& output);
