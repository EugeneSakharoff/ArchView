#ifndef COMBOBOXSELECTOR_H
#define COMBOBOXSELECTOR_H

#include "controlelement.h"
#include "stringvalidator.h"
#include <QComboBox>
#include <QPushButton>
#include <QSet>



class ComboBoxSelector : public ControlElement
{
    Q_OBJECT
    Q_PROPERTY(QSet<QString> currentSet READ currentSet WRITE setCurrentSet)
    Q_PROPERTY(QSet<QString> fullSet READ fullSet WRITE setFullSet)
public:
    ComboBoxSelector(QWidget *parent, QString labeltext);
    ~ComboBoxSelector();
    QSet<QString> currentSet();
    QSet<QString> fullSet();
    void setCurrentSet(QSet<QString> set);
    void setFullSet(QSet<QString> set);
    virtual void init(QSqlQuery* query);
    virtual void init();
    virtual void reset();
    bool allSelected();

public slots:
    void comboBoxChanged();
    void add();
    void solo();

private:
    void resetItemColors();
    QComboBox *comboBox;
    QPushButton *addButton;
    QPushButton *soloButton;
    QSet<QString> current_set, full_set;
};

#endif // COMBOBOXSELECTOR_H
