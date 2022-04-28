
#include "optionswindow.h"
#include "crypto.h"
//Окно настроек

OptionsWindow::OptionsWindow(QWidget *parent) :QDialog(parent),ui(new Ui::OptionsWindow)
{
ui->setupUi(this);

connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&OptionsWindow::accepted);
connect(ui->checkBoxShowQuery,&QCheckBox::stateChanged,this,[=](){if(ui->checkBoxShowQuery->isChecked()){ui->checkBoxEditQuery->setEnabled(true);}
                                                                  else{ui->checkBoxEditQuery->setChecked(false);ui->checkBoxEditQuery->setEnabled(false);}});
using namespace GLOBALS;
//Выводим значения переменных, соответствующих настройкам, в соответствующие поля
ui->checkBoxConnectOnStart->setChecked(CONNECT_ON_STARTUP);
ui->checkBoxShowQuery->setChecked(SHOW_QUERY);
ui->checkBoxEditQuery->setChecked(EDIT_QUERY);
ui->checkBoxAllowAdvDB->setChecked(ALLOW_ADVANCED_DB_SETTINGS);
ui->checkBoxShowSliderSections->setChecked(SHOW_SLIDER_SECTIONS);

ui->editName->setText(DEFAULT_DB_NAME);
ui->editUser->setText(DEFAULT_DB_USERNAME);
ui->editPassword->setText(DEFAULT_DB_PASSWORD);
ui->editPort->setText(DEFAULT_DB_PORT);
ui->editServiceName->setText(SERVICE_DB_NAME);
ui->editServiceUser->setText(SERVICE_DB_USERNAME);
ui->editServicePassword->setText(SERVICE_DB_PASSWORD);
ui->editServicePort->setText(SERVICE_DB_PORT);

using namespace SQL_GLOBALS;
ui->editDescrTableName->setText(DESCRIPTIONS_TABLE);
ui->editValsTableName->setText(VALUES_TABLE);
ui->editMsgsTableName->setText(MESSAGES_TABLE);
ui->editGroupsTableName->setText(GROUPS_TABLE);
ui->editID->setText(ID_COLUMN);
ui->editVarName->setText(NAME_COLUMN);
ui->editVarDescr->setText(DESCRIPTION_COLUMN);
ui->editVarPrec->setText(PRECISION_COLUMN);
ui->editVarUnits->setText(UNITS_COLUMN);
ui->editGroupID->setText(GROUPID_COLUMN);
ui->editVarID->setText(VARID_COLUMN);
ui->editTime->setText(DATETIME_COLUMN);
ui->editMsgs->setText(MESSAGE_COLUMN);
ui->editValue->setText(VALUE_COLUMN);
}

OptionsWindow::~OptionsWindow()
{
delete ui;
}

void OptionsWindow::accepted()
{
QSettings settings(CONFIG_FILE,QSettings::IniFormat);

using namespace GLOBALS;
//пишем выбранные пользователем настройки в файл настроек
settings.setValue("db/DEFAULT_DB_NAME",ui->editName->text());
settings.setValue("db/DEFAULT_DB_USERNAME",ui->editUser->text());

if (GLOBALS::ENCRYPT_PASSWORD)
{
    Crypto crypto(GLOBALS::KEY);
    settings.setValue("db/DEFAULT_DB_PASSWORD",crypto.encryptToString(ui->editPassword->text()));
    settings.setValue("db/SERVICE_DB_PASSWORD",crypto.encryptToString(ui->editServicePassword->text()));
    toDebug("Passwords enecrypted",DT_DATABASE);
}
else
{
    settings.setValue("db/DEFAULT_DB_PASSWORD",ui->editPassword->text());
    settings.setValue("db/SERVICE_DB_PASSWORD",ui->editServicePassword->text());
}
settings.setValue("db/SERVICE_DB_NAME",ui->editServiceName->text());
settings.setValue("db/SERVICE_DB_USERNAME",ui->editServiceUser->text());
settings.setValue("db/DEFAULT_DB_PORT",ui->editPort->text());
settings.setValue("db/SERVICE_DB_PORT",ui->editServicePort->text());


settings.setValue("globals/CONNECT_ON_STARTUP",ui->checkBoxConnectOnStart->isChecked());
settings.setValue("globals/SHOW_QUERY",ui->checkBoxShowQuery->isChecked());
settings.setValue("globals/EDIT_QUERY",ui->checkBoxEditQuery->isChecked());
settings.setValue("globals/ALLOW_ADVANCED_DB_SETTINGS",ui->checkBoxAllowAdvDB->isChecked());
settings.setValue("globals/SHOW_SLIDER_SECTIONS",ui->checkBoxShowSliderSections->isChecked());

settings.setValue("sql/VALUES_TABLE",ui->editValsTableName->text());
settings.setValue("sql/DESCRIPTIONS_TABLE",ui->editDescrTableName->text());
settings.setValue("sql/MESSAGES_TABLE",ui->editMsgsTableName->text());
settings.setValue("sql/GROUPS_TABLE",ui->editGroupsTableName->text());
settings.setValue("sql/ID_COLUMN",ui->editID->text());
settings.setValue("sql/VARID_COLUMN",ui->editVarID->text());
settings.setValue("sql/NAME_COLUMN",ui->editVarName->text());
settings.setValue("sql/DESCRIPTION_COLUMN",ui->editVarDescr->text());
settings.setValue("sql/GROUPID_COLUMN",ui->editGroupID->text());
settings.setValue("sql/DATETIME_COLUMN",ui->editTime->text());
settings.setValue("sql/PRECISION_COLUMN",ui->editVarPrec->text());
settings.setValue("sql/VALUE_COLUMN",ui->editValue->text());
settings.setValue("sql/MESSAGE_COLUMN",ui->editMsgs->text());

settings.sync();
//заново считываем файл, чтобы настройки применились
readSettings();
}

