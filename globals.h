#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtGlobal>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QSettings>

enum DEBUG_TYPES
{
DT_ERROR,
DT_WARNING,
DT_TRACE,
DT_SQL,
DT_CONTROLS,
DT_PLOT,
DT_TABLE,
DT_TEST_TABLES,
DT_DATABASE,
DT_DEFAULT
};

extern const QString HOSTS_CONFIG_FILE;
extern const QString CONFIG_FILE;

namespace GLOBALS {

extern bool DEBUG_TRACE;
extern bool DEBUG_SQL;
extern bool DEBUG_ERRORS;
extern bool DEBUG_WARNINGS;
extern bool DEBUG_CONTROLS;
extern bool DEBUG_PLOT;
extern bool DEBUG_TABLE;
extern bool DEBUG_TEST_TABLES;
extern bool DEBUG_DB_CONNECTION;



extern QString  DEFAULT_DB_NAME;
extern QString  SERVICE_DB_NAME;
extern QString  DEFAULT_DB_USERNAME;
extern QString  DEFAULT_DB_PASSWORD;
extern QString  SERVICE_DB_USERNAME;
extern QString  SERVICE_DB_PASSWORD;
extern QString  DEFAULT_DB_DRIVER;
extern QString  DEFAULT_DB_HOST;
extern QString  DEFAULT_DB_HOSTADDRESS;
extern QString  DEFAULT_DB_PORT;
extern QString  SERVICE_DB_HOST;
extern QString  SERVICE_DB_HOSTADDRESS;
extern QString  SERVICE_DB_PORT;
extern QStringList AVAILABLE_DRIVERS;

extern QString DEFAULT_DATETIME_FORMAT;



extern bool CONNECT_ON_STARTUP;
extern bool MESSAGES_ON_BY_DEFAULT;
extern bool HIDE_COLUMNS_BY_DEFAULT;

extern QString ABOUT_TEXT;
extern QMap<QString, QString> HOSTS_MAP;
}

void readHostsList();
void readSettings();
void toDebug(const QVariant &msg, char type=DT_DEFAULT);

#endif // GLOBALS_H
