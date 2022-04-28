#ifndef TIMESELECTOR_H
#define TIMESELECTOR_H

#include "controlelement.h"
#include <QDateTimeEdit>
#include <QMouseEvent>
#include <QTimer>

class TimeEdit : public QDateTimeEdit
{
public:
    TimeEdit(QWidget *parent);
private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *event);
    int timer_num;
    bool step;
};

class TimeSelector : public ControlElement
{
    Q_OBJECT
public:
    TimeSelector(QWidget *parent,const QString &labeltext);
    ~TimeSelector();
    QString getTimeStr() const;
    QDateTime getTime() const;
    void setTime(const QDateTime &time);
    bool init(QSqlQuery* query);
    bool init();
    void clear();
    void reset();
    void update();




protected:
    TimeEdit *timeEdit;

};

#endif // TIMESELECTOR_H
