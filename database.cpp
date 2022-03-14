#include "database.h"

DBConnectParams::DBConnectParams(const QString &name,
                                 const QString &host,
                                 const QString &addr,
                                 const QString &user,
                                 const QString &password,
                                 const QString &port,
                                 const QString &driver)
{
//TODO: проверка всех аргументов через RegExp
QSettings hosts(HOSTS_CONFIG_FILE,QSettings::IniFormat);

this->name = name;
this->user = user;
this->driver = driver;
this->password = password;
this->port = port;
this->hostName = host;
QRegExp rx(QString("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$")); //RegExp for IP-address
if (rx.exactMatch(addr))
  this->hostAddress = addr;
else
  this->hostAddress = hosts.value(this->hostName,GLOBALS::DEFAULT_DB_HOSTADDRESS).toString();
}

DBConnectParams::~DBConnectParams()
{
toDebug("DBConnectOptions destructor "+name,DT_DATABASE);
}


QString DBConnectParams::getDBName() const {return name;}
QString DBConnectParams::getUserName() const{return user;}
QString DBConnectParams::getPassword() const{return password;}
QString DBConnectParams::getPort() const{return port;}
QString DBConnectParams::getHostName() const{return hostName;}
QString DBConnectParams::getHostAddr() const{return hostAddress;}
QString DBConnectParams::getDriver() const{return driver;}

QString DBConnectParams::toConnectParamsString() const
{
QString result = "";
if (hostName != nullptr)
  result += QString("host=%1;").arg(hostName);
if (hostAddress != nullptr)
  result += QString("hostaddr=%1;").arg(hostAddress);
result += QString("port=%3;dbname=%4;user=%5;password=%6").arg(port,name,user,password);
return result;
}





//конструктор
DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

//деструктор
DataBase::~DataBase()
{
toDebug("Destructor, Closing DB",DT_DATABASE);
close();
}

QSqlDatabase* DataBase::getDbPointer()
{
return &db;
}

DBConnectParams* DataBase::getConnectParams()
{
return &connectParams;
}

bool DataBase::isConnected()
{
return connected;
}

//соединение с БД, либо создание, если БД не существует
bool DataBase::connectDataBase(const DBConnectParams &params,
                               const bool createIfNotAvailable)
{
switch(openDataBase(params))
  {
  case 0: //соединение удалось
    connectParams = params;
    connected = true;
    return true;
  case 1: //БД с таким именем не существует
    if (createIfNotAvailable)
      {
      createDataBase(params.getDBName());    //создание БД
      return connectDataBase(params,false);   //попытка соединиться еще раз
      }
    break;
  }
  return false;   //соединение не удалось
  connected = false;
}

//внутренняя функция для установки соединения с БД
char DataBase::openDataBase(const DBConnectParams &params)
{
toDebug("connecting to "+params.getDBName()+" DB with driver = "+params.getDriver()+" on host= "+params.getHostName(),DT_DATABASE);
//создание и инициализация QSqlDatabase
db = QSqlDatabase::addDatabase(params.getDriver(),params.getDBName());
toDebug("DB added, setting options..."+params.toConnectParamsString(),DT_DATABASE);
db.setConnectOptions(params.toConnectParamsString());
toDebug("Options set, opening...",DT_DATABASE);
if (!db.open()) //Если соединение не удалось
  {
  if (db.lastError().databaseText() == QString("ВАЖНО:  база данных \""+params.getDBName()+"\" не существует\n"))    //если БД с таким именем не существует
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
bool DataBase::createDataBase(const DBConnectParams &params)
{
toDebug("Attemting to create DB, opening "+QString(GLOBALS::SERVICE_DB_NAME),DT_DATABASE);
if (openDataBase(DBConnectParams(GLOBALS::SERVICE_DB_NAME,
                                 GLOBALS::SERVICE_DB_HOST,
                                 GLOBALS::SERVICE_DB_HOSTADDRESS,
                                 GLOBALS::SERVICE_DB_USERNAME,
                                 GLOBALS::SERVICE_DB_PASSWORD))==0) //если удалось соединиться с сервисной БД
  {
  QSqlQuery query(db);
  if (query.exec("CREATE DATABASE "+params.getDBName()+" WITH OWNER = "+params.getUserName()+" ENCODING = 'UTF8'TABLESPACE = pg_default CONNECTION LIMIT = -1;"))
    {
    //если запрос на создание БД выпонился успешно
    toDebug(" DB created successfully",DT_DATABASE);
    return true;
    }
  //запрос на создание БД не выполнился
  toDebug("Failed to create "+params.getDBName()+query.lastError().text(),DT_ERROR);
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



