#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtGlobal>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QSettings>

//Для маршрутизации отладочных сообщений. См. функцию toDebug()
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

//параметры подключения к БД. Хранятся внутри объекта DBConnectParams из database.h
struct CONNECTION_PARAMS {
    QString       hostName;       //имя  хоста
    QString       hostAddress;    //IP хоств
    QString       dbName;         //имя  БД
    QString       dbUser;           //имя пользователя
    QString       dbPassword;       //пароль
    QString       dbPort;           //порт
    QString       driver;         //имя драйвера
};

extern const QString HOSTS_CONFIG_FILE;
extern const QString CONFIG_FILE;

namespace GLOBALS {
//пояснения в .cpp файле
extern bool DEBUG_TRACE;
extern bool DEBUG_SQL;
extern bool DEBUG_ERRORS;
extern bool DEBUG_WARNINGS;
extern bool DEBUG_CONTROLS;
extern bool DEBUG_PLOT;
extern bool DEBUG_TABLE;
extern bool DEBUG_TEST_TABLES;
extern bool DEBUG_DB_CONNECTION;


extern bool ENCRYPT_PASSWORD;
extern const quint64 KEY;

extern QString  DEFAULT_CONNECTION_NAME;
extern QString  DEFAULT_PRESET;
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
extern CONNECTION_PARAMS SERVICE_CONNECTION;

extern QStringList AVAILABLE_DRIVERS;

extern QString DEFAULT_DATETIME_FORMAT;



extern bool CONNECT_ON_STARTUP;
extern bool MESSAGES_ON_BY_DEFAULT;
extern bool HIDE_COLUMNS_BY_DEFAULT;
extern bool SHOW_QUERY;
extern bool EDIT_QUERY;
extern bool ALLOW_ADVANCED_DB_SETTINGS;
extern bool SHOW_SLIDER_SECTIONS;
extern bool AUTO_UPDATE;//Обновлять информацию по таймеру
extern int AUTO_UPDATE_TIMER_INTERVAL; //Интервал таймера


extern QString ABOUT_TEXT;
extern QMap<QString,CONNECTION_PARAMS> CONNECTION_PRESETS;
extern QMap<QString,QString> MESSAGES_TO_SLIDER_SECTIONS;
extern QStringList STAGE_NAMES;
extern QStringList STAGE_MSGS;
}

void readConnectionPresets();
void readSettings();
void toDebug(const QVariant &msg, char type=DT_DEFAULT);

#endif // GLOBALS_H
