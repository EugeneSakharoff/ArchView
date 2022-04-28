#include "sql_query.h"

//Вспомогательные классы, чтобы составлять сложные многоуровневые SQL запросы

//----------------------------------------------------------------------------------------
//конструкция типа JOIN table ON col1=col2
SqlJoin::SqlJoin(const QString &table,const QString &col1,const QString &col2)
{
m_table = table;
m_col1 = col1;
m_col2 = col2;
}

SqlJoin::SqlJoin(const char* table,const char* col1,const char* col2)
{
m_table = table;
m_col1 = col1;
m_col2 = col2;
}

QString SqlJoin::toString() const
{
return "JOIN "+m_table+" ON "+m_col1+ "="+m_col2;
}

//----------------------------------------------------------------------------------------
//конструкция типа WHERE value IN (v1,v2...)
SqlFilter::SqlFilter(const QString &item,const QStringList &values)
{
data.first = item;
data.second = values;
type = 0;
}
//конструкция типа WHERE value IN (v1,v2...)
SqlFilter::SqlFilter(const QString &item,const QSet<QString> &values)
{
if (!values.isEmpty())
  {
  data.first = item;
  QStringList second;
  foreach (QString s, values)
      second.append(s);
  data.second = second;
  }
else
  {
  data.first = "";
  data.second = QStringList{};
  }
type = 0;
}

//конструкция типа WHERE value BETWEEN (v1 AND v2)
SqlFilter::SqlFilter(const QString &item, const QString &min, const QString &max)
{
data.first = item;
data.second = QStringList({min,max});
type = 1;
}

SqlFilter::SqlFilter(const QString &item, const QPair<QString,QString> &interval)
{
data.first = item;
data.second = QStringList({interval.first,interval.second});
type = 1;
}

//возвращает строку
QString SqlFilter::toString() const
{
if (data.first.isEmpty()||data.second.isEmpty())
    return "";
if (type)
  {
  QString result = data.first+" BETWEEN ";
  result += "'"+data.second.at(0)+"' AND '" + data.second.at(1)+"'";
  return result;
  }
QString result = data.first+" IN (";
for(const QString &value:qAsConst(data.second))
  result += "'"+value+"', ";
result.chop(2);
result += ")";
return result;
}

//----------------------------------------------------------------------------------------
//Класс строит сложный запрос SELECT, используя предыдущие 2 класса
SqlSelectQuery::SqlSelectQuery()
{
m_items = QStringList();
m_table = QString();
m_joins = QList<SqlJoin>();
m_filters = QList<SqlFilter>();
m_distinct = false;
m_orderby = QString();
m_order_desc = false;
}

SqlSelectQuery::SqlSelectQuery(const QStringList &items,
                               const QString &table,
                               const QList<SqlJoin> &joins,
                               const QList<SqlFilter> &filters,
                               const bool distinct,
                               const QString &orderby,
                               const bool order_desc)
{
m_items = items;
m_table = table;
m_joins = joins;
m_filters = filters;
m_distinct = distinct;
m_orderby = orderby;
m_order_desc = order_desc;
}


QString SqlSelectQuery::buildSelectQuery(const QStringList &items,
                                         const QString &table,
                                         const QList<SqlJoin> &joins,
                                         const QList<SqlFilter> &filters,
                                         const bool distinct,
                                         const QString &orderby,
                                         const bool order_desc)
{
QString querytext = "SELECT ";
if (distinct) querytext += "DISTINCT ";

//столбцы, которые выбираем
if (items.length())
  for (const QString &item : qAsConst(items))
    querytext += "\n"+item+", ";
else
  querytext += "*  ";

querytext.chop(2);

//из таблицы
querytext += "\nFROM "+table;

if (joins.length())
  for (const SqlJoin &j : qAsConst(joins))
    querytext += "\n"+j.toString()+" ";

//фильтры
if (filters.length())
  {
  querytext += "\nWHERE ";
  for(const SqlFilter &filter : qAsConst(filters))
    {
    querytext += filter.toString();
    querytext += "\n AND ";
    }
  querytext.chop(6);
  }

//сортировка
if (!orderby.isEmpty())
  {
  querytext += "\nORDER BY " + orderby;
  if (order_desc) querytext += " DESC";
  }

return querytext;
}

QString SqlSelectQuery::buildSelectQueryS(const QStringList &items,
                                const QString &table,
                                const QString &joins,
                                const QString &filters,
                                const bool distinct,
                                const QString &orderby,
                                const bool order_desc)
{
    QString querytext = "SELECT ";
    if (distinct) querytext += "DISTINCT ";

    //столбцы, которые выбираем
    if (items.length())
      for (const QString &item : qAsConst(items))
        querytext += "\n"+item+", ";
    else
      querytext += "*  ";

    querytext.chop(2);

    //из таблицы
    querytext += "\nFROM "+table;

    if (!joins.isEmpty())
      querytext += " "+joins;

    if (!filters.isEmpty())
          querytext += " "+filters;

    //сортировка
    if (!orderby.isEmpty())
      {
      querytext += " \nORDER BY " + orderby;
      if (order_desc) querytext += " DESC";
      }

    return querytext;
}

//строит запрос типа SELECT query1 UNION query2
QString SqlSelectQuery::buildUnion(const QString &query1, const QString &query2,
                                const QString &orderby,const bool order_desc)
{
if (query1.isEmpty()) return query2;
if (query2.isEmpty()) return query1;
QString querytext = query1+QString("\nUNION\n")+query2;
//сортировка
if (!orderby.isEmpty())
  {
  querytext += "\nORDER BY " + orderby;
  if (order_desc) querytext += " DESC";
  }
return querytext;
}

QString SqlSelectQuery::toString() const
{
return SqlSelectQuery::buildSelectQuery(m_items,m_table,m_joins,m_filters,m_distinct,m_orderby,m_order_desc);
}

void SqlSelectQuery::resetFilters(const QList<SqlFilter> &filters)
{
m_filters = filters;
}

