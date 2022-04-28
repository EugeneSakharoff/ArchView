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

//Класс для хранения и представления параметров подключения к БД
//Инкапсулирует параметры, умеет возвращать строку подключения
class DBConnectParams
{
public:
    DBConnectParams(const CONNECTION_PARAMS &params);
    ~DBConnectParams();


    QString getHostName() const;
    void setHostName(const QString &hostname);
    QString getHostAddr() const;
    void setHostAddr(const QString &hostaddr);
    QString getDBName() const;
    void setDBName(const QString &dbname);
    QString getDBUser() const;
    void setDBUser(const QString &dbuser);
    QString getDBPassword() const;
    void setDBPassword(const QString &dbpassword);
    QString getDBPort() const;
    void setDBPort(const QString &dbport);
    QString getDriver() const;
    void setDriver(const QString &driver);

    const CONNECTION_PARAMS *getParams()const;

    QString toConnectParamsString() const;

private:
    CONNECTION_PARAMS params;
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
    bool isConnected();
    bool connectDataBase(const bool createIfNotAvailable = true);    //соединение с БД, либо создание, если БД не существует

    void insertValues(const QString &table, const QStringList &pos, const QStringList &values);    //добавить запись в таблицу
    bool createTable(const QString &table,const QString &structure);      //создать таблицу
    int countRows(const QString &table);     //кол-во записей в таблице
    float previousValue(const int varid);         //последнее (по времени) значение переменной
    QSqlQuery* exec(const QString &querytext);      //выполить произвольный запрос
    void close();
    DBConnectParams *connectParams;
    DBConnectParams *serviceParams;
private:
    QSqlDatabase db;    //класс для доступа к
    char openDataBase(const DBConnectParams *params);   //внутренняя функция для установки соединения с БД
    bool createDataBase(); //создание БД
    bool forward_only; //TODO - setForwardOnly!!!!!!!!!!!!!!!!!
    bool connected = false;
};

#endif // DATABASE_H
