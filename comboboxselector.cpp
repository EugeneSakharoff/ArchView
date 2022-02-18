#include "comboboxselector.h"

ComboBoxSelector::ComboBoxSelector(QWidget *parent, QString labeltext, bool withButtons):ControlElement(parent,labeltext)
{
comboBox = new QComboBox(groupBox);
//addButton = new QPushButton(groupBox);
//soloButton = new QPushButton(groupBox);
resetButton = new QPushButton(groupBox);
layout->addWidget(comboBox);
current_set = {};
if (withButtons)
  {
  //addButton->setMaximumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
  //addButton->setMinimumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);

  //soloButton->setMaximumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
  //soloButton->setMinimumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);

  resetButton->setMaximumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
  resetButton->setMinimumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);

  resetButton->setText(UI_GLOBALS::ALIAS_FOR_RESET);

  //connect(addButton,&QPushButton::clicked,this,[=](){emit addClicked();});
  //connect(soloButton,&QPushButton::clicked,this,[=](){emit soloClicked();});
  connect(resetButton,&QPushButton::clicked,this,&ComboBoxSelector::reset);
  }
else
  {
  //addButton->setMaximumSize(0,0);
  //addButton->setMinimumSize(0,0);
  //addButton->setVisible(false);

  //soloButton->setMaximumSize(0,0);
  //soloButton->setMinimumSize(0,0);
  //soloButton->setVisible(false);

  resetButton->setMaximumSize(0,0);
  resetButton->setMinimumSize(0,0);
  resetButton->setVisible(false);
  }
//layout->addWidget(addButton);
//layout->addWidget(soloButton);
layout->addWidget(resetButton);
}

ComboBoxSelector::~ComboBoxSelector()
{
delete resetButton;
//delete addButton;
//delete soloButton;
delete comboBox;
}

int ComboBoxSelector::currentIndex()
{
return comboBox->currentIndex();
}

void ComboBoxSelector::init()
{
toDebug(label->text()+" combobox init (empty)",DT_CONTROLS);
comboBox->clear();
comboBox->setEnabled(false);
comboBox->setEditable(false);
//addButton->setEnabled(false);
//soloButton->setEnabled(false);
resetButton->setEnabled(false);
//current_set = {};
//addButton->setText(UI_GLOBALS::PLACEHOLDER);
//soloButton->setText(UI_GLOBALS::PLACEHOLDER);

}

bool ComboBoxSelector::init(QSqlQuery* query)
{
init();
return true;
}

bool ComboBoxSelector::init(QSqlQueryModel* model, const int model_col, QDataWidgetMapper* mapper, const int mapper_sec, const QByteArray &propertyName)
{
toDebug(label->text()+" combobox init ",DT_CONTROLS);
try
  {
  if(!(mapper==nullptr))
    {
    if (propertyName=="")
      mapper->addMapping(comboBox,mapper_sec);
    else
      mapper->addMapping(comboBox,mapper_sec,propertyName);
    }
  comboBox->setModel(model);
  comboBox->setModelColumn(model_col);
  comboBox->setEnabled(true);
  comboBox->setEditable(true);
  //addButton->setEnabled(true);

  //soloButton->setEnabled(true);

  resetButton->setEnabled(true);
  connect(comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[=](){emit indexChanged();});
  //current_set = {};
  reset();

  toDebug(label->text()+" combobox initialization OK",DT_CONTROLS);
  return true;
  }
catch (...)
  {
  toDebug(label->text()+" combobox initialization FAILED!",DT_ERROR);
  init();
  return false;
  }

}


void ComboBoxSelector::emitChanged()
{

}

void ComboBoxSelector::reset()
{
toDebug(label->text()+" combobox reset",DT_CONTROLS);
comboBox->setCurrentIndex(-1);
//for (int i=0;i<comboBox->count();++i)
//  current_set.insert(comboBox->itemText(i));
//addButton->setText(UI_GLOBALS::ALIAS_FOR_REMOVE);
//soloButton->setText(UI_GLOBALS::ALIAS_FOR_SOLO);
}

QString ComboBoxSelector::currentText()
{
return comboBox->currentText();
}

QSet<QString> ComboBoxSelector::currentSet()
{
return current_set;
}
