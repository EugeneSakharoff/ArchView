#ifndef CONTROLELEMENT_H
#define CONTROLELEMENT_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSqlQuery>
#include <QDebug>

#include "ui.h"
#include "globals.h"

//Абстрактный родительский класс для представления элементов управления запросом (переменные, временной интервал и т.п.)

class ControlElement: public QObject
{
    Q_OBJECT
public:
    ControlElement(QWidget *parent, const QString& labeltext);
    ~ControlElement();
    virtual void init()=0;
    virtual void reset()=0;
    virtual void emitChanged()=0;

signals:
    void changed();

protected:
    QLabel *label;
    QGroupBox *groupBox;
    QHBoxLayout *layout;
    QSqlQuery *init_query;
};

#endif // CONTROLELEMENT_H
