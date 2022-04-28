#ifndef CUSTOMQUERYMODEL_H
#define CUSTOMQUERYMODEL_H

#include <QSqlQueryModel>
#include <QObject>
#include <QColor>
#include <QDebug>
#include "sql_globals.h"
#include "globals.h"
//класс для получения данных из БД по запросу, наследует QSqlQueryModel с корректным отображением заголовков столбцов
class CustomQueryModel : public QSqlQueryModel

{
    Q_OBJECT
public:
    explicit CustomQueryModel(QObject *parent = nullptr);
    void updateQuery(const QString &query,const QStringList &aliases,const QSqlDatabase &db);   //обработчик запроса, показывает корректные названия столбцов
    int aliasToHeaderIndex(const QString &alias) const;              //индекс столбца по псевдониму
    int headerToIndex(const QString &header) const;              //индекс столбца по псевдониму
    QVariant data(const QModelIndex &idx, int role) const;
    QStringList headersAliases() const;
    void clear();
private:  
    QMap<QString,int> alias_to_header_index;//отображение sql псевдонимов на номера столбцов
    QMap<QString,int> header_to_index;//отображение русскоязычных заголовков таблицы на номера столбцов
    QStringList headers_aliases;//список sql псевдонимов
};



#endif // CUSTOMQUERYMODEL_H
