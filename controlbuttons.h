#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H

#include "controlelement.h"
#include <QObject>
#include <QPushButton>

class ControlButtons : public ControlElement
{
    Q_OBJECT
public:
    ControlButtons(QWidget *parent, const QString& labeltext);
    ~ControlButtons();
    virtual void init();
    virtual void reset();
    virtual void emitChanged();
    void setLabelText(const QString &text);
    void setAddButtonText(const QString &text);
    void setSoloButtonText(const QString &text);
    void setEnabled(const bool enabled);
signals:
    void addClicked();
    void soloClicked();
private:
    QPushButton *addButton;
    QPushButton *soloButton;
};

#endif // CONTROLBUTTONS_H
