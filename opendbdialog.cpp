
#include "opendbdialog.h"

/////////////////////////////////////////////////////////////////////////////
// class OpenDBDialog
//Окно диалога открытия БД
/////////////////////////////////////////////////////////////////////////////

OpenDBDialog::OpenDBDialog( const DBConnectParams *current_params, QWidget *parent )
    : QDialog( parent ), ui( new Ui::OpenDBDialog )
{

  ui->setupUi( this );
  setWindowFlags( windowFlags() & ~Qt::WindowContextHelpButtonHint );
  connect( ui->groupBoxAdvanced, &QGroupBox::clicked, this, &OpenDBDialog::resizeAdvancedGroupBox);
  connect(ui->buttonBox,&QDialogButtonBox::accepted,this,&OpenDBDialog::tryAccept);

  disconnect( ui->buttonBox, SIGNAL( accepted() ), this, SLOT( accept() ) );

  ui->groupBoxAdvanced->setEnabled(GLOBALS::ALLOW_ADVANCED_DB_SETTINGS);
  ui->groupBoxAdvanced->setVisible(GLOBALS::ALLOW_ADVANCED_DB_SETTINGS);
  ui->editPassword->setEchoMode(QLineEdit::Password);
  QRegExp ipRegExp( QString( "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)(\\.(?!$)|$)){4}$" ) );//для IPадреса
  QValidator *IPValidator = new QRegExpValidator( ipRegExp, this );
  ui->editIP->setValidator( IPValidator );
  QIntValidator *portValidator = new QIntValidator( this );
  ui->editPort->setValidator( portValidator );

  //составляем список хостов из HOSTS_MAP
  ui->editPreset->addItems(GLOBALS::CONNECTION_PRESETS.keys());
  ui->editDriver->addItems( GLOBALS::AVAILABLE_DRIVERS );
  if (ui->editDriver->findText( GLOBALS::DEFAULT_DB_DRIVER )<0)
      ui->editDriver->addItem(GLOBALS::DEFAULT_DB_DRIVER);

  CONNECTION_PARAMS params;
  if (current_params)
      params = *current_params->getParams();
  else
      params = GLOBALS::CONNECTION_PRESETS[GLOBALS::DEFAULT_PRESET];

  qDebug()<<params.dbName<<params.hostName<<params.hostAddress<<params.dbUser<<params.dbPassword<<params.dbPort<<params.driver;

  ui->editHost->setText( params.hostName );
  ui->editIP->setText( params.hostAddress );
  ui->editName->setText( params.dbName );
  ui->editUser->setText( params.dbUser );
  ui->editPassword->setText( params.dbPassword );
  ui->editPort->setText( params.dbPort);
  int index = ui->editDriver->findText( params.driver);
  if ( index >= 0 )
    ui->editDriver->setCurrentIndex( index );
  else
    {
    toDebug( "Current driver not on the list: " + params.driver, DT_ERROR );
    ui->editDriver->setCurrentIndex(ui->editDriver->findText( GLOBALS::DEFAULT_DB_DRIVER ));
    }
  connect( ui->editPreset, &QComboBox::currentTextChanged, this, &OpenDBDialog::editPresetChanged );
  resizeAdvancedGroupBox();
}

void OpenDBDialog::editPresetChanged()
{
  ui->editHost->setText( GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].hostName );
  ui->editIP->setText( GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].hostAddress );
  ui->editName->setText( GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].dbName );
  ui->editUser->setText( GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].dbUser );
  ui->editPassword->setText( GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].dbPassword );
  ui->editPort->setText( GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].dbPort );
  int index = ui->editDriver->findText( GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].driver );
  if ( index >= 0 )
    ui->editDriver->setCurrentIndex( index );
  else
    {
      toDebug( "Driver not on the list: " + GLOBALS::CONNECTION_PRESETS[ui->editPreset->currentText()].driver, DT_WARNING );
      ui->editDriver->setCurrentIndex(ui->editDriver->findText( GLOBALS::DEFAULT_DB_DRIVER ));
    }
}

OpenDBDialog::~OpenDBDialog()
{
  delete ui;
}

//возвращает параметры соединения, которые выбрал пользователь
CONNECTION_PARAMS* OpenDBDialog::getDBParams()
{
  if ( this->exec() == 1 )
    {
      CONNECTION_PARAMS *params =  new CONNECTION_PARAMS();
      check();

      params->hostName = ui->editHost->text();
      params->hostAddress = ui->editIP->text();
      params->dbName = ui->editName->text();
      params->dbUser = ui->editUser->text();
      params->dbPassword = ui->editPassword->text();
      params->dbPort = ui->editPort->text();
      params->driver = ui->editDriver->currentText();
      return params;
    }
  return nullptr;
}

//проверка заданных польхователем параметров
bool OpenDBDialog::check()
{
  if ( ui->editName->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задано имя архива!" );
      return false;
    }
  if ( ui->editHost->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задано имя хоста!" );
      return false;
    }
  if ( ui->editIP->text().isEmpty() )
    { 
      QMessageBox::warning( this, "Ошибка", "Не задан IP-адрес!" );
      return false;
    }
  if ( ui->editUser->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задано имя пользователя!" );
      return false;
    }
  if ( ui->editPassword->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задан пароль!" );
      return false;
    }
  if ( ui->editPort->text().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задан порт!" );
      return false;
    }
  if ( ui->editDriver->currentText().isEmpty() )
    {
      QMessageBox::warning( this, "Ошибка", "Не задан драйвер!" );
      return false;
    }
return true;
}

void OpenDBDialog::tryAccept()
{
if(check())
    accept();
}

//Правильная отрисовка, когда подробные настройки подключения скрыты
void OpenDBDialog::resizeAdvancedGroupBox()
{
    if (!ui->groupBoxAdvanced->isChecked())
    {
        ui->groupBoxAdvanced->setFlat(true);
        ui->groupBoxAdvanced->setMaximumHeight(UI_GLOBALS::ELEMENT_HEIGHT);
        ui->groupBoxAdvanced->setMinimumHeight(UI_GLOBALS::ELEMENT_HEIGHT);
        setFixedHeight(ui->groupBoxSimple->height()+ui->buttonBox->height()+layout()->spacing()*2+UI_GLOBALS::ELEMENT_HEIGHT+layout()->margin()*2);
    }
    else
    {
        ui->groupBoxAdvanced->setFlat(false);
        int height = UI_GLOBALS::ELEMENT_HEIGHT*6+ui->groupBoxAdvanced->layout()->spacing()*5+ui->groupBoxAdvanced->layout()->margin()*2;
        ui->groupBoxAdvanced->setMaximumHeight(height);
        ui->groupBoxAdvanced->setMinimumHeight(height);
        setFixedHeight(ui->groupBoxSimple->height()+ui->buttonBox->height()+layout()->spacing()*2+height+layout()->margin()*2);
    }
}
