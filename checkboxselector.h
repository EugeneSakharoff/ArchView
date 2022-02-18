#ifndef CHECKBOXSELECTOR_H
#define CHECKBOXSELECTOR_H

#include "controlelement.h"
#include <QCheckBox>

class CheckBoxSelector : public ControlElement
{
    Q_OBJECT
public:
    CheckBoxSelector(QWidget *parent, QString labeltext);
    ~CheckBoxSelector();
    bool isChecked();
    virtual bool init(QSqlQuery* query);
    virtual void init();
    virtual void reset();
    virtual void emitChanged();
private:
    QCheckBox *checkBox;
};

#endif // CHECKBOXSELECTOR_H
