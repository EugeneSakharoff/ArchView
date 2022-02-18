#include "timeselector.h"

TimeEdit::TimeEdit(QWidget *parent):QDateTimeEdit(parent)
{

}

void TimeEdit::mousePressEvent(QMouseEvent *event)
{
if (event->button() == Qt::LeftButton)
  {
  step = (event->pos().y()>height()/2);
  timer_num = startTimer(UI_GLOBALS::CONTROLS_TIMER_INTERVAL);
  }
}

void TimeEdit::mouseReleaseEvent(QMouseEvent *event)
{
if (event->button() == Qt::LeftButton)
  killTimer(timer_num);
}

void TimeEdit::timerEvent(QTimerEvent *event)
{
    switch (currentSectionIndex())
      {
      case 0: setDateTime(dateTime().addYears((1-2*step)*1));break;
      case 1: setDateTime(dateTime().addMonths((1-2*step)*1));break;
      case 2: setDateTime(dateTime().addDays((1-2*step)*1));break;
      case 3: setDateTime(dateTime().addSecs((1-2*step)*3600));break;
      case 4: setDateTime(dateTime().addSecs((1-2*step)*60));break;
      case 5: setDateTime(dateTime().addSecs((1-2*step)*1));break;
      }
}


TimeSelector::TimeSelector(QWidget *parent,const QString labeltext):ControlElement(parent,labeltext)
{
timeEdit = new TimeEdit(groupBox);
timeEdit->setDisplayFormat(GLOBALS::DEFAULT_DATETIME_FORMAT);
layout->addWidget(timeEdit);

}

TimeSelector::~TimeSelector()
{
delete timeEdit;
}

QString TimeSelector::getTimeStr() const
{
return timeEdit->dateTime().toString(GLOBALS::DEFAULT_DATETIME_FORMAT);
}

QDateTime TimeSelector::getTime() const
{
return timeEdit->dateTime();
}


void TimeSelector::setTime(const QDateTime &time)
{
timeEdit->setDateTime(time);
}

void TimeSelector::init()
{
toDebug("timeselector default init",DT_CONTROLS);
timeEdit->setDateTime(QDateTime::currentDateTime());
//timeEdit->setDateTimeRange(QDateTime::fromSecsSinceEpoch(0),QDateTime::currentDateTime());
timeEdit->setEnabled(false);
disconnect(timeEdit,&QTimeEdit::editingFinished,this,&TimeSelector::emitChanged);
}

bool TimeSelector::init(QSqlQuery* query)
{
QDateTime min,max;
try
  {
  toDebug("timeselector init with query: "+query->lastQuery(),DT_CONTROLS);
  if (query->first())
    {
    min = query->value(0).toDateTime();
    max = query->value(1).toDateTime();
    }
  //timeEdit->setDateTimeRange(min,max);
  timeEdit->setDateTime(max);
  timeEdit->setEnabled(true);
  timeEdit->setCurrentSectionIndex(5);
  connect(timeEdit,&QTimeEdit::editingFinished,this,&TimeSelector::emitChanged);
  return true;
  }
catch (...)
  {
  toDebug("TimeSelector initialization failed!",DT_ERROR);
  init();
  return false;
  }
}

void TimeSelector::reset()
{
toDebug("timeselector reset",DT_CONTROLS);
timeEdit->setDateTime(QDateTime::currentDateTime());
emit changed();
}


void TimeSelector::emitChanged()
{
emit changed();
}


