#include "globals.h"
#include <QSettings>

const QString HOSTS_CONFIG_FILE = "hosts.ini";
const QString CONFIG_FILE = "ArchView.ini";

namespace GLOBALS {
QSettings settings(CONFIG_FILE,QSettings::IniFormat);

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
const QString ABOUT_TEXT = settings.value("globals/ABOUT_TEXT","ООО 'СКУ СИСТЕМА' просмотр архива.").toString();

QMap<QString, QString> HOSTS_MAP = {};

const QString DEFAULT_DB_NAME        = settings.value("db/DEFAULT_DB_NAME",        "test").toString();
const QString SERVICE_DB_NAME        = settings.value("db/SERVICE_DB_NAME",        "template1").toString();
const QString DEFAULT_DB_USERNAME    = settings.value("db/DEFAULT_DB_USERNAME",    "postgres").toString();
const QString DEFAULT_DB_PASSWORD    = settings.value("db/DEFAULT_DB_PASSWORD",    "postgres").toString();
const QString DEFAULT_DB_DRIVER      = settings.value("db/DEFAULT_DB_DRIVER",      "QPSQL").toString();
const QString DEFAULT_DB_HOST        = settings.value("db/DEFAULT_DB_HOST",        "localhost").toString();
const QString DEFAULT_DB_HOSTADDRESS = settings.value("db/DEFAULT_DB_HOSTADDRESS", "127.0.0.1").toString();
const QString DEFAULT_DB_PORT        = settings.value("db/DEFAULT_DB_PORT",        "5432").toString();
const QStringList AVAILABLE_DRIVERS  = QStringList({DEFAULT_DB_DRIVER});
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
