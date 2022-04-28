#ifndef INTERVALSELECTOR_H
#define INTERVALSELECTOR_H

#include <QObject>
#include <QWidget>
#include "timeselector.h"
#include "intervalslider.h"

//класс содержит в себе два TimeSelector-а (начало и конец) и IntervalSlider, обеспечивает их взаимодействие
class IntervalSelector: public QObject
{
    Q_OBJECT
public:
    IntervalSelector(QWidget *parent);
    ~IntervalSelector();
    QPair<QString,QString> getInterval();
    void clear();
    bool init(QSqlDatabase* db);
    void reset();
    void update();

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
    QSqlQuery* minmax_query;
    QSqlQuery* stages_query;
};

#endif // INTERVALSELECTOR_H
