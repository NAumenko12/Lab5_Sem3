CXX = clang++
CPPFLAGS = -include struct/vector.cpp
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

TARGET = gradebook
EXPORT_TARGET = gradebook_export
SESSION_SOURCES = main.cpp commands/session.cpp \
                  menu/user_menu.cpp menu/admin_menu.cpp menu/teacher_menu.cpp \
                  menu/student_menu.cpp menu/staff_actions.cpp menu/input.cpp
EXPORT_SOURCES = export_main.cpp commands/export.cpp
COMMON_SOURCES = struct/grade_book.cpp struct/user.cpp struct/subjects.cpp struct/works.cpp \
                 struct/results.cpp struct/json.cpp \
                 storage/load.cpp storage/save.cpp storage/json_file.cpp \
                 parser/parser.cpp parser/helper.cpp parser/value_handlers.cpp
SESSION_HEADERS = commands/session.h menu/user_menu.h menu/admin_menu.h menu/teacher_menu.h \
                  menu/student_menu.h menu/staff_actions.h menu/input.h
EXPORT_HEADERS = commands/export.h
COMMON_HEADERS = struct/grade_book.h struct/user.h struct/subjects.h struct/works.h \
                 struct/results.h struct/json.h struct/vector.h \
                 storage/json_file.h parser/parser.h parser/helper.h parser/value_handlers.h
SOURCES = $(SESSION_SOURCES) $(EXPORT_SOURCES) $(COMMON_SOURCES)
HEADERS = $(SESSION_HEADERS) $(EXPORT_HEADERS) $(COMMON_HEADERS)

all: $(TARGET) $(EXPORT_TARGET)

$(TARGET): $(SESSION_SOURCES) $(COMMON_SOURCES) $(SESSION_HEADERS) $(COMMON_HEADERS) struct/vector.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SESSION_SOURCES) $(COMMON_SOURCES) -o $@

$(EXPORT_TARGET): $(EXPORT_SOURCES) $(COMMON_SOURCES) $(EXPORT_HEADERS) $(COMMON_HEADERS) struct/vector.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(EXPORT_SOURCES) $(COMMON_SOURCES) -o $@

format:
	clang-format --style=Google --dry-run --Werror $(SOURCES) $(HEADERS) struct/vector.cpp

lint:
	cppcheck --std=c++17 --enable=warning,performance,portability --error-exitcode=1 \
		--include=struct/vector.cpp $(SOURCES)

clean:
	rm -f $(TARGET) $(EXPORT_TARGET)

.PHONY: all format lint clean
