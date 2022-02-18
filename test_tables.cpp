#include "test_tables.h"

/*
 * Модуль для создания трех тестовых таблиц и заполнения из значениями
 *
 */



namespace test_tables_structure {
using namespace SQL_GLOBALS;
bool create_test_tables_flag = false;

//имена таблиц
const QStringList NAMES = {DESCRIPTIONS_TABLE,VALUES_TABLE,MESSAGES_TABLE,GROUPS_TABLE};

//структура таблицы descriptions (описание переменных): id, имя_переменной, ед.изменеия, точность представления, группа
const QString DESCR_STRUCTURE = QString("(%1 serial primary key, "
                                         "%2 varchar(20) UNIQUE, "
                                         "%3 varchar(20), "
                                         "%4 smallint, "
                                         "%5 int, "
                                         "%6 varchar(100))").arg(ID_COLUMN,NAME_COLUMN,UNITS_COLUMN,PRECISION_COLUMN,GROUPID_COLUMN,DESCRIPTION_COLUMN);

//структура таблицы vals (изменения значений переменных): id, id_переменной, дата_и_время, значение, предыдущее значение
const QString VALUES_STRUCTURE = QString("(%1 serial primary key, "
                                          "%2 int , "
                                          "%3 timestamp, "
                                          "%4 float)").arg(ID_COLUMN,VARID_COLUMN,DATETIME_COLUMN,VALUE_COLUMN);

//структура таблицы messages (сообщения): id, текст_сообщения, дата_и_время
const QString MESSAGES_STRUCTURE = QString("(%1 serial primary key, "
                                            "%2 int, "
                                            "%3 varchar(256), "
                                            "%4 timestamp)").arg(ID_COLUMN,VARID_COLUMN,MESSAGE_COLUMN,DATETIME_COLUMN);

//структура таблицы messages (сообщения): id, текст_сообщения, дата_и_время
const QString GROUPS_STRUCTURE = QString("(%1 serial primary key, "
                                         "%2 varchar(256))").arg(ID_COLUMN,NAME_COLUMN);

//структуры трех таблиц в одном массиве
const QStringList STRUCTURES = {DESCR_STRUCTURE,VALUES_STRUCTURE,MESSAGES_STRUCTURE,GROUPS_STRUCTURE};

//число переменных
int VARIABLES_NUM = 10;
int VALUES_NUM = 100;
int MESSAGES_NUM = 20;
int GROUPS_NUM = 3;

const QStringList UNITSLIST = {"'В'","'А'","'кг/см"+QString(178)+"'","'"+QString(176)+"C'"};

//максимальное значение переменных для случайной генерации(одно на всех)
const int MAX_VAL = 1000;
const int MAX_PRECISION = 4;

//максимальное значение шага по времени в секундах для случайной генерации(одно на всех)
const int MAX_TIMESTEP_SEC = 100;
QDateTime START_TIME = QDateTime::currentDateTime();
}

using namespace  test_tables_structure;


//Создание таблиц
void create_test_tables(DataBase *db)
{
if (db->isConnected())
  {
  toDebug("Creating test tables...",DT_TRACE);
  for (int i = 0;i<NAMES.length(); i++)
    {
    toDebug("Creating: "+NAMES.at(i)+STRUCTURES.at(i),DT_TEST_TABLES);
    db->createTable(NAMES.at(i),STRUCTURES.at(i));

    }
  }
else
  toDebug("Unable to create test tables - DB not connected! ",DT_ERROR);
}


void populate_groups_table(DataBase *db)
{
auto randgroupname = [](int i){return QString("'group_%1'").arg(i);};
int i=db->countRows(GROUPS_TABLE);
toDebug(QString("Populating groups, current rows = %1, needed = %2").arg(i).arg(GROUPS_NUM),DT_TEST_TABLES);
while (i<GROUPS_NUM)
  {
  toDebug(randgroupname(i),DT_TEST_TABLES);
  db->insertValues(GROUPS_TABLE,{NAME_COLUMN},{randgroupname(i)});
  i++;
  }
}

//заполнение значениями таблицы descriptions
void populate_descriptions_table(DataBase *db)
{
auto randname = [](int i,int g){return QString("'variable_%1_group_%2'").arg(i).arg(g);};
auto randdescr = [](int i,int g){return QString("'Description of variable_%1 of group_%2'").arg(i).arg(g);};
auto randprec = [](){return QString::number(rand()%MAX_PRECISION);};
auto randunit = [](){return UNITSLIST.at(rand()%UNITSLIST.length());};

int i=db->countRows(DESCRIPTIONS_TABLE);
toDebug(QString("Populating descriptions, current rows = %1, needed = %2").arg(i).arg(VARIABLES_NUM),DT_TEST_TABLES);
int g;
while (i<VARIABLES_NUM)
   {
   g = (rand()%GROUPS_NUM);
   toDebug(randname(i,g),DT_TEST_TABLES);
   db->insertValues(DESCRIPTIONS_TABLE,
                    {NAME_COLUMN,UNITS_COLUMN,PRECISION_COLUMN,GROUPID_COLUMN,DESCRIPTION_COLUMN},
                    {randname(i,g),randunit(),randprec(),QString::number(g),randdescr(i,g)});
   i++;
   }
}

//заполнение случайными значениями таблицы vals. N - требуемое кол-во записей
void populate_values_table(DataBase *db, const int N)
{
auto randfloat = [](){return static_cast <double> (rand()) / static_cast <double> (MAX_VAL);}; //лямбда для генерации случайного float
QDateTime time = START_TIME;
toDebug(QString("Populating vals, current rows = %1, needed = %2").arg(db->countRows(VALUES_TABLE)).arg(N),DT_TEST_TABLES);
//пока количество записей меньше требуемого
while (db->countRows(VALUES_TABLE)<N)
  {
  time = time.addSecs(rand()%MAX_TIMESTEP_SEC);        //увеличиваем время на случайное кол-во секунд
  db->insertValues(VALUES_TABLE,
                   {VARID_COLUMN,DATETIME_COLUMN,VALUE_COLUMN},
                   {QString::number((rand()%VARIABLES_NUM)),"'"+time.toString(GLOBALS::DEFAULT_DATETIME_FORMAT)+"'",QString::number(randfloat())});

  }
}

//заполнение сообщениями таблицы messages. N - требуемое кол-во записей
void populate_messages_table(DataBase *db, const int N)
{
auto randmessage = [](int i){return "'Сообщение_"+QString::number(i)+": HTML обычный <b>жирный</b> <u>подчеркн</u>. '";};
auto randvarid = [](){return QString::number(rand()%VARIABLES_NUM);};
QDateTime time = START_TIME;
int i=db->countRows(MESSAGES_TABLE);
toDebug(QString("Populating messages, current rows = %1, needed = %2").arg(i).arg(N),DT_TEST_TABLES);
//пока количество записей меньше требуемого
while (i<N)
{
  time = time.addSecs(rand()%MAX_TIMESTEP_SEC*5);
  db->insertValues(MESSAGES_TABLE,
                   {VARID_COLUMN,MESSAGE_COLUMN,DATETIME_COLUMN},
                   {randvarid(),randmessage(i),"'"+time.toString(GLOBALS::DEFAULT_DATETIME_FORMAT)+"'"});
  i++;
}
}

//три предыдущие функции в одной
void populate_test_tables(DataBase *db)
{
toDebug("populating test tables",DT_TRACE);
populate_groups_table(db);
populate_descriptions_table(db);
populate_values_table(db,VALUES_NUM);
populate_messages_table(db,MESSAGES_NUM);
}
