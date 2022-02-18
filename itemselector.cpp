#include "itemselector.h"


ItemSelector::ItemSelector(QWidget* parent)
{

groupSelector = new ComboBoxSelector(parent, "Группа",true);
varSelector = new ComboBoxSelector(parent, "Переменная",true);
descrSelector = new ComboBoxSelector(parent, "Описание",false);

model = new QSqlQueryModel(this);
group_model = new QSqlQueryModel(this);
mapper = new QDataWidgetMapper(this);

}

ItemSelector::~ItemSelector()
{
delete varSelector;
delete groupSelector;
delete descrSelector;
delete model;
delete group_model;
delete mapper;

}

QList<SqlFilter> ItemSelector::getFilters()
{
  QList<SqlFilter> filters;
  if (!varSelector->currentText().isEmpty())
      filters.append(SqlFilter(SQL_GLOBALS::VARNAME,varSet()));
  return filters;
}

QSet<QString> ItemSelector::varSet()
{
QSet<QString> var_set;
if (varSelector->currentText().isEmpty())
  for (int i=0;i<model->rowCount();++i)
    var_set.insert(model->data(model->index(i,0)).toString());
else
    var_set.insert(varSelector->currentText());
return var_set;
}


void ItemSelector::init(QSqlQuery *name_descr_query, QSqlQuery *group_query)
{
toDebug("ItemSelector init (query)",DT_CONTROLS);
init_query = name_descr_query;
model->setQuery(*name_descr_query);
group_model->setQuery(*group_query);
mapper->setModel(model);
varSelector->init(model,0,mapper,0);
groupSelector->init(group_model,0);
descrSelector->init(model,2,mapper,2);
connect(descrSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::descrSelectorChanged);
connect(groupSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::groupSelectorChanged);
connect(varSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::varSelectorChanged);
qDebug()<<mapper->currentIndex();
//connect(varSelector,&ComboBoxSelector::addClicked,this,&ItemSelector::varSelectorChanged);
//connect(varSelector,&ComboBoxSelector::soloClicked,this,&ItemSelector::varSelectorChanged);
//connect(groupSelector,&ComboBoxSelector::addClicked,this,&ItemSelector::groupSelectorChanged);
//connect(groupSelector,&ComboBoxSelector::soloClicked,this,&ItemSelector::groupSelectorChanged);
//mapper->toFirst();
}

void ItemSelector::init()
{
toDebug("ItemSelector init (empty)",DT_CONTROLS);
varSelector->init();
groupSelector->init();
descrSelector->init();
}

void ItemSelector::reset()
{
varSelector->reset();
groupSelector->reset();
descrSelector->reset();
}

void ItemSelector::varSelectorChanged()
{
mapper->setCurrentIndex(varSelector->currentIndex());
if (varSelector->currentIndex()<0)
  descrSelector->reset();
emit changed();
}

void ItemSelector::descrSelectorChanged()
{
mapper->setCurrentIndex(descrSelector->currentIndex());
if (descrSelector->currentIndex()<0)
  varSelector->reset();
emit changed();
}

void ItemSelector::groupSelectorChanged()
{
using namespace SQL_GLOBALS;
if (groupSelector->currentIndex()<0)
  init_query->exec(SqlSelectQuery::buildSelectQuery({NAME_COLUMN,GROUPID_COLUMN,DESCRIPTION_COLUMN},DESCRIPTIONS_TABLE,{},
                                                    {},
                                                    false,NAME_COLUMN));
else
  init_query->exec(SqlSelectQuery::buildSelectQuery({NAME_COLUMN,GROUPID_COLUMN,DESCRIPTION_COLUMN},DESCRIPTIONS_TABLE,{},
                                                    {SqlFilter(GROUPID,QStringList(QString::number(groupSelector->currentIndex())))},
                                                    false,NAME_COLUMN));
model->setQuery(*init_query);
descrSelector->reset();
varSelector->reset();
}



