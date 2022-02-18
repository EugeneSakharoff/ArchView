#ifndef INTERVALSELECTOR_H
#define INTERVALSELECTOR_H

#include <QObject>
#include <QWidget>
#include "timeselector.h"
#include "intervalslider.h"
class IntervalSelector: public QObject
{
    Q_OBJECT
public:
    IntervalSelector(QWidget *parent);
    ~IntervalSelector();
    QPair<QString,QString> getInterval();
    void init();
    bool init(QSqlQuery* query);
    void reset();

public slots:
    void startSelectorChanged();
    void endSelectorChanged();
    void sliderChanged(int min, int max);
signals:
    void changed();

private:
    TimeSelector* startSelector;
    TimeSelector* endSelector;
    IntervalSlider* slider;
    QSqlQuery* init_query;
};

#endif // INTERVALSELECTOR_H
