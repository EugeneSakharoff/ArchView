#ifndef ITEMSELECTOR_H
#define ITEMSELECTOR_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include "database.h"
#include "comboboxselector.h"
#include "controlbuttons.h"



class ItemSelector: public QObject
{
    Q_OBJECT
public:
    ItemSelector(QWidget* parent);
    ~ItemSelector();
    bool init(QSqlDatabase *db);
    void clear();
    void reset();
    void update();
    QSet<QString> varSet();
    QSet<QString> fullSet();


public slots:
    void varSelectorChanged();
    void groupSelectorChanged();
    void descrSelectorChanged();

signals:
    void changed();

private:
    void addValue();
    void soloValue();
    QSqlQueryModel* model;
    QSqlQuery *namedescr_query;
    QSqlQuery *group_query;
    QSqlQueryModel* group_model;
    QDataWidgetMapper *mapper;
    ComboBoxSelector* varSelector;
    ComboBoxSelector* groupSelector;
    ComboBoxSelector* descrSelector;
    ControlButtons* buttons;
    QSet<QString> current_set;
};

#endif // ITEMSELECTOR_H
