#include "database.h"


//Класс для хранения и представления параметров подключения к БД
//Инкапсулирует параметры, умеет возвращать строку подключения
DBConnectParams::DBConnectParams(const CONNECTION_PARAMS &params)
{
    this->params=params;
}

DBConnectParams::~DBConnectParams()
{

}

const CONNECTION_PARAMS* DBConnectParams::getParams()const
{
  return &params;
}

//геттеры и сеттеры для параметров подключения
QString DBConnectParams::getHostName() const {return params.hostName;}
void DBConnectParams::setHostName(const QString &hostname){this->params.hostName = hostname;}

QString DBConnectParams::getHostAddr() const {return params.hostAddress;}
void DBConnectParams::setHostAddr(const QString &hostaddr)
{
QRegExp rx(QString("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$")); //RegExp for IP-address
if (rx.exactMatch(hostaddr))
  this->params.hostAddress = hostaddr;
else
  this->params.hostAddress = GLOBALS::DEFAULT_DB_HOSTADDRESS;
}

QString DBConnectParams::getDBName() const {return params.dbName;}
void DBConnectParams::setDBName(const QString &dbname){this->params.dbName = dbname;}

QString DBConnectParams::getDBUser() const {return params.dbUser;}
void DBConnectParams::setDBUser(const QString &dbuser){this->params.dbUser = dbuser;}

QString DBConnectParams::getDBPassword() const {return params.dbPassword;}
void DBConnectParams::setDBPassword(const QString &dbpassword){this->params.dbPassword = dbpassword;}

QString DBConnectParams::getDBPort() const {return params.dbPort;}
void DBConnectParams::setDBPort(const QString &dbport)
{
QRegExp rx(QString("^\\d+$")); //RegExp for integer
if (rx.exactMatch(dbport))
  this->params.dbPort = dbport;
else
  this->params.dbPort = GLOBALS::DEFAULT_DB_PORT;
}

QString DBConnectParams::getDriver() const {return params.driver;}
void DBConnectParams::setDriver(const QString &driver)
{
if (GLOBALS::AVAILABLE_DRIVERS.contains(driver))
    this->params.driver = driver;
else
    this->params.driver = GLOBALS::DEFAULT_DB_DRIVER;
}

//Специальная строка, которую нужно передать драйверу БД
QString DBConnectParams::toConnectParamsString() const
{
QString result = "";
if ((!params.hostName.isNull()) && (!params.hostName.isEmpty()))
  result += QString("host=%1;").arg(params.hostName);
if ((!params.hostAddress.isNull()) && (!params.hostAddress.isEmpty()))
  result += QString("hostaddr=%1;").arg(params.hostAddress);
result += QString("port=%3;dbname=%4;user=%5;password=%6").arg(params.dbPort,params.dbName,params.dbUser,params.dbPassword);
return result;
}


//конструктор
DataBase::DataBase(QObject *parent) : QObject(parent)
{
connectParams=NULL;
serviceParams=NULL;
}

//деструктор
DataBase::~DataBase()
{
delete connectParams;
delete serviceParams;
toDebug("Destructor, Closing DB",DT_DATABASE);
close();
}

QSqlDatabase* DataBase::getDbPointer()
{
return &db;
}


bool DataBase::isConnected()
{
return connected;
}

//соединение с БД, либо создание, если БД не существует
bool DataBase::connectDataBase(const bool createIfNotAvailable)
{
switch(openDataBase(connectParams))
  {
  case 0: //соединение удалось
    connected = true;
    return true;
  case 1: //БД с таким именем не существует
    if (createIfNotAvailable)
      {
      createDataBase();    //создание БД
      return connectDataBase(false);   //попытка соединиться еще раз
      }
    break;
  }
  return false;   //соединение не удалось
  connected = false;
}

//внутренняя функция для установки соединения с БД
char DataBase::openDataBase(const DBConnectParams *params)
{
if (params==nullptr)
{
    toDebug("Connection params are NULL",DT_ERROR);
    return 2;
}

toDebug("connecting to "+params->getDBName()+" DB with driver = "+params->getDriver()+" on host= "+params->getHostName(),DT_DATABASE);
//создание и инициализация QSqlDatabase
db = QSqlDatabase::addDatabase(params->getDriver(),params->getDBName());
toDebug("DB added, setting options..."+params->toConnectParamsString(),DT_DATABASE);
db.setConnectOptions(params->toConnectParamsString());
toDebug("Options set, opening...",DT_DATABASE);
if (!db.open()) //Если соединение не удалось
  {
  if (db.lastError().databaseText() == QString("ВАЖНО:  база данных \""+params->getDBName()+"\" не существует\n"))    //если БД с таким именем не существует
    {
    toDebug("DB not found "+db.lastError().nativeErrorCode()+db.lastError().text()+db.lastError().type(),DT_WARNING);
    return 1;
    }
  else    //другая ошибка
    {
    toDebug("DB connection error"+db.lastError().databaseText()+db.lastError().nativeErrorCode(),DT_ERROR);
    return 2;
    }
  }
toDebug("DB connected successfully",DT_DATABASE);
return 0;
}

