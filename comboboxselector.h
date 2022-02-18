#ifndef COMBOBOXSELECTOR_H
#define COMBOBOXSELECTOR_H

#include "controlelement.h"
#include "stringvalidator.h"
#include <QComboBox>
#include <QPushButton>
#include <QSet>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>



class ComboBoxSelector : public ControlElement
{
    Q_OBJECT
public:
    ComboBoxSelector(QWidget *parent, QString labeltext,bool withButtons);
    ~ComboBoxSelector();
    virtual bool init(QSqlQuery* query);
    bool init(QSqlQueryModel* model, const int model_col=0, QDataWidgetMapper* mapper=nullptr, const int mapper_sec=0, const QByteArray &propertyName="");
    virtual void init();
    virtual void reset();
    virtual void emitChanged();
    int currentIndex();
    QString currentText();
    QSet<QString> currentSet();

signals:
    void addClicked();
    void soloClicked();
    void resetClicked();
    void indexChanged();


private:
    QComboBox *comboBox;
    QPushButton *resetButton;
    QSet<QString> current_set;
};

#endif // COMBOBOXSELECTOR_H
