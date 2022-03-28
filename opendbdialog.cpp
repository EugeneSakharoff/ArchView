#include "opendbdialog.h"

/////////////////////////////////////////////////////////////////////////////
// class OpenDBDialog
/////////////////////////////////////////////////////////////////////////////

OpenDBDialog::OpenDBDialog( const DBConnectParams &params, QWidget *parent )
    : QDialog( parent ), ui( new Ui::OpenDBDialog )
{
  ui->setupUi( this );
  setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );
  connect( ui->buttonBox, &QDialogButtonBox::accepted, this, &OpenDBDialog::checkOptions );
  disconnect( ui->buttonBox, SIGNAL( accepted() ), this, SLOT( accept() ) );

  QRegExp rx( QString( "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$" ) );
  QValidator *IPValidator = new QRegExpValidator( rx, this );
  ui->editIP->setValidator( IPValidator );

  QIntValidator *portValidator = new QIntValidator( this );
  ui->editPort->setValidator( portValidator );

  readHostsList();
  //составляем список хостов из HOSTS_MAP
  QMap<QString, QString>::iterator it;
  for ( it = GLOBALS::HOSTS_MAP.begin(); it != GLOBALS::HOSTS_MAP.end(); ++it )
    ui->editHost->addItem( it.key() );

  //выставляем индекс на текущий хост
  int index = ui->editHost->findText( params.getHostName() );
  if ( index >= 0 )
    {
      ui->editHost->setCurrentIndex( index );
      if ( params.getHostAddr() != GLOBALS::HOSTS_MAP[params.getHostName()] )
        toDebug( "Current host addres does not match: " + params.getHostName() + params.getHostAddr(), DT_WARNING );
    }
  else
    {
      toDebug( "Current host name not on the list: " + params.getHostName(), DT_WARNING );
      ui->editHost->addItem( params.getHostName() );
      ui->editHost->setCurrentIndex( ui->editHost->count() - 1 );
    }
  ui->editIP->setText( params.getHostAddr() );

  connect( ui->editHost, &QComboBox::currentTextChanged, this, &OpenDBDialog::editHostChanged );

  ui->editName->setText( params.getDBName() );
  ui->editUser->setText( params.getUserName() );
  ui->editPassword->setText( params.getPassword() );
  ui->editPort->setText( params.getPort() );

  //составляем список драйверов и ищем в нем текущий
  ui->editDriver->addItems( GLOBALS::AVAILABLE_DRIVERS );
  index = ui->editDriver->findText( params.getDriver() );
  if ( index >= 0 )
    ui->editDriver->setCurrentIndex( index );
  else
    {
      toDebug( "Current driver not on the list: " + params.getDriver(), DT_ERROR );
      ui->editDriver->addItem( params.getDriver() );
      ui->editDriver->setCurrentIndex( ui->editDriver->count() - 1 );
    }
}

void OpenDBDialog::editHostChanged()
{
  ui->editIP->setText( GLOBALS::HOSTS_MAP[ui->editHost->currentText()] );
}

OpenDBDialog::~OpenDBDialog()
{
  delete ui;
}

DBConnectParams *OpenDBDialog::getDBParams()
{
  if ( this->exec() == 1 )
    {
      DBConnectParams *params = new DBConnectParams( ui->editName->text(), ui->editHost->currentText(),
                                                     ui->editIP->text(), ui->editUser->text(), ui->editPassword->text(),
                                                     ui->editPort->text(), ui->editDriver->currentText() );
      toDebug( "Setting DB params: " + params->getHostName() + params->getHostAddr(), DT_DATABASE );
      return params;
    }
  return nullptr;
}

void OpenDBDialog::checkOptions()
{
  if ( ui->editName->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задано имя архива!" );
      return;
    }
  if ( ui->editHost->currentText().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задано имя хоста!" );
      return;
    }
  if ( ui->editIP->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задан IP-адрес!" );
      return;
    }
  if ( ui->editUser->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задано имя пользователя!" );
      return;
    }
  if ( ui->editPassword->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задан пароль!" );
      return;
    }
  if ( ui->editPort->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задан порт!" );
      return;
    }
  if ( ui->editDriver->currentText().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задан драйвер!" );
      return;
    }
  accept();
}