//создание БД
bool DataBase::createDataBase()
{
if (connectParams==nullptr)
{
  toDebug("Connection params are NULL",DT_ERROR);
  return false;
}
toDebug("Attemting to create DB",DT_DATABASE);
if (openDataBase(serviceParams)==0) //если удалось соединиться с сервисной БД
  {
  QSqlQuery query(db);
  if (query.exec("CREATE DATABASE "+connectParams->getDBName()+" WITH OWNER = "+connectParams->getDBUser()+" ENCODING = 'UTF8'TABLESPACE = pg_default CONNECTION LIMIT = -1;"))
    {
    //если запрос на создание БД выпонился успешно
    toDebug(" DB created successfully",DT_DATABASE);
    return true;
    }
  //запрос на создание БД не выполнился
  toDebug("Failed to create "+connectParams->getDBName()+query.lastError().text(),DT_ERROR);
  db.close();
  toDebug("service DB closed",DT_DATABASE);
  }
return false;
}

//добавление данных в заданные столбцы заданной таблицы
void DataBase::insertValues(const QString &table, const QStringList &pos, const QStringList &values)
{
//подготовка запроса
//TODO:
//static QSqlQuery query(db);
//query.prepare("INSERT INTO :table (:columns) VALUES (:items)");
QString querytext = "INSERT INTO "+table+" (";

for(const QString &value:qAsConst(pos))
  querytext += value+", ";
querytext.chop(2);
querytext += ") VALUES (";
for(const QString &value:qAsConst(values))
  querytext += value+", ";
querytext.chop(2);
querytext += ")";
exec(querytext);
}

//создание таблицы с заданной структурой столбцов
bool DataBase::createTable(const QString &table,const QString &structure)
{
QSqlQuery query(db);
if(!query.exec( "CREATE TABLE IF NOT EXISTS " + table + " " + structure))
  {
  //если запрос не был выполнен
  toDebug("cannot create table "+table+query.lastError().text(),DT_ERROR);
  return false;
  }
if(!query.exec( "ALTER SEQUENCE "+table+"_id_seq RESTART WITH 0 INCREMENT BY 1 MINVALUE 0"))
  {
  //если запрос не был выполнен
  toDebug("cannot alter index of "+table+query.lastError().text(),DT_ERROR);
  return false;
  }

return true;
}

//возвращает кол-во записей в таблице
int DataBase::countRows(const QString &table)
{
QSqlQuery query(db);
if(!query.exec( "SELECT * FROM " + table ))
  {
  //если запрос не был выполнен
  toDebug("Can not get number of rows in "+table+query.lastError().text(),DT_ERROR);
  return -1;
  }
return query.size();//кол-во записей
}

//возвращает последнее(по времени) значение переменной
float DataBase::previousValue(int varid)
{
QSqlQuery query(db);
if(!query.exec("select val from vals where varid="+QString::number(varid)+" order by time desc"))
  {
  //если запрос не был выполнен
  toDebug("Can not get previous value of "+QString::number(varid)+query.lastError().text(),DT_ERROR);
  return -1;
  }
  if (query.first())
    return query.value(0).toFloat();//значение переменной
  return -1;
}

//выполнение произвольного SQL запроса
QSqlQuery* DataBase::exec(const QString &querytext)
{
if (!db.isOpen())
  {
  toDebug("Database is not ready! ",DT_ERROR);
  return nullptr;
  }
QSqlQuery* query;
query = new QSqlQuery(db);
toDebug("Executing: "+querytext,DT_SQL);
if(!query->exec(querytext))
  //если запрос не был выполнен
  toDebug("QUERY FAILED!!"+query->lastQuery()+ query->lastError().text()+ query->lastError().nativeErrorCode(),DT_ERROR);
return query;
}

void DataBase::close()
{
toDebug("Closing DB...",DT_DATABASE);
connected = false;
db.close();
//db.removeDatabase(connectOptions.getDBName());

}



