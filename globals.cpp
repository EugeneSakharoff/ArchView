#include "globals.h"
#include <QSettings>
#include <QTextCodec>
#include "sql_globals.h"

const QString HOSTS_CONFIG_FILE = "hosts.ini";
const QString CONFIG_FILE = "ArchView.ini";

namespace GLOBALS {
 bool DEBUG_TRACE;
 bool DEBUG_SQL;
 bool DEBUG_ERRORS;
 bool DEBUG_WARNINGS;
 bool DEBUG_CONTROLS;
 bool DEBUG_PLOT;
 bool DEBUG_TABLE;
 bool DEBUG_TEST_TABLES;
 bool DEBUG_DB_CONNECTION;



 QString  DEFAULT_DB_NAME;
 QString  SERVICE_DB_NAME;
 QString  DEFAULT_DB_USERNAME;
 QString  DEFAULT_DB_PASSWORD;
 QString  SERVICE_DB_USERNAME;
 QString  SERVICE_DB_PASSWORD;
 QString  DEFAULT_DB_DRIVER;
 QString  DEFAULT_DB_HOST;
 QString  DEFAULT_DB_HOSTADDRESS;
 QString  DEFAULT_DB_PORT;
 QString  SERVICE_DB_HOST;
 QString  SERVICE_DB_HOSTADDRESS;
 QString  SERVICE_DB_PORT;
 QStringList AVAILABLE_DRIVERS;

 QString DEFAULT_DATETIME_FORMAT;



 bool CONNECT_ON_STARTUP;
 bool MESSAGES_ON_BY_DEFAULT;
 bool HIDE_COLUMNS_BY_DEFAULT;

 QString ABOUT_TEXT;
 QMap<QString, QString> HOSTS_MAP;
/*
const bool DEBUG_TRACE         = settings.value("debug/DEBUG_TRACE","false").toBool();
const bool DEBUG_SQL           = settings.value("debug/DEBUG_SQL","false").toBool();
const bool DEBUG_ERRORS        = settings.value("debug/DEBUG_ERRORS","false").toBool();
const bool DEBUG_WARNINGS      = settings.value("debug/DEBUG_WARNINGS","false").toBool();
const bool DEBUG_CONTROLS      = settings.value("debug/DEBUG_CONTROLS","false").toBool();
const bool DEBUG_PLOT          = settings.value("debug/DEBUG_PLOT","false").toBool();
const bool DEBUG_TABLE         = settings.value("debug/DEBUG_TABLE","false").toBool();
const bool DEBUG_TEST_TABLES   = settings.value("debug/DEBUG_TEST_TABLES","false").toBool();
const bool DEBUG_DB_CONNECTION = settings.value("debug/DEBUG_DB_CONNECTION","false").toBool();

const bool CONNECT_ON_STARTUP      = settings.value("globals/CONNECT_ON_STARTUP","false").toBool();
const bool MESSAGES_ON_BY_DEFAULT  = settings.value("globals/MESSAGES_ON_BY_DEFAULT","false").toBool();
const bool HIDE_COLUMNS_BY_DEFAULT = settings.value("globals/HIDE_COLUMNS_BY_DEFAULT","false").toBool();

const QString DEFAULT_DATETIME_FORMAT = settings.value("globals/DEFAULT_DATETIME_FORMAT","dd-MM-yyyy hh:mm:ss").toString();
const QString ABOUT_TEXT = QString::fromLocal8Bit(settings.value("globals/ABOUT_TEXT","ООО 'СКУ СИСТЕМА' просмотр архива.").toByteArray());

QMap<QString, QString> HOSTS_MAP = {};

const QString DEFAULT_DB_NAME        = settings.value("db/DEFAULT_DB_NAME",        "test").toString();
const QString SERVICE_DB_NAME        = settings.value("db/SERVICE_DB_NAME",        "template1").toString();
const QString DEFAULT_DB_USERNAME    = settings.value("db/DEFAULT_DB_USERNAME",    "postgres").toString();
const QString DEFAULT_DB_PASSWORD    = settings.value("db/DEFAULT_DB_PASSWORD",    "postgres").toString();
const QString SERVICE_DB_USERNAME    = settings.value("db/SERVICE_DB_USERNAME",    "postgres").toString();
const QString SERVICE_DB_PASSWORD    = settings.value("db/SERVICE_DB_PASSWORD",    "postgres").toString();
const QString DEFAULT_DB_DRIVER      = settings.value("db/DEFAULT_DB_DRIVER",      "QPSQL").toString();
const QString DEFAULT_DB_HOST        = settings.value("db/DEFAULT_DB_HOST",        "localhost").toString();
const QString DEFAULT_DB_HOSTADDRESS = settings.value("db/DEFAULT_DB_HOSTADDRESS", "127.0.0.1").toString();
const QString DEFAULT_DB_PORT        = settings.value("db/DEFAULT_DB_PORT",        "5432").toString();
const QString SERVICE_DB_HOST        = settings.value("db/SERVICE_DB_HOST",        "localhost").toString();
const QString SERVICE_DB_HOSTADDRESS = settings.value("db/SERVICE_DB_HOSTADDRESS", "127.0.0.1").toString();
const QString SERVICE_DB_PORT        = settings.value("db/SERVICE_DB_PORT",        "5432").toString();
const QStringList AVAILABLE_DRIVERS  = QStringList({DEFAULT_DB_DRIVER});
*/
}

