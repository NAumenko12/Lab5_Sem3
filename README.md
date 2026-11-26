# Lab5_Sem3

## Запуск

Из корня проекта с компилятором C++17 собери обе программы и открой журнал.

```bash
make
./gradebook lab5_demo.json
```

В меню выбери пользователя по номеру. Введи `0`, чтобы выйти из меню роли, и ещё раз `0`, чтобы закрыть журнал.

Выгрузка итогов по предметам запускается отдельно.

```bash
./gradebook_export lab5_demo.json lab5_results.json
```

## Где реализованы операции из ТЗ

Действия вызываются из меню [суперпользователя](menu/admin_menu.cpp#L15), [преподавателя](menu/teacher_menu.cpp#L23) и [студента](menu/student_menu.cpp#L20). Добавление пользователей, создание предметов и назначения проходят через [RunStaffAction](menu/staff_actions.cpp#L30). Преподаватель открывает эти действия через пункт `7`.

| Операция | Функции |
| --- | --- |
| Создать журнал с единственным суперпользователем | [GradeBook::GradeBook](struct/grade_book.cpp#L7), [GradeBook::LoadUsers](storage/load.cpp#L46) |
| Добавить преподавателя или студента | [GradeBook::AddUser](struct/grade_book.cpp#L35) |
| Добавить предмет и автоматически назначить на него преподавателя, который его создал | [GradeBook::AddSubject](struct/grade_book.cpp#L44), [Subjects::Add](struct/subjects.cpp#L22) |
| Назначить преподавателя на предмет | [GradeBook::AssignUser](struct/grade_book.cpp#L56), [Subjects::AssignTeacher](struct/subjects.cpp#L32) |
| Назначить студента на предмет | [GradeBook::AssignUser](struct/grade_book.cpp#L56), [Subjects::AssignStudent](struct/subjects.cpp#L40) |
| Добавить доклад или лабораторную по предмету | [GradeBook::AddWork](struct/grade_book.cpp#L71), [Works::Add](struct/works.cpp#L59) |
| Записаться на доклад | [GradeBook::RegisterReport](struct/grade_book.cpp#L76), [Works::RegisterReport](struct/works.cpp#L68) |
| Отменить запись на доклад до утверждения | [GradeBook::CancelReport](struct/grade_book.cpp#L82), [Works::CancelReport](struct/works.cpp#L78) |
| Утвердить запись на доклад | [GradeBook::ApproveReport](struct/grade_book.cpp#L88), [Works::ApproveReport](struct/works.cpp#L91) |
| Сдать доклад, сдать лабораторную или пересдать её после отказа | [GradeBook::SubmitWork](struct/grade_book.cpp#L94), [Works::SubmitWork](struct/works.cpp#L99) |
| Проверить доклад и выставить «сдано» или «не сдано» | [GradeBook::ReviewReport](struct/grade_book.cpp#L100), [Works::ReviewReport](struct/works.cpp#L119) |
| Принять лабораторную с баллом от 1 до 10 или отклонить её | [GradeBook::ReviewLab](struct/grade_book.cpp#L106), [Works::ReviewLab](struct/works.cpp#L130) |
| Показать преподавателю оценки всех студентов по предмету | [GradeBook::SubjectResults](struct/grade_book.cpp#L112), [Results::ForSubject](struct/results.cpp#L89) |
| Показать студенту его оценки по всем предметам | [GradeBook::StudentResults](struct/grade_book.cpp#L118), [Results::ForStudent](struct/results.cpp#L98) |
| Выгрузить итоги по предметам в JSON | [ExportResults](commands/export.cpp#L12), [GradeBook::AllResults](struct/grade_book.cpp#L126), [Results::ForAll](struct/results.cpp#L108), [WriteJson](storage/json_file.cpp#L29) |
