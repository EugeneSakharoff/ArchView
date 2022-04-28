#include "checkboxselector.h"
//Класс наследуется от ControlElement, содержит в себе чекбокс
//Используется чтобы отображать/не отображать сообщения

CheckBoxSelector::CheckBoxSelector(QWidget *parent,const QString& labeltext):ControlElement(parent,labeltext)
{
checkBox = new QCheckBox(groupBox);
layout->addWidget(checkBox);
}

CheckBoxSelector::~CheckBoxSelector()
{
delete checkBox;
}

//возвращает True если чекбокс отмечен. Нужно для инкапсуляции
bool CheckBoxSelector::isChecked()
{
if (checkBox->isChecked()) return true;
else return false;
}

//инициализация
bool CheckBoxSelector::init()
{
toDebug(label->text()+" Checkbox init",DT_TRACE);
checkBox->setChecked(GLOBALS::MESSAGES_ON_BY_DEFAULT);
checkBox->setEnabled(true);
checkBox->update();
connect(checkBox,&QCheckBox::clicked,this,[=](){emit changed();});
return true;
}

//Пустая инициализация (без sql запроса).
void CheckBoxSelector::clear()
{
toDebug(label->text()+" Checkbox init(empty)",DT_CONTROLS);
checkBox->setChecked(false);
checkBox->setEnabled(false);
checkBox->update();
}

//сброс установок. В данном случае просто устанавливает значение в MESSAGES_ON_BY_DEFAULT
void CheckBoxSelector::reset()
{
toDebug(label->text()+" checkbox reset",DT_CONTROLS);
checkBox->setChecked(GLOBALS::MESSAGES_ON_BY_DEFAULT);
checkBox->update();
}

void CheckBoxSelector::update()
{

}


