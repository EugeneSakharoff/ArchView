#include "comboboxselector.h"

ComboBoxSelector::ComboBoxSelector(QWidget *parent, QString labeltext):ControlElement(parent,labeltext)
{
comboBox = new QComboBox(groupBox);
addButton = new QPushButton(groupBox);
soloButton = new QPushButton(groupBox);

addButton->setMaximumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
addButton->setMinimumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
soloButton->setMaximumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
soloButton->setMinimumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
layout->addWidget(comboBox);
layout->addWidget(addButton);
layout->addWidget(soloButton);
connect(comboBox,&QComboBox::currentTextChanged,this,&ComboBoxSelector::comboBoxChanged);
connect(addButton,&QPushButton::clicked,this,&ComboBoxSelector::add);
connect(soloButton,&QPushButton::clicked,this,&ComboBoxSelector::solo);
}

ComboBoxSelector::~ComboBoxSelector()
{
delete soloButton;
delete addButton;
delete comboBox;
}

QSet<QString> ComboBoxSelector::currentSet()
{
return current_set;
}

QSet<QString> ComboBoxSelector::fullSet()
{
return full_set;
}

void  ComboBoxSelector::setCurrentSet(QSet<QString> set)
{
current_set = set;
}

void  ComboBoxSelector::setFullSet(QSet<QString> set)
{
full_set = set;
}

void ComboBoxSelector::init(QSqlQuery* query)
{
full_set.clear();
current_set.clear();
comboBox->clear();
if (query == nullptr)
  {
  if (DEBUG_CONTROLS) qDebug()<<label->text()<<"Combobox init, query is null";
  init_query = query;
  comboBox->setEnabled(false);
  addButton->setText("");
  addButton->setEnabled(false);
  soloButton->setText("");
  soloButton->setEnabled(false);
  return;
  }
if (DEBUG_CONTROLS) qDebug()<<label->text()<<" combobox init, query="<<query->lastQuery();

comboBox->addItem(UI_GLOBALS::ALIAS_FOR_ALL);
while (query->next())
  {
  comboBox->addItem(query->value(0).toString());
  full_set.insert(query->value(0).toString());
  }

stringValidator* validator = new stringValidator(full_set, comboBox);
comboBox->setEditable(true);
comboBox->setEnabled(true);
comboBox->setValidator(validator);
current_set = full_set;
comboBox->setCurrentIndex(0);
addButton->setText("");
addButton->setEnabled(false);
soloButton->setText(UI_GLOBALS::ALIAS_FOR_MUTE);
soloButton->setEnabled(true);
resetItemColors();
if (DEBUG_CONTROLS) qDebug()<<label->text()<<" initialized with "<<full_set;
}

void ComboBoxSelector::resetItemColors()
{
for (int i = 1; i < full_set.count()+1;i++){
  if (current_set.contains(comboBox->itemData(i,Qt::DisplayRole).toString()))
    {
    comboBox->setItemData(i, UI_GLOBALS::COMBOBOX_SELECTED_BACKGROUND, Qt::BackgroundRole);
    comboBox->setItemData(i, UI_GLOBALS::COMBOBOX_SELECTED_FOREGROUND, Qt::ForegroundRole);
    }
  else
    {
    comboBox->setItemData(i, UI_GLOBALS::COMBOBOX_NONSELECTED_BACKGROUND, Qt::BackgroundRole);
    comboBox->setItemData(i, UI_GLOBALS::COMBOBOX_NONSELECTED_FOREGROUND, Qt::ForegroundRole);
    }
  }
}

bool ComboBoxSelector::allSelected()
{
if (current_set.count()==full_set.count()) return true;
else return false;
}

void ComboBoxSelector::comboBoxChanged()
{
if (DEBUG_CONTROLS) qDebug()<<label->text()<<" index changed "<<current_set;
if (comboBox->currentText() == UI_GLOBALS::ALIAS_FOR_ALL)
  {
  addButton->setEnabled(false);
  addButton->setText("");
  if (full_set.count()==0)
    {
    soloButton->setText("");
    soloButton->setEnabled(false);
    }
  else
    {
    if (allSelected()) soloButton->setText(UI_GLOBALS::ALIAS_FOR_MUTE);
    else soloButton->setText(UI_GLOBALS::ALIAS_FOR_SOLO);
    soloButton->setEnabled(true);
    }
  }
else
  {
  addButton->setEnabled(true);
  soloButton->setEnabled(true);
  if (current_set.contains(comboBox->currentText())) addButton->setText(UI_GLOBALS::ALIAS_FOR_REMOVE);
  else addButton->setText(UI_GLOBALS::ALIAS_FOR_ADD);
  soloButton->setText(UI_GLOBALS::ALIAS_FOR_SOLO);
  }
}

void ComboBoxSelector::add()
{
if (comboBox->currentText() == UI_GLOBALS::ALIAS_FOR_ALL)
  {
  //все переменные
  current_set = full_set;
  addButton->setText("");
  addButton->setEnabled(false);
  }
else
  if (current_set.contains(comboBox->currentText()))
    {
    //удалить переменную
    current_set.remove(comboBox->currentText());
    addButton->setText(UI_GLOBALS::ALIAS_FOR_ADD);
    }
  else
    {
    //добавить переменную
    current_set.insert(comboBox->currentText());
    addButton->setText(UI_GLOBALS::ALIAS_FOR_REMOVE);
    }
resetItemColors();
emit changed();
}

void ComboBoxSelector::solo()
{
if (comboBox->currentText() == UI_GLOBALS::ALIAS_FOR_ALL)
  {
  if (!allSelected())
    {
    current_set = full_set;
    soloButton->setText(UI_GLOBALS::ALIAS_FOR_MUTE);
    }
  else
    {
    current_set.clear();
    soloButton->setText(UI_GLOBALS::ALIAS_FOR_SOLO);
    }
  }
else
  {
  if (current_set.count()==1 && current_set.contains(comboBox->currentText()))
    {
    current_set.remove(comboBox->currentText());
    soloButton->setText(UI_GLOBALS::ALIAS_FOR_SOLO);
    addButton->setText(UI_GLOBALS::ALIAS_FOR_ADD);
    }
  else
    {
    current_set.clear();
    current_set.insert(comboBox->currentText());
    soloButton->setText(UI_GLOBALS::ALIAS_FOR_MUTE);
    addButton->setText(UI_GLOBALS::ALIAS_FOR_REMOVE);
    }
  }
resetItemColors();
emit changed();
}

void ComboBoxSelector::init()
{
if (DEBUG_CONTROLS) qDebug()<<label->text()<<"combobox init (empty)";
current_set.clear();
full_set.clear();
comboBox->clear();
comboBox->setEnabled(false);
addButton->setText("");
addButton->setEnabled(false);
soloButton->setText("");
soloButton->setEnabled(false);
}

void ComboBoxSelector::reset()
{
if (DEBUG_CONTROLS) qDebug()<<label->text()<<" combobox reset";
current_set=full_set;
comboBox->setCurrentIndex(0);
emit changed();
}
