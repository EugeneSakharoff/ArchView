#ifndef TEST_TABLES_H
#define TEST_TABLES_H

#include "database.h"

namespace test_tables_structure {
extern bool create_test_tables_flag;

extern const QStringList NAMES;

//структура таблицы descriptions (описание переменных): id, имя_переменной, ед.изменеия, точность представления, группа
extern const QString DESCR_STRUCTURE;

//структура таблицы vals (изменения значений переменных): id, id_переменной, дата_и_время, значение, предыдущее значение
extern const QString VALUES_STRUCTURE;

//структура таблицы messages (сообщения): id, текст_сообщения, дата_и_время
extern const QString MESSAGES_STRUCTURE;

extern const QString GROUPS_STRUCTURE;
//структуры трех таблиц в одном массиве
extern const QStringList STRUCTURES;

//число переменных
extern int VALUES_NUM;
extern int GROUPS_NUM;

//единицы измерения
extern const QStringList UNITSLIST;

//максимальное значение переменных для случайной генерации(одно на всех)
extern const int MAX_VAL;
extern const int MAX_PRECISION;

//максимальное значение шага по времени в секундах для случайной генерации(одно на всех)
extern const int MAX_TIMESTEP_SEC;
extern QDateTime START_TIME;
}

/*
 * Модуль для создания трех тестовых таблиц и заполнения из значениями
 *
 */

//Создание таблиц
void create_test_tables(DataBase *db);

//Заполнение таблиц
void populate_test_tables(DataBase *db);

#endif // TEST_TABLES_H
