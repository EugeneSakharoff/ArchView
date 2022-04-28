#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H

#include "controlelement.h"
#include <QObject>
#include <QPushButton>
//Кнопки "Добавить" и "Добавить соло"
class ControlButtons : public ControlElement
{
    Q_OBJECT
public:
    ControlButtons(QWidget *parent, const QString& labeltext);
    ~ControlButtons();
    bool init();
    void reset();
    void clear();
    void setLabelText(const QString &text);
    void setAddButtonText(const QString &text);
    void setSoloButtonText(const QString &text);
    void setEnabled(const bool enabled);
    virtual void update();
signals:
    void addClicked();
    void soloClicked();
private:
    QPushButton *addButton;
    QPushButton *soloButton;
};

#endif // CONTROLBUTTONS_H