void readHostsList()
{
QSettings hosts(HOSTS_CONFIG_FILE,QSettings::IniFormat);
foreach (const QString &hostname,hosts.allKeys())
  GLOBALS::HOSTS_MAP.insert(hostname,hosts.value(hostname).toString());
}

void toDebug(const QVariant &msg, char type)
{
QSettings settings(CONFIG_FILE,QSettings::IniFormat);
switch (type)
  {
  case DT_ERROR:
    if (GLOBALS::DEBUG_ERRORS) qDebug()<<QString("!!!ERROR!!! %1").arg(msg.toString());
    break;
  case DT_WARNING:
    if (GLOBALS::DEBUG_WARNINGS) qDebug()<<QString("!WARNING! %1").arg(msg.toString());
  break;
  case DT_TRACE:
    if (GLOBALS::DEBUG_TRACE) qDebug()<<QString("%1").arg(msg.toString(),-70,QChar(46));
    break;
  case DT_SQL:
    if (GLOBALS::DEBUG_SQL) qDebug()<<msg;
    break;
  case DT_CONTROLS:
    if (GLOBALS::DEBUG_CONTROLS) qDebug()<<msg;
    break;
  case DT_PLOT:
    if (GLOBALS::DEBUG_PLOT) qDebug()<<msg;
    break;
  case DT_TABLE:
    if (GLOBALS::DEBUG_TABLE) qDebug()<<msg;
    break;
  case DT_TEST_TABLES:
    if (GLOBALS::DEBUG_TEST_TABLES) qDebug()<<msg;
    break;
  case DT_DATABASE:
    if (GLOBALS::DEBUG_DB_CONNECTION) qDebug()<<msg;
    break;
  qDebug()<<msg;
  }
}

