#include "sql_globals.h"
#include <QStringBuilder>

namespace SQL_GLOBALS {

QSettings settings(CONFIG_FILE,QSettings::IniFormat);

const QString VALUES_TABLE       = settings.value("sql/VALUES_TABLE",       "vals").toString();
const QString DESCRIPTIONS_TABLE = settings.value("sql/DESCRIPTIONS_TABLE", "descriptions").toString();
const QString MESSAGES_TABLE     = settings.value("sql/MESSAGES_TABLE",     "messages").toString();
const QString GROUPS_TABLE       = settings.value("sql/GROUPS_TABLE",       "groups").toString();

const QString ID_COLUMN          = settings.value("sql/ID_COLUMN",          "id").toString();
const QString VARID_COLUMN       = settings.value("sql/VARID_COLUMN",       "varid").toString();
const QString NAME_COLUMN        = settings.value("sql/NAME_COLUMN",        "name").toString();
const QString DESCRIPTION_COLUMN = settings.value("sql/DESCRIPTION_COLUMN", "description").toString();
const QString UNITS_COLUMN       = settings.value("sql/UNITS_COLUMN",       "units").toString();
const QString GROUPID_COLUMN     = settings.value("sql/GROUPID_COLUMN",     "ingroup").toString();
const QString DATETIME_COLUMN    = settings.value("sql/DATETIME_COLUMN",    "time").toString();
const QString PRECISION_COLUMN   = settings.value("sql/PRECISION_COLUMN",   "precision").toString();
const QString VALUE_COLUMN       = settings.value("sql/VALUE_COLUMN",       "val").toString();
const QString MESSAGE_COLUMN     = settings.value("sql/MESSAGE_COLUMN",     "message").toString();

const QString ALIAS_ID         = settings.value("sql/ALIAS_ID",          "id").toString();
const QString ALIAS_VARID      = settings.value("sql/ALIAS_VARID",       "varid").toString();
const QString ALIAS_VARNAME    = settings.value("sql/ALIAS_VARNAME",     "varname").toString();
const QString ALIAS_DESCR      = settings.value("sql/ALIAS_DESCR",       "description").toString();
const QString ALIAS_UNITS      = settings.value("sql/ALIAS_UNITS",       "varunits").toString();
const QString ALIAS_GROUPID    = settings.value("sql/ALIAS_GROUPID",     "groupid").toString();
const QString ALIAS_GROUPNAME  = settings.value("sql/ALIAS_GROUPNAME",   "groupname").toString();
const QString ALIAS_DATETIME   = settings.value("sql/ALIAS_DATETIME",    "dt").toString();
const QString ALIAS_DATE       = settings.value("sql/ALIAS_DATE",        "d").toString();
const QString ALIAS_TIME       = settings.value("sql/ALIAS_TIME",        "t").toString();
const QString ALIAS_PRECISION  = settings.value("sql/ALIAS_PRECISION",   "precision").toString();
const QString ALIAS_VALUE      = settings.value("sql/ALIAS_VALUE",       "val").toString();
const QString ALIAS_VALUE_RAW  = settings.value("sql/ALIAS_VALUE_RAW",   "val_raw").toString();

const QString HEADER_ID        = settings.value("sql/HEADER_ID",        "Номер").toString();
const QString HEADER_VARID     = settings.value("sql/HEADER_VARID",     "id переменной").toString();
const QString HEADER_VARNAME   = settings.value("sql/HEADER_VARNAME",   "Наименование").toString();
const QString HEADER_DESCR     = settings.value("sql/HEADER_DESCR",     "Описание").toString();
const QString HEADER_UNITS     = settings.value("sql/HEADER_UNITS",     "Единица измерения").toString();
const QString HEADER_GROUPNAME = settings.value("sql/HEADER_GROUPNAME", "Группа").toString();
const QString HEADER_DATETIME  = settings.value("sql/HEADER_DATETIME",  "Дата и время").toString();
const QString HEADER_DATE      = settings.value("sql/HEADER_DATE",      "Дата").toString();
const QString HEADER_TIME      = settings.value("sql/HEADER_TIME",      "Время").toString();
const QString HEADER_PRECISION = settings.value("sql/HEADER_PRECISION", "Точность").toString();
const QString HEADER_VALUE     = settings.value("sql/HEADER_VALUE",     "Значение").toString();
const QString HEADER_VALUE_RAW = settings.value("sql/HEADER_VALUE_RAW", "Точное значение").toString();

//выражения на SQL, получающие определенный столбец определенной таблицы
const QString VALUES_ID             = VALUES_TABLE%QString(".")%ID_COLUMN;
const QString DESCRIPTIONS_ID       = DESCRIPTIONS_TABLE%QString(".")%ID_COLUMN;
const QString GROUPS_ID             = GROUPS_TABLE%QString(".")%ID_COLUMN;
const QString VARID                 = VALUES_TABLE%QString(".")%VARID_COLUMN;
const QString VARNAME               = DESCRIPTIONS_TABLE%QString(".")%NAME_COLUMN;
const QString GROUPNAME             = GROUPS_TABLE%QString(".")%NAME_COLUMN;
const QString VARDESCR              = DESCRIPTIONS_TABLE%QString(".")%DESCRIPTION_COLUMN;
const QString UNITS                 = DESCRIPTIONS_TABLE%QString(".")%UNITS_COLUMN;
const QString GROUPID               = DESCRIPTIONS_TABLE%QString(".")%GROUPID_COLUMN;
const QString DATETIME              = DATETIME_COLUMN;
const QString PRECISION             = DESCRIPTIONS_TABLE%QString(".")%PRECISION_COLUMN;
const QString VALUE                 = VALUES_TABLE%QString(".")%VALUE_COLUMN;
const QString MESSAGE               = MESSAGES_TABLE%QString(".")%MESSAGE_COLUMN;

//выражения для получения столбцов с псевдонимами и доп. опциями
const QString SEL_ID                = VALUES_ID%QString(" AS ")%ALIAS_ID;
const QString SEL_VARID             = VARID%QString(" AS ")%ALIAS_VARID;
const QString SEL_VARNAME           = VARNAME%QString(" AS ")%ALIAS_VARNAME;
const QString SEL_VARDESCR          = VARDESCR%QString(" AS ")%ALIAS_DESCR;
const QString SEL_UNITS             = UNITS%QString(" AS ")%ALIAS_UNITS;
const QString SEL_GROUPNAME         = GROUPNAME%QString(" AS ")%ALIAS_GROUPNAME;
const QString SEL_DATETIME          = QString("to_char(")%DATETIME_COLUMN%QString(", 'dd-MM-YYYY HH24:MI:SS') AS ")%ALIAS_DATETIME;
const QString SEL_DATE              = QString("to_char(")%DATETIME_COLUMN%QString(", 'dd-MM-YYYY') AS ")%ALIAS_DATE;
const QString SEL_TIME              = QString("to_char(")%DATETIME_COLUMN%QString(", 'HH24:MI:SS')  AS ")%ALIAS_TIME;
const QString SEL_PRECISION         = PRECISION%QString(" AS ")%ALIAS_PRECISION;
const QString SEL_VALUE_RAW         = VALUE%QString(" AS ")%ALIAS_VALUE_RAW;
const QString SEL_VALUE_ROUNDED     = QString("round(")%VALUE%QString("::numeric,")%PRECISION%QString(") AS ")%ALIAS_VALUE;
const QString SEL_VALUE_WITH_UNIT   = QString("concat(round(")%VALUE%QString("::numeric,")%PRECISION%QString("),' ', ")%UNITS%QString(") AS ")%ALIAS_VALUE;
const QString SEL_MESSAGE           = MESSAGE%QString(" AS ")%ALIAS_VALUE;


const QMap<QString, QString> HEADERS_MAP  {{ALIAS_ID,        HEADER_ID},
                                           {ALIAS_VARID,     HEADER_VARID},
                                           {ALIAS_VARNAME,   HEADER_VARNAME},
                                           {ALIAS_DESCR,     HEADER_DESCR},
                                           {ALIAS_UNITS,     HEADER_UNITS},
                                           {ALIAS_GROUPNAME, HEADER_GROUPNAME},
                                           {ALIAS_DATETIME,  HEADER_DATETIME},
                                           {ALIAS_DATE,      HEADER_DATE},
                                           {ALIAS_TIME,      HEADER_TIME},
                                           {ALIAS_PRECISION, HEADER_PRECISION},
                                           {ALIAS_VALUE,     HEADER_VALUE},
                                           {ALIAS_VALUE_RAW, HEADER_VALUE_RAW}};


const QMap<QString, QString> VALS_MSGS_UNION_MAP  {{SEL_ID,               QString("null AS ")%ALIAS_ID},
                                                   {SEL_VARID,            QString("null AS ")%ALIAS_VARID},
                                                   {SEL_VARNAME,          QString("null AS ")%ALIAS_VARNAME},
                                                   {SEL_VARDESCR,         QString("null AS ")%ALIAS_DESCR},
                                                   {SEL_UNITS,            QString("null AS ")%ALIAS_UNITS},
                                                   {SEL_GROUPNAME,        QString("null AS ")%ALIAS_GROUPNAME},
                                                   {SEL_DATETIME,         SEL_DATETIME},
                                                   {SEL_DATE,             SEL_DATE},
                                                   {SEL_TIME,             SEL_TIME},
                                                   {SEL_PRECISION,        QString("null AS ")%ALIAS_PRECISION},
                                                   {SEL_VALUE_RAW,        SEL_MESSAGE},
                                                   {SEL_VALUE_ROUNDED,    SEL_MESSAGE},
                                                   {SEL_VALUE_WITH_UNIT,  SEL_MESSAGE}};

const join_t VALS_DESCR_JOIN {DESCRIPTIONS_TABLE,{VARID,DESCRIPTIONS_ID}};
const join_t EMPTY_JOIN {nullptr,{nullptr,nullptr}};

const QStringList DEFAULT_VALS_ITEMS = QStringList({SEL_DATETIME,SEL_DATE,SEL_TIME,SEL_VARNAME,SEL_VALUE_WITH_UNIT,SEL_VARDESCR,SEL_GROUPNAME,SEL_PRECISION,SEL_UNITS});
const QStringList DEFAULT_ALIASES = QStringList({ALIAS_DATETIME,ALIAS_DATE,ALIAS_TIME,ALIAS_VARNAME,ALIAS_VALUE,ALIAS_DESCR,ALIAS_GROUPNAME,ALIAS_PRECISION,ALIAS_UNITS});

const QStringList DEFAULT_HIDDEN_COLUMNS = QStringList({HEADERS_MAP.value(ALIAS_VARID),
                                                        HEADERS_MAP.value(ALIAS_DATETIME),
                                                        HEADERS_MAP.value(ALIAS_VALUE_RAW),
                                                        HEADERS_MAP.value(ALIAS_DESCR),
                                                        HEADERS_MAP.value(ALIAS_GROUPNAME),
                                                        HEADERS_MAP.value(ALIAS_ID),
                                                        HEADERS_MAP.value(ALIAS_PRECISION),
                                                        HEADERS_MAP.value(ALIAS_UNITS)});

const QStringList DEFAULT_PLOT_ITEMS = QStringList({SEL_DATETIME,SEL_VARNAME,SEL_VALUE_RAW});
}

QStringList buildMessageItems(QStringList valsItems)
{
QStringList messageItems;
foreach (const QString item, valsItems) messageItems.append(SQL_GLOBALS::VALS_MSGS_UNION_MAP[item]);
return messageItems;
}

QString getAliasFromHeader(QString header)
{
return SQL_GLOBALS::HEADERS_MAP.key(header);
};




