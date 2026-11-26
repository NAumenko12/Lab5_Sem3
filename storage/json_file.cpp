#include "json_file.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

#include "../parser/parser.h"

using namespace std;

Json ReadJson(const string& filePath) {
  ifstream file(filePath);
  if (!file) {
    throw runtime_error("Не удалось открыть журнал: " + filePath);
  }
  string text;
  string line;
  while (getline(file, line)) {
    text += line + '\n';
  }
  if (file.bad() || !file.eof()) {
    throw runtime_error("Не удалось прочитать журнал: " + filePath);
  }

  Parser parser;
  return parser.Parse(text);
}

void WriteJson(const string& filePath, const Json& value) {
  string text = value.ToJson() + '\n';
  filesystem::path directory = filesystem::path(filePath).parent_path();
  if (!directory.empty()) {
    filesystem::create_directories(directory);
  }
  filesystem::path tempDirectory(filePath + ".tmp");
  if (!filesystem::create_directory(tempDirectory)) {
    throw runtime_error("Временный каталог уже существует: " + tempDirectory.string());
  }
  filesystem::path tempPath = tempDirectory / "data.json";
  try {
    ofstream file(tempPath);
    if (!file) {
      throw runtime_error("Не удалось открыть файл для записи: " + filePath);
    }
    file << text;
    file.close();
    if (!file) {
      throw runtime_error("Не удалось записать файл: " + filePath);
    }
    filesystem::rename(tempPath, filePath);
  } catch (...) {
    error_code error;
    filesystem::remove(tempPath, error);
    filesystem::remove(tempDirectory, error);
    throw;
  }
  error_code error;
  filesystem::remove(tempDirectory, error);
}
