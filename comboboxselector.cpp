#include "comboboxselector.h"


//Класс наследуется от ControlElement, содержит в себе комбобокс и кнопку reset
//Входит в состав ItemSelector
ComboBoxSelector::ComboBoxSelector(QWidget *parent, const QString& labeltext, bool withButtons):ControlElement(parent,labeltext)
{
comboBox = new QComboBox(groupBox);
resetButton = new QPushButton(groupBox);
layout->addWidget(comboBox);
if (withButtons)
  {
  resetButton->setMaximumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
  resetButton->setMinimumSize(UI_GLOBALS::BUTTON_WIDTH,UI_GLOBALS::ELEMENT_HEIGHT);
  resetButton->setText(UI_GLOBALS::ALIAS_FOR_RESET);

  connect(resetButton,&QPushButton::clicked,this,&ComboBoxSelector::reset);
  }
else
  {
  resetButton->setMaximumSize(0,0);
  resetButton->setMinimumSize(0,0);
  resetButton->setVisible(false);
  }
layout->addWidget(resetButton);
}

ComboBoxSelector::~ComboBoxSelector()
{
delete resetButton;
delete comboBox;
}

//возвращает текущий индекс комбобокса
int ComboBoxSelector::currentIndex()
{
return comboBox->currentIndex();
}

//возвращает текущий текст комбобокса
QString ComboBoxSelector::currentText()
{
return comboBox->currentText();
}

//инициализация без запроса
void ComboBoxSelector::clear()
{
toDebug(label->text()+" combobox init (empty)",DT_CONTROLS);
comboBox->clear();
comboBox->setEnabled(false);
comboBox->setEditable(false);
resetButton->setEnabled(false);
}

bool ComboBoxSelector::init()
{
clear();
return 0;
}

//инициализация через QSqlQueryModel и QDataWidgetMapper
//model_col - столбец модели, в котором содержатся множество значений для комбобокса
//mapper_sec и propertyName нужны для взаимодействия нескольких ComboBoxSelector-ов внутри ItemSelector-а
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
  resetButton->setEnabled(true);
  connect(comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,[=](){emit indexChanged();});
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

void ComboBoxSelector::reset()
{
toDebug(label->text()+" combobox reset",DT_CONTROLS);
comboBox->setCurrentIndex(-1);
}

void ComboBoxSelector::update()
{

}


