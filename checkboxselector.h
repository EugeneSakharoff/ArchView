#ifndef CHECKBOXSELECTOR_H
#define CHECKBOXSELECTOR_H

#include "controlelement.h"
#include <QCheckBox>

//Класс наследуется от ControlElement, содержит в себе чекбокс
//Используется чтобы отображать/не отображать сообщения
class CheckBoxSelector : public ControlElement
{
    Q_OBJECT
public:
    CheckBoxSelector(QWidget *parent, const QString& labeltext);
    ~CheckBoxSelector();
    bool isChecked();
    bool init();
    void reset();
    void update();
    void clear();
private:
    QCheckBox *checkBox;
};

#endif // CHECKBOXSELECTOR_H
