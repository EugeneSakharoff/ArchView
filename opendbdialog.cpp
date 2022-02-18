#include "opendbdialog.h"


OpenDBDialog::OpenDBDialog(const DBConnectOptions &options,QWidget *parent) : QDialog(parent), ui(new Ui::OpenDBDialog)
{
ui->setupUi(this);
connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&OpenDBDialog::checkOptions);
disconnect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

QRegExp rx(QString("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$"));
QValidator *IPValidator = new QRegExpValidator(rx, this);
ui->editIP->setValidator(IPValidator);

QIntValidator *portValidator = new QIntValidator(this);
ui->editPort->setValidator(portValidator);

readHostsList();
//составляем список хостов из HOSTS_MAP
QMap<QString, QString>::iterator it;
for (it = GLOBALS::HOSTS_MAP.begin(); it != GLOBALS::HOSTS_MAP.end(); ++it)
  ui->editHost->addItem(it.key());

//выставляем индекс на текущий хост
int index = ui->editHost->findText(options.getHostName());
if (index >= 0)
  {
  ui->editHost->setCurrentIndex(index);
  if (options.getHostAddr()!=GLOBALS::HOSTS_MAP[options.getHostName()])
    toDebug("Current host addres does not match: "+options.getHostName()+options.getHostAddr(),DT_WARNING);
  }
else
  {
  toDebug("Current host name not on the list: "+options.getHostName(),DT_WARNING);
  ui->editHost->addItem(options.getHostName());
  ui->editHost->setCurrentIndex(ui->editHost->count()-1);
  }
ui->editIP->setText(options.getHostAddr());

connect(ui->editHost,&QComboBox::currentTextChanged,this,&OpenDBDialog::editHostChanged);

ui->editName->setText(options.getDBName());
ui->editUser->setText(options.getUserName());
ui->editPassword->setText(options.getPassword());
ui->editPort->setText(options.getPort());

//составляем список драйверов и ищем в нем текущий
ui->editDriver->addItems(GLOBALS::AVAILABLE_DRIVERS);
index = ui->editDriver->findText(options.getDriver());
if (index >= 0)
  ui->editDriver->setCurrentIndex(index);
else
  {
  toDebug("Current driver not on the list: "+options.getDriver(),DT_ERROR);
  ui->editDriver->addItem(options.getDriver());
  ui->editDriver->setCurrentIndex(ui->editDriver->count()-1);
  }
}


void OpenDBDialog::editHostChanged()
{
ui->editIP->setText(GLOBALS::HOSTS_MAP[ui->editHost->currentText()]);
}

OpenDBDialog::~OpenDBDialog()
{
delete ui;
}

DBConnectOptions* OpenDBDialog::getDBParams()
{
if (this->exec()==1)
  {
  DBConnectOptions *options = new DBConnectOptions(ui->editName->text(),
                                                   ui->editHost->currentText(),
                                                   ui->editIP->text(),
                                                   ui->editUser->text(),
                                                   ui->editPassword->text(),
                                                   ui->editPort->text(),
                                                   ui->editDriver->currentText());
  toDebug("Setting DB params: "+options->getHostName()+options->getHostAddr(),DT_DATABASE);
  return options;
  }
return nullptr;
}

void OpenDBDialog::checkOptions()
{
if (ui->editName->text().isEmpty())
  {
  QMessageBox::warning(this,"Ошибка","Не задано имя БД!");
  return;
  }
if (ui->editHost->currentText().isEmpty())
  {
  QMessageBox::warning(this,"Ошибка","Не задано имя хоста!");
  return;
  }
if (ui->editIP->text().isEmpty())
  {
  QMessageBox::warning(this,"Ошибка","Не задан IP-адрес!");
  return;
  }
if (ui->editUser->text().isEmpty())
  {
  QMessageBox::warning(this,"Ошибка","Не задано имя пользователя!");
  return;
  }
if (ui->editPassword->text().isEmpty())
  {
  QMessageBox::warning(this,"Ошибка","Не задан пароль!");
  return;
  }
if (ui->editPort->text().isEmpty())
  {
  QMessageBox::warning(this,"Ошибка","Не задан порт!");
  return;
  }
if (ui->editDriver->currentText().isEmpty())
  {
  QMessageBox::warning(this,"Ошибка","Не задан драйвер!");
  return;
  }
accept();
}
