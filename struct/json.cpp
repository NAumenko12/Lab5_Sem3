#include "json.h"

Json::Json(const string& type, const string& name, const string& data)
    : type(type), name(name), data(data) {}

const string& Json::GetType() const { 
  return type; 
}

const string& Json::GetName() const { 
  return name; 
}

const string& Json::GetData() const { 
  return data; 
}

const Vector<Json>& Json::GetElements() const { 
  return elements; 
}

void Json::SetName(const string& fieldName) { 
  name = fieldName; 
}

void Json::AddField(const Json& field) {
  if (type != "object") {
    throw runtime_error("только в объект");
  }
  elements.PushBack(field);
}

void Json::AddElement(const Json& element) {
  if (type != "array") {
    throw runtime_error("только в массив");
  }
  elements.PushBack(element);
}

string Json::ContainerToJson(char openBracket, char closeBracket, size_t indent) const {
  string jsonText(1, openBracket);
  for (size_t i = 0; i < elements.Size(); ++i) {
    if (i > 0) {
      jsonText += ',';
    }
    jsonText += '\n';
    jsonText += string(indent + 2, ' ');
    const Json& element = elements[i];
    if (type == "object") {
      jsonText += QuoteString(element.GetName());
      jsonText += ": ";
    }
    jsonText += element.ToJson(indent + 2);
  }
  if (elements.Size() > 0) {
    jsonText += '\n';
    jsonText += string(indent, ' ');
  }

  jsonText += closeBracket;
  return jsonText;
}

string Json::ToJson(size_t indent) const {
  if (type == "string") {
    return QuoteString(data);
  }
  if (type == "number" || type == "boolean") {
    return data;
  }
  if (type == "null") {
    return "null";
  }
  if (type == "array") {
    return ContainerToJson('[', ']', indent);
  }
  if (type == "object") {
    return ContainerToJson('{', '}', indent);
  }
  throw runtime_error("Неизвестный тип  " + type);
}

const Json* Json::FindField(const string& fieldName) const {
  const Json* field = nullptr;
  if (type == "object") {
    for (size_t i = 0; i < elements.Size() && field == nullptr; ++i) {
      if (elements[i].GetName() == fieldName) {
        field = &elements[i];
      }
    }
  }
  return field;
}

string Json::QuoteString(const string& text) const {
  string jsonText;
  jsonText += '"';
  for (char curChar : text) {
    switch (curChar) {
      case '"':
      case '\\':
        jsonText += '\\';
        jsonText += curChar;
        break;
      case '\n':
        jsonText += "\\n";
        break;
      case '\r':
        jsonText += "\\r";
        break;
      case '\t':
        jsonText += "\\t";
        break;
      case '\b':
        jsonText += "\\b";
        break;
      case '\f':
        jsonText += "\\f";
        break;
      default:
        if (curChar >= 0 && curChar < 32) {
          throw runtime_error("Неподдерживаемый символ в json");
        }
        jsonText += curChar;
    }
  }
  jsonText += '"';
  return jsonText;
}
