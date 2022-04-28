#ifndef COMBOBOXSELECTOR_H
#define COMBOBOXSELECTOR_H

#include "controlelement.h"
#include "stringvalidator.h"
#include <QComboBox>
#include <QPushButton>
#include <QSet>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>

//Класс наследуется от ControlElement, содержит в себе комбобокс и кнопку reset
//Входит в состав ItemSelector
class ComboBoxSelector : public ControlElement
{
    Q_OBJECT
public:
    ComboBoxSelector(QWidget *parent, const QString& labeltext,bool withButtons);
    ~ComboBoxSelector();
    bool init(QSqlQueryModel* model, const int model_col=0, QDataWidgetMapper* mapper=nullptr, const int mapper_sec=0, const QByteArray &propertyName="");
    bool init();
    void clear();
    void reset();
    int currentIndex();
    QString currentText();
    QSet<QString> currentSet();
    virtual void update();

signals:
    void resetClicked();
    void indexChanged();


private:
    QComboBox *comboBox;
    QPushButton *resetButton;
};

#endif // COMBOBOXSELECTOR_H
