#pragma once
#include <iosfwd>
#include <string>

using namespace std;

string ReadText(istream& input, ostream& output, const string& prompt);
int ReadNumber(istream& input, ostream& output, const string& prompt);
