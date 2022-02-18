#ifndef CUSTOMQUERYMODEL_H
#define CUSTOMQUERYMODEL_H

#include <QSqlQueryModel>
#include <QObject>
#include <QColor>
#include <QDebug>
#include "sql_globals.h"
#include "globals.h"

class CustomQueryModel : public QSqlQueryModel
//класс для получения данных из БД по запросу, наследует QSqlQueryModel с корректным отображением заголовков столбцов
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
    QMap<QString,int> alias_to_header_index;            //словарь индексов столбцов по псевдониму
    QMap<QString,int> header_to_index;
    QStringList headers_aliases;
};



#endif // CUSTOMQUERYMODEL_H
