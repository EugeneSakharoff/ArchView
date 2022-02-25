#ifndef ITEMSELECTOR_H
#define ITEMSELECTOR_H

#include <QObject>
#include <QWidget>
#include <QListView>>
#include "sql_query.h"
#include "database.h"
#include "comboboxselector.h"
#include "controlbuttons.h"



class ItemSelector: public QObject
{
    Q_OBJECT
public:
    ItemSelector(QWidget* parent);
    ~ItemSelector();
    void init(QSqlQuery *name_descr_query, QSqlQuery *group_query);
    void init();
    void reset();
    QList<SqlFilter> getFilters();
    QSet<QString> varSet();



public slots:
    void varSelectorChanged();
    void groupSelectorChanged();
    void descrSelectorChanged();

signals:
    void changed();

private:
    void addValue();
    QSqlQueryModel* model;
    QSqlQuery *init_query;
    QSqlQueryModel* group_model;
    QDataWidgetMapper *mapper;
    ComboBoxSelector* varSelector;
    ComboBoxSelector* groupSelector;
    ComboBoxSelector* descrSelector;
    ControlButtons* buttons;
    QSet<QString> current_set;
};

#endif // ITEMSELECTOR_H
