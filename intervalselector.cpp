#include "intervalselector.h"
#include "sql_query.h"

//класс содержит в себе два TimeSelector-а (начало и конец) и IntervalSlider, обеспечивает их взаимодействие
IntervalSelector::IntervalSelector(QWidget *parent)
{
startSelector = new TimeSelector(parent, "Начало");
endSelector = new TimeSelector(parent, "Конец");
slider = new IntervalSlider(parent,"");

minmax_query = nullptr;
stages_query = nullptr;
}

IntervalSelector::~IntervalSelector()
{
delete startSelector;
delete endSelector;
if (minmax_query!=nullptr)
    delete minmax_query;
if (stages_query!=nullptr)
    delete stages_query;
}

//возвращает текущий выбранный интервал
QPair<QString,QString> IntervalSelector::getInterval()
{
if (startSelector->getTime()>endSelector->getTime())
  {
  toDebug("Start time= "+startSelector->getTime().toString()+ " > end time= "+endSelector->getTime().toString(),DT_WARNING);
  reset();
  }
return QPair<QString,QString>(startSelector->getTimeStr(),endSelector->getTimeStr());
}

//пустой инит
void IntervalSelector::clear()
{
disconnect(startSelector,&TimeSelector::changed,this,&IntervalSelector::startSelectorChanged);
disconnect(slider,&IntervalSlider::changed,this,&IntervalSelector::sliderChanged);
disconnect(endSelector,&TimeSelector::changed,this,&IntervalSelector::endSelectorChanged);
startSelector->clear();
endSelector->clear();
slider->clear();
if (minmax_query!=nullptr)
    delete minmax_query;
if (stages_query!=nullptr)
    delete stages_query;
}

//инит через два sql запроса, один возвращает минимальное и максимальное значения времени в БД
//Второй возвращает временные точки для определения этапов
bool IntervalSelector::init(QSqlDatabase *db)
{
minmax_query = new QSqlQuery(*db);
stages_query = new QSqlQuery(*db);
using namespace SQL_GLOBALS;
minmax_query->prepare(SqlSelectQuery::buildSelectQuery(
                          { QString( "MIN(%1)" ).arg( DATETIME_COLUMN ), QString( "MAX(%1)" ).arg( DATETIME_COLUMN ) },
                           QString( "(%1) tmp" )
                               .arg( SqlSelectQuery::buildUnion(
                                   SqlSelectQuery::buildSelectQuery( { DATETIME_COLUMN }, VALUES_TABLE ),
                                   SqlSelectQuery::buildSelectQuery( { DATETIME_COLUMN }, MESSAGES_TABLE ) ) ) ) );
stages_query->prepare(SqlSelectQuery::buildSelectQuery( { MESSAGE_COLUMN, DATETIME_COLUMN }, MESSAGES_TABLE, {},
                                                         { SqlFilter( MESSAGE_COLUMN, GLOBALS::STAGE_MSGS ) }));

update();
return 1;
}

void IntervalSelector::reset()
{
startSelector->setTime(minmax_query->value(0).toDateTime());
endSelector->setTime(minmax_query->value(1).toDateTime());
slider->setValues(minmax_query->value(0).toDateTime().toSecsSinceEpoch(),minmax_query->value(1).toDateTime().toSecsSinceEpoch());
}

//сигналы эмитятся каждый раз, когда меняется один из элементов
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

void IntervalSelector::update()
{
disconnect(startSelector,&TimeSelector::changed,this,&IntervalSelector::startSelectorChanged);
disconnect(slider,&IntervalSlider::changed,this,&IntervalSelector::sliderChanged);
disconnect(endSelector,&TimeSelector::changed,this,&IntervalSelector::endSelectorChanged);
minmax_query->exec();
stages_query->exec();
startSelector->init(minmax_query);
endSelector->init(minmax_query);
slider->init(minmax_query,stages_query);
startSelector->setTime(QDateTime::fromSecsSinceEpoch(slider->getMin()));
endSelector->setTime(QDateTime::fromSecsSinceEpoch(slider->getMax()+1));
connect(startSelector,&TimeSelector::changed,this,&IntervalSelector::startSelectorChanged);
connect(slider,&IntervalSlider::changed,this,&IntervalSelector::sliderChanged);
connect(endSelector,&TimeSelector::changed,this,&IntervalSelector::endSelectorChanged);
}
