#include "controlbuttons.h"

//Кнопки "Добавить" и "Добавить соло"

ControlButtons::ControlButtons(QWidget *parent,const QString& labeltext):ControlElement(parent,labeltext)
{
addButton = new QPushButton(groupBox);
soloButton = new QPushButton(groupBox);
addButton->setMinimumSize(UI_GLOBALS::BIG_BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
addButton->setMaximumSize(UI_GLOBALS::BIG_BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
soloButton->setMinimumSize(UI_GLOBALS::BIG_BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
soloButton->setMaximumSize(UI_GLOBALS::BIG_BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
label->setMaximumSize(UI_GLOBALS::LABEL_WIDTH*4, UI_GLOBALS::ELEMENT_HEIGHT);
label->setMinimumSize(UI_GLOBALS::LABEL_WIDTH*4, UI_GLOBALS::ELEMENT_HEIGHT);
layout->addWidget(addButton);
layout->addWidget(soloButton);
layout->setAlignment(label,Qt::AlignLeft);

layout->setSpacing(1);
layout->update();
connect(addButton,&QPushButton::clicked,this,[=](){emit addClicked();});
connect(soloButton,&QPushButton::clicked,this,[=](){emit soloClicked();});
}

ControlButtons::~ControlButtons()
{
delete addButton;
delete soloButton;
}

bool ControlButtons::init()
{
setEnabled(true);
return 0;
}

void ControlButtons::clear()
{
setEnabled(false);
}

void ControlButtons::reset()
{

}


void ControlButtons::update()
{

}


void ControlButtons::setLabelText(const QString &text)
{
label->setText(text);
}

void ControlButtons::setAddButtonText(const QString &text)
{
addButton->setText(text);
}

void ControlButtons::setSoloButtonText(const QString &text)
{
soloButton->setText(text);
}

void ControlButtons::setEnabled(const bool enabled)
{
addButton->setEnabled(enabled);
soloButton->setEnabled(enabled);
}
