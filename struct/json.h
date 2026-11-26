#pragma once
#include <string>

#include "vector.h"
using namespace std;

class Json {
 private:
  string type;
  string name;
  string data;
  Vector<Json> elements;
  string QuoteString(const string& text) const;
  string ContainerToJson(char openBracket, char closeBracket,size_t indent) const;

 public:
  Json(const string& type = "null", const string& name = "",const string& data = "");
  const string& GetType() const;
  const string& GetName() const;
  const string& GetData() const;
  const Vector<Json>& GetElements() const;
  void AddField(const Json& field);
  void AddElement(const Json& element);
  void SetName(const string& fieldName);
  string ToJson(size_t indent = 0) const;
  const Json* FindField(const string& fieldName) const;
};