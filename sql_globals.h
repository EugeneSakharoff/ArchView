#ifndef SQL_GLOBALS_H
#define SQL_GLOBALS_H

#include <QtGlobal>
#include <QPair>
#include <QString>
#include <QMap>
#include <QDebug>
#include "globals.h"

typedef  QPair<QString,QPair<QString,QString>> join_t;

namespace SQL_GLOBALS {
extern QString VALUES_TABLE;
extern QString DESCRIPTIONS_TABLE;
extern QString MESSAGES_TABLE;
extern QString GROUPS_TABLE;

extern QString ID_COLUMN;           //колонка первичного ключа (одинакова для всех таблиц)
extern QString VARID_COLUMN;        //колонка идентификатора переменной в таблице значений
extern QString NAME_COLUMN;         //имя переменной
extern QString DESCRIPTION_COLUMN;  //описание переменной
extern QString UNITS_COLUMN;        //единицы измерения
extern QString GROUPID_COLUMN;      //группа переменной
extern QString DATETIME_COLUMN;     //время изменения
extern QString PRECISION_COLUMN;    //точность пердставления
extern QString VALUE_COLUMN;        //значение
extern QString MESSAGE_COLUMN;      //текст сообщения

//псевдонимы для столбцов
extern QString ALIAS_ID;
extern QString ALIAS_VARID;
extern QString ALIAS_VARNAME;
extern QString ALIAS_DESCR;
extern QString ALIAS_UNITS;
extern QString ALIAS_GROUPID;
extern QString ALIAS_GROUPNAME;
extern QString ALIAS_DATETIME;
extern QString ALIAS_DATE;
extern QString ALIAS_TIME;
extern QString ALIAS_PRECISION;
extern QString ALIAS_VALUE;
extern QString ALIAS_VALUE_RAW;

extern QString HEADER_ID;
extern QString HEADER_VARID;
extern QString HEADER_VARNAME;
extern QString HEADER_DESCR;
extern QString HEADER_UNITS;
extern QString HEADER_GROUPNAME;
extern QString HEADER_DATETIME;
extern QString HEADER_DATE;
extern QString HEADER_TIME;
extern QString HEADER_PRECISION;
extern QString HEADER_VALUE;
extern QString HEADER_VALUE_RAW;

//выражения на SQL, получающие определенный столбец определенной таблицы
extern QString VALUES_ID;
extern QString DESCRIPTIONS_ID;
extern QString GROUPS_ID;
extern QString VARID;
extern QString VARNAME;
extern QString GROUPNAME;
extern QString VARDESCR;
extern QString UNITS;
extern QString GROUPID;
extern QString DATETIME;
extern QString PRECISION;
extern QString VALUE;
extern QString MESSAGE;

//выражения для получения столбцов с псевдонимами и доп. опциями
extern QString SEL_ID;
extern QString SEL_VARID;
extern QString SEL_VARNAME;
extern QString SEL_VARDESCR;
extern QString SEL_UNITS;
extern QString SEL_GROUPNAME;
extern QString SEL_DATETIME;
extern QString SEL_DATE;
extern QString SEL_TIME;
extern QString SEL_PRECISION;
extern QString SEL_VALUE_RAW;
extern QString SEL_VALUE_ROUNDED;
extern QString SEL_VALUE_WITH_UNIT;
extern QString SEL_MESSAGE;

//шаблоны запросов
extern join_t VALS_DESCR_JOIN;
extern join_t EMPTY_JOIN;

//заголовки столбцов в таблице (каждому столбцу из БД соответствует название)
extern QMap<QString, QString> HEADERS_MAP;

//сопоставление стлбцов vals->messages, чтобы корректно выполнялся union
extern QMap<QString, QString> VALS_MSGS_UNION_MAP;

//значения для запросов по умолчанию
extern QStringList DEFAULT_VALS_ITEMS;
extern QStringList DEFAULT_ALIASES;
extern QStringList DEFAULT_PLOT_ITEMS;
extern QStringList DEFAULT_HIDDEN_COLUMNS;
}

QStringList buildMessageItems(QStringList valsItems);
QString getAliasFromHeader(QString header);




#endif // SQL_GLOBALS_H