void readSettings()
{
QSettings settings(CONFIG_FILE,QSettings::IniFormat);
QTextCodec *codec = QTextCodec::codecForName("UTF-8");
settings.setIniCodec(codec);

toDebug("Reading config file: "+CONFIG_FILE, DT_TRACE);

using namespace GLOBALS;
DEBUG_TRACE         = settings.value("debug/DEBUG_TRACE","false").toBool();
DEBUG_SQL           = settings.value("debug/DEBUG_SQL","false").toBool();
DEBUG_ERRORS        = settings.value("debug/DEBUG_ERRORS","false").toBool();
DEBUG_WARNINGS      = settings.value("debug/DEBUG_WARNINGS","false").toBool();
DEBUG_CONTROLS      = settings.value("debug/DEBUG_CONTROLS","false").toBool();
DEBUG_PLOT          = settings.value("debug/DEBUG_PLOT","false").toBool();
DEBUG_TABLE         = settings.value("debug/DEBUG_TABLE","false").toBool();
DEBUG_TEST_TABLES   = settings.value("debug/DEBUG_TEST_TABLES","false").toBool();
DEBUG_DB_CONNECTION = settings.value("debug/DEBUG_DB_CONNECTION","false").toBool();

CONNECT_ON_STARTUP      = settings.value("globals/CONNECT_ON_STARTUP","false").toBool();
MESSAGES_ON_BY_DEFAULT  = settings.value("globals/MESSAGES_ON_BY_DEFAULT","false").toBool();
HIDE_COLUMNS_BY_DEFAULT = settings.value("globals/HIDE_COLUMNS_BY_DEFAULT","false").toBool();

DEFAULT_DATETIME_FORMAT = settings.value("globals/DEFAULT_DATETIME_FORMAT","dd-MM-yyyy hh:mm:ss").toString();
ABOUT_TEXT = settings.value("globals/ABOUT_TEXT","ООО 'СКУ СИСТЕМА' просмотр архива.").toString();

HOSTS_MAP = {};

DEFAULT_DB_NAME        = settings.value("db/DEFAULT_DB_NAME",        "test").toString();
SERVICE_DB_NAME        = settings.value("db/SERVICE_DB_NAME",        "template1").toString();
DEFAULT_DB_USERNAME    = settings.value("db/DEFAULT_DB_USERNAME",    "postgres").toString();
DEFAULT_DB_PASSWORD    = settings.value("db/DEFAULT_DB_PASSWORD",    "postgres").toString();
SERVICE_DB_USERNAME    = settings.value("db/SERVICE_DB_USERNAME",    "postgres").toString();
SERVICE_DB_PASSWORD    = settings.value("db/SERVICE_DB_PASSWORD",    "postgres").toString();
DEFAULT_DB_DRIVER      = settings.value("db/DEFAULT_DB_DRIVER",      "QPSQL").toString();
DEFAULT_DB_HOST        = settings.value("db/DEFAULT_DB_HOST",        "localhost").toString();
DEFAULT_DB_HOSTADDRESS = settings.value("db/DEFAULT_DB_HOSTADDRESS", "127.0.0.1").toString();
DEFAULT_DB_PORT        = settings.value("db/DEFAULT_DB_PORT",        "5432").toString();
SERVICE_DB_HOST        = settings.value("db/SERVICE_DB_HOST",        "localhost").toString();
SERVICE_DB_HOSTADDRESS = settings.value("db/SERVICE_DB_HOSTADDRESS", "127.0.0.1").toString();
SERVICE_DB_PORT        = settings.value("db/SERVICE_DB_PORT",        "5432").toString();
AVAILABLE_DRIVERS  = QStringList({DEFAULT_DB_DRIVER});

using namespace SQL_GLOBALS;
VALUES_TABLE       = settings.value("sql/VALUES_TABLE",       "vals").toString();
DESCRIPTIONS_TABLE = settings.value("sql/DESCRIPTIONS_TABLE", "descriptions").toString();
MESSAGES_TABLE     = settings.value("sql/MESSAGES_TABLE",     "messages").toString();
GROUPS_TABLE       = settings.value("sql/GROUPS_TABLE",       "groups").toString();

ID_COLUMN          = settings.value("sql/ID_COLUMN",          "id").toString();
VARID_COLUMN       = settings.value("sql/VARID_COLUMN",       "varid").toString();
NAME_COLUMN        = settings.value("sql/NAME_COLUMN",        "name").toString();
DESCRIPTION_COLUMN = settings.value("sql/DESCRIPTION_COLUMN", "description").toString();
UNITS_COLUMN       = settings.value("sql/UNITS_COLUMN",       "units").toString();
GROUPID_COLUMN     = settings.value("sql/GROUPID_COLUMN",     "ingroup").toString();
DATETIME_COLUMN    = settings.value("sql/DATETIME_COLUMN",    "time").toString();
PRECISION_COLUMN   = settings.value("sql/PRECISION_COLUMN",   "precision").toString();
VALUE_COLUMN       = settings.value("sql/VALUE_COLUMN",       "val").toString();
MESSAGE_COLUMN     = settings.value("sql/MESSAGE_COLUMN",     "message").toString();

ALIAS_ID         = settings.value("sql/ALIAS_ID",          "id").toString();
ALIAS_VARID      = settings.value("sql/ALIAS_VARID",       "varid").toString();
ALIAS_VARNAME    = settings.value("sql/ALIAS_VARNAME",     "varname").toString();
ALIAS_DESCR      = settings.value("sql/ALIAS_DESCR",       "description").toString();
ALIAS_UNITS      = settings.value("sql/ALIAS_UNITS",       "varunits").toString();
ALIAS_GROUPID    = settings.value("sql/ALIAS_GROUPID",     "groupid").toString();
ALIAS_GROUPNAME  = settings.value("sql/ALIAS_GROUPNAME",   "groupname").toString();
ALIAS_DATETIME   = settings.value("sql/ALIAS_DATETIME",    "dt").toString();
ALIAS_DATE       = settings.value("sql/ALIAS_DATE",        "d").toString();
ALIAS_TIME       = settings.value("sql/ALIAS_TIME",        "t").toString();
ALIAS_PRECISION  = settings.value("sql/ALIAS_PRECISION",   "precision").toString();
ALIAS_VALUE      = settings.value("sql/ALIAS_VALUE",       "val").toString();
ALIAS_VALUE_RAW  = settings.value("sql/ALIAS_VALUE_RAW",   "val_raw").toString();

HEADER_ID        = settings.value("sql/HEADER_ID",        "Номер").toString();
HEADER_VARID     = settings.value("sql/HEADER_VARID",     "id переменной").toString();
HEADER_VARNAME   = settings.value("sql/HEADER_VARNAME",   "Наименование").toString();
HEADER_DESCR     = settings.value("sql/HEADER_DESCR",     "Описание").toString();
HEADER_UNITS     = settings.value("sql/HEADER_UNITS",     "Единица измерения").toString();
HEADER_GROUPNAME = settings.value("sql/HEADER_GROUPNAME", "Группа").toString();
HEADER_DATETIME  = settings.value("sql/HEADER_DATETIME",  "Дата и время").toString();
HEADER_DATE      = settings.value("sql/HEADER_DATE",      "Дата").toString();
HEADER_TIME      = settings.value("sql/HEADER_TIME",      "Время").toString();
HEADER_PRECISION = settings.value("sql/HEADER_PRECISION", "Точность").toString();
HEADER_VALUE     = settings.value("sql/HEADER_VALUE",     "Значение").toString();
HEADER_VALUE_RAW = settings.value("sql/HEADER_VALUE_RAW", "Точное значение").toString();

//выражения на SQL, получающие определенный столбец определенной таблицы
VALUES_ID             = VALUES_TABLE+QString(".")+ID_COLUMN;
DESCRIPTIONS_ID       = DESCRIPTIONS_TABLE+QString(".")+ID_COLUMN;
GROUPS_ID             = GROUPS_TABLE+QString(".")+ID_COLUMN;
VARID                 = VALUES_TABLE+QString(".")+VARID_COLUMN;
VARNAME               = DESCRIPTIONS_TABLE+QString(".")+NAME_COLUMN;
GROUPNAME             = GROUPS_TABLE+QString(".")+NAME_COLUMN;
VARDESCR              = DESCRIPTIONS_TABLE+QString(".")+DESCRIPTION_COLUMN;
UNITS                 = DESCRIPTIONS_TABLE+QString(".")+UNITS_COLUMN;
GROUPID               = DESCRIPTIONS_TABLE+QString(".")+GROUPID_COLUMN;
DATETIME              = DATETIME_COLUMN;
PRECISION             = DESCRIPTIONS_TABLE+QString(".")+PRECISION_COLUMN;
VALUE                 = VALUES_TABLE+QString(".")+VALUE_COLUMN;
MESSAGE               = MESSAGES_TABLE+QString(".")+MESSAGE_COLUMN;

//выражения для получения столбцов с псевдонимами и доп. опциями
SEL_ID                = VALUES_ID+QString(" AS ")+ALIAS_ID;
SEL_VARID             = VARID+QString(" AS ")+ALIAS_VARID;
SEL_VARNAME           = VARNAME+QString(" AS ")+ALIAS_VARNAME;
SEL_VARDESCR          = VARDESCR+QString(" AS ")+ALIAS_DESCR;
SEL_UNITS             = UNITS+QString(" AS ")+ALIAS_UNITS;
SEL_GROUPNAME         = GROUPNAME+QString(" AS ")+ALIAS_GROUPNAME;
SEL_DATETIME          = QString("to_char(")+DATETIME_COLUMN+QString(", 'dd-MM-YYYY HH24:MI:SS') AS ")+ALIAS_DATETIME;
SEL_DATE              = QString("to_char(")+DATETIME_COLUMN+QString(", 'dd-MM-YYYY') AS ")+ALIAS_DATE;
SEL_TIME              = QString("to_char(")+DATETIME_COLUMN+QString(", 'HH24:MI:SS')  AS ")+ALIAS_TIME;
SEL_PRECISION         = PRECISION+QString(" AS ")+ALIAS_PRECISION;
SEL_VALUE_RAW         = VALUE+QString(" AS ")+ALIAS_VALUE_RAW;
SEL_VALUE_ROUNDED     = QString("round(")+VALUE+QString("::numeric,")+PRECISION+QString(") AS ")+ALIAS_VALUE;
SEL_VALUE_WITH_UNIT   = QString("concat(round(")+VALUE+QString("::numeric,")+PRECISION+QString("),' ', ")+UNITS+QString(") AS ")+ALIAS_VALUE;
SEL_MESSAGE           = MESSAGE+QString(" AS ")+ALIAS_VALUE;


HEADERS_MAP = {{ALIAS_ID,        HEADER_ID},
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


VALS_MSGS_UNION_MAP = {{SEL_ID,               QString("null AS ")+ALIAS_ID},
                       {SEL_VARID,            QString("null AS ")+ALIAS_VARID},
                       {SEL_VARNAME,          QString("null AS ")+ALIAS_VARNAME},
                       {SEL_VARDESCR,         QString("null AS ")+ALIAS_DESCR},
                       {SEL_UNITS,            QString("null AS ")+ALIAS_UNITS},
                       {SEL_GROUPNAME,        QString("null AS ")+ALIAS_GROUPNAME},
                       {SEL_DATETIME,         SEL_DATETIME},
                       {SEL_DATE,             SEL_DATE},
                       {SEL_TIME,             SEL_TIME},
                       {SEL_PRECISION,        QString("null AS ")+ALIAS_PRECISION},
                       {SEL_VALUE_RAW,        SEL_MESSAGE},
                       {SEL_VALUE_ROUNDED,    SEL_MESSAGE},
                       {SEL_VALUE_WITH_UNIT,  SEL_MESSAGE}};

VALS_DESCR_JOIN = {DESCRIPTIONS_TABLE,{VARID,DESCRIPTIONS_ID}};
EMPTY_JOIN = {nullptr,{nullptr,nullptr}};

DEFAULT_VALS_ITEMS = QStringList({SEL_DATETIME,SEL_DATE,SEL_TIME,SEL_VARNAME,SEL_VALUE_WITH_UNIT,SEL_VARDESCR,SEL_GROUPNAME,SEL_PRECISION,SEL_UNITS});
DEFAULT_ALIASES = QStringList({ALIAS_DATETIME,ALIAS_DATE,ALIAS_TIME,ALIAS_VARNAME,ALIAS_VALUE,ALIAS_DESCR,ALIAS_GROUPNAME,ALIAS_PRECISION,ALIAS_UNITS});

DEFAULT_HIDDEN_COLUMNS = QStringList({HEADERS_MAP.value(ALIAS_VARID),
                                                        HEADERS_MAP.value(ALIAS_DATETIME),
                                                        HEADERS_MAP.value(ALIAS_VALUE_RAW),
                                                        HEADERS_MAP.value(ALIAS_DESCR),
                                                        HEADERS_MAP.value(ALIAS_GROUPNAME),
                                                        HEADERS_MAP.value(ALIAS_ID),
                                                        HEADERS_MAP.value(ALIAS_PRECISION),
                                                        HEADERS_MAP.value(ALIAS_UNITS)});

DEFAULT_PLOT_ITEMS = QStringList({SEL_DATETIME,SEL_VARNAME,SEL_VALUE_RAW});
toDebug("End reading config file", DT_TRACE);
}
