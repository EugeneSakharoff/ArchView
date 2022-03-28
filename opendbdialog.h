#ifndef OPENDBDIALOG_H
#define OPENDBDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "globals.h"
#include "sql_globals.h"
#include "ui_opendbdialog.h"
#include "database.h"

namespace Ui {
class OpenDBDialog;
}

/////////////////////////////////////////////////////////////////////////////
// class OpenDBDialog
/////////////////////////////////////////////////////////////////////////////

class OpenDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDBDialog(const DBConnectParams &params, QWidget *parent = nullptr);
    ~OpenDBDialog();
    DBConnectParams* getDBParams();
private slots:
    void editHostChanged();
    void checkOptions();

private:
    Ui::OpenDBDialog *ui;

};

#endif // OPENDBDIALOG_H
