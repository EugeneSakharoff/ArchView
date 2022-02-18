#include "controlelement.h"


ControlElement::ControlElement(QWidget *parent, QString labeltext)
{
groupBox = new QGroupBox(parent);
groupBox->setFlat(true);
groupBox->setStyleSheet("QGroupBox { border: 0px solid gray;}");
layout = new QHBoxLayout(groupBox);
label = new QLabel(labeltext,groupBox);
label->setMaximumSize(UI_GLOBALS::LABEL_WIDTH, UI_GLOBALS::ELEMENT_HEIGHT);
label->setMinimumSize(UI_GLOBALS::LABEL_WIDTH, UI_GLOBALS::ELEMENT_HEIGHT);
layout->setSpacing(0);
layout->addWidget(label);
parent->layout()->addWidget(groupBox);
}


ControlElement::~ControlElement()
{
delete label;
delete layout;
delete groupBox;
}
