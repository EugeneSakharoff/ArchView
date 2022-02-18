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
extern const QString VALUES_TABLE;
extern const QString DESCRIPTIONS_TABLE;
extern const QString MESSAGES_TABLE;
extern const QString GROUPS_TABLE;

extern const QString ID_COLUMN;           //колонка первичного ключа (одинакова для всех таблиц)
extern const QString VARID_COLUMN;        //колонка идентификатора переменной в таблице значений
extern const QString NAME_COLUMN;         //имя переменной
extern const QString DESCRIPTION_COLUMN;  //описание переменной
extern const QString UNITS_COLUMN;        //единицы измерения
extern const QString GROUPID_COLUMN;      //группа переменной
extern const QString DATETIME_COLUMN;     //время изменения
extern const QString PRECISION_COLUMN;    //точность пердставления
extern const QString VALUE_COLUMN;        //значение
extern const QString MESSAGE_COLUMN;      //текст сообщения

//псевдонимы для столбцов
extern const QString ALIAS_ID;
extern const QString ALIAS_VARID;
extern const QString ALIAS_VARNAME;
extern const QString ALIAS_DESCR;
extern const QString ALIAS_UNITS;
extern const QString ALIAS_GROUPID;
extern const QString ALIAS_GROUPNAME;
extern const QString ALIAS_DATETIME;
extern const QString ALIAS_DATE;
extern const QString ALIAS_TIME;
extern const QString ALIAS_PRECISION;
extern const QString ALIAS_VALUE;
extern const QString ALIAS_VALUE_RAW;

extern const QString HEADER_ID;
extern const QString HEADER_VARID;
extern const QString HEADER_VARNAME;
extern const QString HEADER_DESCR;
extern const QString HEADER_UNITS;
extern const QString HEADER_GROUPNAME;
extern const QString HEADER_DATETIME;
extern const QString HEADER_DATE;
extern const QString HEADER_TIME;
extern const QString HEADER_PRECISION;
extern const QString HEADER_VALUE;
extern const QString HEADER_VALUE_RAW;

//выражения на SQL, получающие определенный столбец определенной таблицы
extern const QString VALUES_ID;
extern const QString DESCRIPTIONS_ID;
extern const QString GROUPS_ID;
extern const QString VARID;
extern const QString VARNAME;
extern const QString GROUPNAME;
extern const QString VARDESCR;
extern const QString UNITS;
extern const QString GROUPID;
extern const QString DATETIME;
extern const QString PRECISION;
extern const QString VALUE;
extern const QString MESSAGE;



//выражения для получения столбцов с псевдонимами и доп. опциями
extern const QString SEL_ID;
extern const QString SEL_VARID;
extern const QString SEL_VARNAME;
extern const QString SEL_VARDESCR;
extern const QString SEL_UNITS;
extern const QString SEL_GROUPNAME;
extern const QString SEL_DATETIME;
extern const QString SEL_DATE;
extern const QString SEL_TIME;
extern const QString SEL_PRECISION;
extern const QString SEL_VALUE_RAW;
extern const QString SEL_VALUE_ROUNDED;
extern const QString SEL_VALUE_WITH_UNIT;
extern const QString SEL_MESSAGE;

//шаблоны запросов
extern const join_t VALS_DESCR_JOIN;
extern const join_t EMPTY_JOIN;

//заголовки столбцов в таблице (каждому столбцу из БД соответствует название)
extern const QMap<QString, QString> HEADERS_MAP;

//сопоставление стлбцов vals->messages, чтобы корректно выполнялся union
extern const QMap<QString, QString> VALS_MSGS_UNION_MAP;

//значения для запросов по умолчанию
extern const QStringList DEFAULT_VALS_ITEMS;
extern const QStringList DEFAULT_ALIASES;
extern const QStringList DEFAULT_PLOT_ITEMS;
extern const QStringList DEFAULT_HIDDEN_COLUMNS;
}

QStringList buildMessageItems(QStringList valsItems);
QString getAliasFromHeader(QString header);




#endif // SQL_GLOBALS_H
