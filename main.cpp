#include <iostream>
#include <stdexcept>

#include "commands/session.h"

using namespace std;

int main(int argC, char* argV[]) {
  try {
    if (argC > 2) {
      throw runtime_error("Запуск: ./gradebook [журнал.json]");
    }
    const char* filePath = "gradebook.json";
    if (argC == 2) {
      filePath = argV[1];
    }
    RunSession(filePath, cin, cout);
  } catch (const exception& error) {
    cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
