#ifndef DATABASE_H
#define DATABASE_H


#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include "sql_query.h"
#include "sql_globals.h"
#include "globals.h"

class DBConnectParams
{
public:
    DBConnectParams(const QString &name      = GLOBALS::DEFAULT_DB_NAME,
                    const QString &host      = GLOBALS::DEFAULT_DB_HOST,
                    const QString &addr      = GLOBALS::DEFAULT_DB_HOSTADDRESS,
                    const QString &user      = GLOBALS::DEFAULT_DB_USERNAME,
                    const QString &password  = GLOBALS::DEFAULT_DB_PASSWORD,
                    const QString &port      = GLOBALS::DEFAULT_DB_PORT,
                    const QString &driver    = GLOBALS::DEFAULT_DB_DRIVER);
    ~DBConnectParams();
    QString getDBName() const;
    QString getUserName() const;
    QString getPassword() const;
    QString getPort() const;
    QString getHostName() const;
    QString getHostAddr() const;
    QString getDriver() const;
    QString toConnectParamsString() const;
private:
    QString       name;           //имя  БД
    QString       hostName;       //имя  хоста
    QString       driver;         //имя драйвера
    QString       user;           //имя пользователя
    QString       password;       //пароль
    QString       hostAddress;    //IP хоств
    QString       port;           //порт
};



class DataBase : public QObject
//класс-обертка для QSqlDatabase, умеет подключаться к БД, создавать БД если она не найдена,
//создавать таблицы, выполнять запросы

{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    QSqlDatabase* getDbPointer();
    DBConnectParams* getConnectParams();
    bool isConnected();
    bool connectDataBase(const DBConnectParams &params,
                         const bool createIfNotAvailable = true);    //соединение с БД, либо создание, если БД не существует

    void insertValues(const QString &table, const QStringList &pos, const QStringList &values);    //добавить запись в таблицу
    bool createTable(const QString &table,const QString &structure);      //создать таблицу
    int countRows(const QString &table);     //кол-во записей в таблице
    float previousValue(const int varid);         //последнее (по времени) значение переменной
    QSqlQuery* exec(const QString &querytext);      //выполить произвольный запрос
    void close();

private:

    QSqlDatabase db;    //класс для доступа к БД
    DBConnectParams connectParams = DBConnectParams();
    char openDataBase(const DBConnectParams &params);   //внутренняя функция для установки соединения с БД
    bool createDataBase(const DBConnectParams &params); //создание БД
    bool forward_only; //TODO - setForwardOnly!!!!!!!!!!!!!!!!!
    bool connected = false;
};

#endif // DATABASE_H
