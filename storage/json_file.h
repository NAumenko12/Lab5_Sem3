#pragma once
#include <string>

#include "../struct/json.h"

using namespace std;

Json ReadJson(const string& filePath);
void WriteJson(const string& filePath, const Json& value);
