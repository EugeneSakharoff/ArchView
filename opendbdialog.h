#ifndef OPENDBDIALOG_H
#define OPENDBDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "globals.h"
#include "sql_globals.h"
#include "ui_opendbdialog.h"
#include "ui.h"
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
    explicit OpenDBDialog(const DBConnectParams *current_params, QWidget *parent = nullptr);
    ~OpenDBDialog();
    CONNECTION_PARAMS* getDBParams();
private slots:
    void editPresetChanged();
    bool check();
    void resizeAdvancedGroupBox();
    void tryAccept();

private:
    Ui::OpenDBDialog *ui;

};

#endif // OPENDBDIALOG_H
