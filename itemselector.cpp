#include "itemselector.h"

//класс содержит в себе три  ComboboxSelector-а и ControlButtons
ItemSelector::ItemSelector(QWidget* parent)
{
groupSelector = new ComboBoxSelector(parent, "Группа",true);
varSelector = new ComboBoxSelector(parent, "Переменная",true);
descrSelector = new ComboBoxSelector(parent, "Описание",false);
buttons = new ControlButtons(parent,"");

model = new QSqlQueryModel(this);
group_model = new QSqlQueryModel(this);
mapper = new QDataWidgetMapper(this);
namedescr_query = nullptr;
group_query = nullptr;
connect(buttons,&ControlButtons::addClicked,this,&ItemSelector::addValue);
connect(buttons,&ControlButtons::soloClicked,this,&ItemSelector::soloValue);
}

ItemSelector::~ItemSelector()
{
delete varSelector;
delete groupSelector;
delete descrSelector;
delete buttons;
delete model;
delete mapper;
if (namedescr_query!=nullptr)
  delete namedescr_query;
if (group_query!=nullptr)
  delete group_query;
}

//набор текущих выбранных переменных
QSet<QString> ItemSelector::varSet()
{
return current_set;
}

//все доступные переменные
QSet<QString> ItemSelector::fullSet()
{
QSet<QString> res;
for (int i=0;i<model->rowCount();++i)
  res.insert(model->data(model->index(i,0)).toString());
return res;
}


//инициализация двумя SQL запросами, один для получения списка имен и описаний, второй для групп
bool ItemSelector::init(QSqlDatabase *db)
{
toDebug("ItemSelector init (query)",DT_CONTROLS);

using namespace SQL_GLOBALS;
namedescr_query = new QSqlQuery(*db);
group_query = new QSqlQuery(*db);
namedescr_query->prepare(SqlSelectQuery::buildSelectQuery({NAME_COLUMN,GROUPID_COLUMN,DESCRIPTION_COLUMN},DESCRIPTIONS_TABLE,{},{},false,NAME_COLUMN));
group_query->prepare(SqlSelectQuery::buildSelectQuery({NAME_COLUMN},GROUPS_TABLE,{},{},true,NAME_COLUMN));

update();
current_set = {};
addValue();
buttons->setSoloButtonText(UI_GLOBALS::ALIAS_FOR_SOLO);
return 0;
}

void ItemSelector::clear()
{
toDebug("ItemSelector clear",DT_CONTROLS);
disconnect(descrSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::descrSelectorChanged);
disconnect(groupSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::groupSelectorChanged);
disconnect(varSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::varSelectorChanged);

if (namedescr_query!=nullptr)
    delete namedescr_query;
if (group_query!=nullptr)
    delete group_query;

varSelector->clear();
groupSelector->clear();
descrSelector->clear();
current_set = {};
buttons->setAddButtonText(UI_GLOBALS::PLACEHOLDER);
buttons->setSoloButtonText(UI_GLOBALS::PLACEHOLDER);
}

void ItemSelector::reset()
{
varSelector->reset();
groupSelector->reset();
descrSelector->reset();
}

//вызывается при изменении селектора переменной
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
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_ADD_ALL);
  else
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE_ALL);
  }
else
  if (current_set.contains(v))
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE);
  else
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_ADD);
//buttons->setLabelText(QString("Группа: %1; Переменная: %2").arg(g,v));
emit changed();
}

//вызывается при изменении селектора описания переменной
void ItemSelector::descrSelectorChanged()
{
mapper->setCurrentIndex(descrSelector->currentIndex());
if (descrSelector->currentIndex()<0)
  varSelector->reset();
emit changed();
}

//вызывается при изменении селектора группы
void ItemSelector::groupSelectorChanged()
{
using namespace SQL_GLOBALS;
if (groupSelector->currentIndex()<0)
  namedescr_query->prepare(SqlSelectQuery::buildSelectQuery({NAME_COLUMN,GROUPID_COLUMN,DESCRIPTION_COLUMN},DESCRIPTIONS_TABLE,{},
                                                    {},
                                                    false,NAME_COLUMN));
else
  namedescr_query->prepare(SqlSelectQuery::buildSelectQuery({NAME_COLUMN,GROUPID_COLUMN,DESCRIPTION_COLUMN},DESCRIPTIONS_TABLE,{},
                                                    {SqlFilter(GROUPID,QStringList(QString::number(groupSelector->currentIndex())))},
                                                    false,NAME_COLUMN));

descrSelector->reset();
varSelector->reset();
}

//вызывается при инажатии на кнопку "Добавить"
void ItemSelector::addValue()
{
if (!varSelector->currentText().isEmpty())
  if (current_set.contains(varSelector->currentText()))
    {
    current_set.remove(varSelector->currentText());
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_ADD);
    }
  else
    {
    current_set.insert(varSelector->currentText());
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE);
    }
else
  if (current_set.isEmpty())
    {
    for (int i=0;i<model->rowCount();++i)
      current_set.insert(model->data(model->index(i,0)).toString());
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE_ALL);
    }
  else
    {
    current_set = {};
    buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_ADD_ALL);
    }
emit changed();
}


//вызывается при инажатии на кнопку "Добавить соло"
void ItemSelector::soloValue()
{
if (!varSelector->currentText().isEmpty())
  {
  current_set.clear();
  current_set.insert(varSelector->currentText());
  buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE);
  }
else
  {
  for (int i=0;i<model->rowCount();++i)
    current_set.insert(model->data(model->index(i,0)).toString());
  buttons->setAddButtonText(UI_GLOBALS::ALIAS_FOR_REMOVE_ALL);
  }
emit changed();
}

void ItemSelector::update()
{
disconnect(descrSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::descrSelectorChanged);
disconnect(groupSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::groupSelectorChanged);
disconnect(varSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::varSelectorChanged);
namedescr_query->exec();
group_query->exec();
model->setQuery(*namedescr_query);
group_model->setQuery(*group_query);
mapper->setModel(model); //маппер связывает имена и описания переменных
varSelector->init(model,0,mapper,0);
groupSelector->init(group_model,0);
descrSelector->init(model,2,mapper,2);
connect(descrSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::descrSelectorChanged);
connect(groupSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::groupSelectorChanged);
connect(varSelector,&ComboBoxSelector::indexChanged,this,&ItemSelector::varSelectorChanged);

}
