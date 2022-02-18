#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include <QDebug>
#include <QSql>
#include <QSqlQueryModel>
#include <QtWidgets>
#include "sql_globals.h"
#include "customdelegate.h"
#include "customquerymodel.h"
#include "customsortmodel.h"

class CustomTableView : public QTableView
//отображение таблицы, добавлены сигналы\слоты для обработки событий мыши
{
    Q_OBJECT
    Q_PROPERTY(QStringList hiddenColumns READ hiddenColumns WRITE setHiddenColumns)
public:
    CustomTableView(QWidget *parent = 0);
    void init(QSortFilterProxyModel *model, CustomDelegate *delegate); //начальная инициализация
    void setHiddenColumns(const QStringList &list);
    QStringList hiddenColumns();
    void updateColumns();

private slots:
    void onHoverIndexChanged(QModelIndex& index);   //при смене ячейки, над которой указатель мыши, выводит всплывающую подсказку
    void customMenuRequested(QPoint pos);   //слот, отображающий всплывающее меню при щелчке правой кнопкой мыши по заголовку таблицы
    void sortingRequested(int logicalIndex, Qt::SortOrder order);//при нажатии на заголовок таблицы вызывает сортировку

signals:
    void hoverIndexChanged(QModelIndex& index);//отслеживание движения мыши

private:
    void mouseMoveEvent(QMouseEvent *event);//отслеживание движения мыши, посылает сигнал о смене ячейки
    QStringList hidden_columns;
};

#endif // CUSTOMTABLEVIEW_H
