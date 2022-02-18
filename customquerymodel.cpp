#include "customquerymodel.h"

CustomQueryModel::CustomQueryModel(QObject *parent) : QSqlQueryModel(parent)
{

}

void CustomQueryModel::clear()
{
QSqlQueryModel::clear();
alias_to_header_index.clear();
headers_aliases.clear();
}

//обработчик запроса
void CustomQueryModel::updateQuery(const QString &query,const QStringList &aliases,const QSqlDatabase &db)
{
toDebug("CustomQueryModel::UpdateQuery()",DT_SQL);
alias_to_header_index.clear();
headers_aliases.clear();
header_to_index.clear();

setQuery(query,db);
if (aliases.count()!=columnCount())
  toDebug(QString("aliases.count = %1 not equal to column count = %2").arg(aliases.count(),columnCount()),DT_WARNING);
for (int i=0; i < columnCount(); ++i)
  {
  toDebug(QString("Column %1, alias %2, header %3").arg(QString::number(i),
                                                        aliases.at(i),
                                                        SQL_GLOBALS::HEADERS_MAP.value(headerData(i,Qt::Horizontal).toString())),DT_TABLE);
  alias_to_header_index.insert(aliases.at(i),i);
  setHeaderData(i, Qt::Horizontal,SQL_GLOBALS::HEADERS_MAP.value(aliases.at(i)));
  headers_aliases.append(headerData(i, Qt::Horizontal).toString());
  header_to_index.insert(headerData(i, Qt::Horizontal).toString(),i);
  }
}

//индекс столбца по псевдониму
int CustomQueryModel::aliasToHeaderIndex(const QString &alias) const
{
return alias_to_header_index.value(alias);
}

QVariant CustomQueryModel::data(const QModelIndex &idx, int role) const
{
QVariant v = QSqlQueryModel::data(idx, role);
if (role == Qt::BackgroundRole)
  return QColor(Qt::black);
return (v);
}

QStringList CustomQueryModel::headersAliases() const
{
return headers_aliases;
}

int CustomQueryModel::headerToIndex(const QString &header) const
{
return header_to_index.value(header);
}
