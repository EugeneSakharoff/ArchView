#include "intervalselector.h"

IntervalSelector::IntervalSelector(QWidget *parent)
{
startSelector = new TimeSelector(parent, "Начало");
connect(startSelector,&TimeSelector::changed,this,&IntervalSelector::startSelectorChanged);
endSelector = new TimeSelector(parent, "Конец");
connect(endSelector,&TimeSelector::changed,this,&IntervalSelector::endSelectorChanged);
slider = new IntervalSlider(parent,"");
connect(slider,&IntervalSlider::changed,this,&IntervalSelector::sliderChanged);
}

IntervalSelector::~IntervalSelector()
{
delete startSelector;
delete endSelector;
delete init_query;
}

QPair<QString,QString> IntervalSelector::getInterval()
{
if (startSelector->getTime()>endSelector->getTime())
  {
  toDebug("Start time= "+startSelector->getTime().toString()+ " > end time= "+endSelector->getTime().toString(),DT_WARNING);
  reset();
  }
return QPair<QString,QString>(startSelector->getTimeStr(),endSelector->getTimeStr());
}

void IntervalSelector::init()
{
startSelector->init();
endSelector->init();
slider->init();
}

bool IntervalSelector::init(QSqlQuery* query,QSqlQuery* stages)
{
if (query==nullptr)
  {
  toDebug("intervalSelector init failed with query = NULL",DT_ERROR);
  return false;
  }
init_query = query;
stages_query = stages;
if (startSelector->init(init_query)&&endSelector->init(init_query)&&slider->init(init_query,stages_query))
  {
  toDebug("intervalSelector init with "+init_query->lastQuery()+init_query->value(0).toString()+init_query->value(1).toString()+stages->lastQuery(),DT_CONTROLS);
  reset();
  return true;
  }
else
  {
  toDebug("intervalSelector init failed with query "+init_query->lastQuery(),DT_ERROR);
  return false;
  }
}

void IntervalSelector::reset()
{
if (init_query==nullptr)
  {
  toDebug("intervalSelector reset failed with query = NULL",DT_ERROR);
  return;
  }
if (init_query->first())
  {
  toDebug("intervalSelector reset with "+init_query->lastQuery()+init_query->value(0).toString()+init_query->value(1).toString(),DT_CONTROLS);
  startSelector->setTime(init_query->value(0).toDateTime());
  endSelector->setTime(init_query->value(1).toDateTime());
  slider->setValues(init_query->value(0).toDateTime().toSecsSinceEpoch(),init_query->value(1).toDateTime().toSecsSinceEpoch());

  }
else
  toDebug("intervalSelector reset failed with query "+init_query->lastQuery(),DT_ERROR);
}

void IntervalSelector::startSelectorChanged()
{
if (startSelector->getTime()>endSelector->getTime())
  startSelector->setTime(endSelector->getTime());
slider->setValues(startSelector->getTime().toSecsSinceEpoch(),endSelector->getTime().toSecsSinceEpoch());
emit changed();
}

void IntervalSelector::endSelectorChanged()
{
if (startSelector->getTime()>endSelector->getTime())
  endSelector->setTime(startSelector->getTime());
slider->setValues(startSelector->getTime().toSecsSinceEpoch(),endSelector->getTime().toSecsSinceEpoch());
emit changed();
}

void IntervalSelector::sliderChanged(int min, int max)
{
startSelector->setTime(QDateTime::fromSecsSinceEpoch(min));
endSelector->setTime(QDateTime::fromSecsSinceEpoch(max));
emit changed();
}

