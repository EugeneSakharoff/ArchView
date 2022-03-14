#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "ui_optionswindow.h"
#include <QDialog>
#include <QDebug>
#include "globals.h"
#include "sql_globals.h"
#include "ui.h"


namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();
    void accepted();

private:
    Ui::OptionsWindow *ui;

};

#endif // OPTIONSWINDOW_H

