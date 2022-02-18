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

extern const bool DEBUG_TRACE;
extern const bool DEBUG_SQL;
extern const bool DEBUG_ERRORS;
extern const bool DEBUG_WARNINGS;
extern const bool DEBUG_CONTROLS;
extern const bool DEBUG_PLOT;
extern const bool DEBUG_TABLE;
extern const bool DEBUG_TEST_TABLES;
extern const bool DEBUG_DB_CONNECTION;



extern const QString  DEFAULT_DB_NAME;
extern const QString  SERVICE_DB_NAME;
extern const QString  DEFAULT_DB_USERNAME;
extern const QString  DEFAULT_DB_PASSWORD;
extern const QString  DEFAULT_DB_DRIVER;
extern const QString  DEFAULT_DB_HOST;
extern const QString  DEFAULT_DB_HOSTADDRESS;
extern const QString  DEFAULT_DB_PORT;
extern const QStringList AVAILABLE_DRIVERS;

extern const QString DEFAULT_DATETIME_FORMAT;



extern const bool CONNECT_ON_STARTUP;
extern const bool MESSAGES_ON_BY_DEFAULT;
extern const bool HIDE_COLUMNS_BY_DEFAULT;

extern const QString ABOUT_TEXT;
extern QMap<QString, QString> HOSTS_MAP;
}

void readHostsList();
void toDebug(const QVariant &msg, char type=DT_DEFAULT);

#endif // GLOBALS_H
