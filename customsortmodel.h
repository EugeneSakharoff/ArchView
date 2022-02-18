#ifndef CUSTOMSORTMODEL_H
#define CUSTOMSORTMODEL_H

#include <QSortFilterProxyModel>
#include <QObject>
#include "customquerymodel.h"

class CustomSortModel : public QSortFilterProxyModel
//класс нужен для "правильной" сортировки столбцов, переопределяет функцию lessThan()
{
    Q_OBJECT
public:
    explicit CustomSortModel(QObject *parent = nullptr);
    int aliasToHeaderIndex(const QString &alias) const; //индекс столбца по псевдониму
    int headerToIndex(const QString &header) const; //индекс столбца по псевдониму
    QStringList headersAliases() const;

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right); //корректное сравнение значений
};

#endif // CUSTOMSORTMODEL_H
