#include <iostream>
#include <stdexcept>

#include "commands/export.h"

using namespace std;

int main(int argC, char* argV[]) {
  try {
    if (argC != 3) {
      throw runtime_error("Запуск: ./gradebook_export журнал.json итоги.json");
    }
    ExportResults(argV[1], argV[2], cout);
  } catch (const exception& error) {
    cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
