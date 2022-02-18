#include "checkboxselector.h"

CheckBoxSelector::CheckBoxSelector(QWidget *parent, QString labeltext):ControlElement(parent,labeltext)
{
checkBox = new QCheckBox(groupBox);
layout->addWidget(checkBox);
}

CheckBoxSelector::~CheckBoxSelector()
{
delete checkBox;
delete init_query;
}

bool CheckBoxSelector::isChecked()
{
if (checkBox->isChecked()) return true;
else return false;
}


bool CheckBoxSelector::init(QSqlQuery* query)
{
toDebug(label->text()+" Checkbox init",DT_TRACE);
init_query = query;
if (query==nullptr)
  {
  toDebug(label->text()+" CheckboxQuery is NULL",DT_ERROR);
  init();
  return false;
  }
if (!query->first())
  {
  toDebug(label->text()+" CheckboxQuery is empty",DT_ERROR);
  init();
  return false;
  }
checkBox->setChecked(GLOBALS::MESSAGES_ON_BY_DEFAULT);
checkBox->setEnabled(true);
checkBox->update();
connect(checkBox,&QCheckBox::clicked,this,&CheckBoxSelector::emitChanged);
toDebug(label->text()+" CheckboxQuery is OK",DT_CONTROLS);
return true;
}

void CheckBoxSelector::init()
{
toDebug(label->text()+" Checkbox init(empty)",DT_TRACE);
checkBox->setChecked(false);
checkBox->setEnabled(false);
checkBox->update();
disconnect(checkBox,&QCheckBox::clicked,this,&CheckBoxSelector::emitChanged);
}


void CheckBoxSelector::reset()
{
toDebug(label->text()+" checkbox reset",DT_TRACE);
checkBox->setChecked(GLOBALS::MESSAGES_ON_BY_DEFAULT);
checkBox->update();
}

void CheckBoxSelector::emitChanged()
{
toDebug(label->text()+" Checkbox changed",DT_CONTROLS);
emit changed();
}
