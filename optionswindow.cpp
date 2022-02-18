#include "optionswindow.h"


OptionsWindow::OptionsWindow(QWidget *parent) :QDialog(parent),ui(new Ui::OptionsWindow)
{
ui->setupUi(this);
//ui->editName->setText(DEFAULT_DB.name);
//ui->editUser->setText(DEFAULT_DB.user);
//ui->editPassword->setText(DEFAULT_DB.password);
//ui->editPort->setText(QString::number(DEFAULT_DB.port));
//ui->editServiceName->setText(SERVICE_DB.name);
//ui->editServiceUser->setText(SERVICE_DB.user);
//ui->editServicePassword->setText(SERVICE_DB.password);
}

OptionsWindow::~OptionsWindow()
{
delete ui;
}

