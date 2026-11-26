#include "export.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "../storage/json_file.h"
#include "../struct/grade_book.h"

using namespace std;

void ExportResults(const string& filePath, const string& resultsPath, ostream& output){
  if (filesystem::exists(resultsPath) && filesystem::equivalent(filePath, resultsPath)){
    throw runtime_error("Укажите отдельный файл для выгрузки");
  }
  GradeBook book;
  book.Load(filePath);
  WriteJson(resultsPath, book.AllResults());
  output << "Итоги сохранены в " << resultsPath << '\n';
}
