#include "itemselector.h"


ItemSelector::ItemSelector(QWidget* parent)
{

groupSelector = new ComboBoxSelector(parent, "Группа",true);
varSelector = new ComboBoxSelector(parent, "Переменная",true);
descrSelector = new ComboBoxSelector(parent, "Описание",false);
buttons = new ControlButtons(parent,"");

model = new QSqlQueryModel(this);
group_model = new QSqlQueryModel(this);
mapper = new QDataWidgetMapper(this);

}

ItemSelector::~ItemSelector()
{
delete varSelector;
delete groupSelector;
delete descrSelector;
delete buttons;
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

return current_set;
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
connect(buttons,&ControlButtons::addClicked,this,&ItemSelector::addValue);
current_set = {};
addValue();

}

void ItemSelector::init()
{
toDebug("ItemSelector init (empty)",DT_CONTROLS);
disconnect(descrSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::descrSelectorChanged);
disconnect(groupSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::groupSelectorChanged);
disconnect(varSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::varSelectorChanged);
varSelector->init();
groupSelector->init();
descrSelector->init();
current_set = {};
}

void ItemSelector::reset()
{
varSelector->reset();
groupSelector->reset();
descrSelector->reset();
}

void ItemSelector::varSelectorChanged()
{
QString g,v;
g = groupSelector->currentText();
if (g.isEmpty()) g="Все";
v = varSelector->currentText();
mapper->setCurrentIndex(varSelector->currentIndex());
if (varSelector->currentIndex()<0)
  descrSelector->reset();
if (v.isEmpty())
  {
  v = "Все";
  if (current_set.isEmpty())
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_ADD_ALL);
  else
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE_ALL);
  }
else
  if (current_set.contains(v))
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE);
  else
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_ADD);
buttons->setLabelText(QString("Группа: %1; Переменная: %2").arg(g,v));
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

void ItemSelector::addValue()
{
if (!varSelector->currentText().isEmpty())
  if (current_set.contains(varSelector->currentText()))
    {
    current_set.remove(varSelector->currentText());
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_ADD);
    }
  else
    {
    current_set.insert(varSelector->currentText());
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE);
    }
else
  if (current_set.isEmpty())
    {
    for (int i=0;i<model->rowCount();++i)
      current_set.insert(model->data(model->index(i,0)).toString());
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE_ALL);
    }
  else
    {
    current_set = {};
    buttons->setButtonText(UI_GLOBALS::ALIAS_FOR_ADD_ALL);
    }
emit changed();

}

