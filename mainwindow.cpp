#include "mainwindow.h"
#include <QCoreApplication>

/////////////////////////////////////////////////////////////////////////////
// class MainWindow
/////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------
//конструктор
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow )
{
toDebug( "MainWindow constructor", DT_TRACE );
ui->setupUi( this );
currentLayout = true;
ui->controlPanel->setLayout( new QVBoxLayout( ui->controlPanel ) );

readSettings();

itemSelector = new ItemSelector( ui->controlPanel );
messagesSelector = new CheckBoxSelector( ui->controlPanel, UI_GLOBALS::ALIAS_FOR_MESSAGES );
intervalSelector = new IntervalSelector( ui->controlPanel );

//соединяем сигналы от элементов интерфейса со слотами
connect( intervalSelector, &IntervalSelector::changed, this, &MainWindow::intervalSelectorChanged );
connect( itemSelector, &ItemSelector::changed, this, &MainWindow::itemSelectorChanged );
connect( messagesSelector, &CheckBoxSelector::changed, this, &MainWindow::messagesSelectorChanged );
connect( ui->queryEdit, &QTextEdit::textChanged, this, &MainWindow::queryChanged );
connect( ui->sendQuery, &QPushButton::clicked, this, &MainWindow::sendQueryClicked );

db = new DataBase( this );
createMenuBar();
readHostsList();
initPlot();
initModel();
initInterface();
dbInfoLabel = new QLabel( statusBar() );
statusBar()->addPermanentWidget( dbInfoLabel );
if ( GLOBALS::CONNECT_ON_STARTUP )
  setDataBase(* db->getConnectParams() );
}

//--------------------------------------------------------
//деструктор
MainWindow::~MainWindow()
{
delete model;
delete db;
delete ui;
}

//--------------------------------------------------------
void MainWindow::afterInit()
{
toDebug( "afterInit()", DT_TRACE );
if ( UI_GLOBALS::DEFAULT_LAYOUT )
  changeLayout();
ui->controlPanel->layout()->setSpacing( 0 );
ui->controlPanel->layout()->setMargin( 0 );
ui->view_controls_splitter->setSizes( UI_GLOBALS::VIEW_CONTROLS_SPLITTER_SIZES );
ui->controls_query_splitter->setSizes( UI_GLOBALS::CONTROLS_QUERY_SPLITTER_SIZES );
}

//ИНИЦИАЛИЗАЦИЯ ИНТЕРФЕЙСА
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------
//инициализация БД
void MainWindow::setDataBase( const DBConnectParams &params )
{
toDebug( "setDataBase()", DT_TRACE );
if ( db->connectDataBase( params ) )
  {
    dbInfoLabel->setText( UI_GLOBALS::STATUS_CURRENT_DB.arg( params.getDBName(), params.getHostName() ) );

    //создать и заполнить тестовые таблицы
    if ( test_tables_structure::create_test_tables_flag )
      {
        create_test_tables( db );
        populate_test_tables( db );
      }

    using namespace SQL_GLOBALS;
    itemSelector->init(
        db->exec( SqlSelectQuery::buildSelectQuery( { NAME_COLUMN, GROUPID_COLUMN, DESCRIPTION_COLUMN },
                                                    DESCRIPTIONS_TABLE, {}, {}, false, NAME_COLUMN ) ),
        db->exec( SqlSelectQuery::buildSelectQuery( { NAME_COLUMN }, GROUPS_TABLE, {}, {}, true, NAME_COLUMN ) ) );
    intervalSelector->init(
        db->exec( SqlSelectQuery::buildSelectQuery(
            { QString( "MIN(%1)" ).arg( DATETIME_COLUMN ), QString( "MAX(%1)" ).arg( DATETIME_COLUMN ) },
            QString( "(%1) tmp" )
                .arg( SqlSelectQuery::buildUnion(
                    SqlSelectQuery::buildSelectQuery( { DATETIME_COLUMN }, VALUES_TABLE ),
                    SqlSelectQuery::buildSelectQuery( { DATETIME_COLUMN }, MESSAGES_TABLE ) ) ) ) ),
        db->exec( SqlSelectQuery::buildSelectQuery( { MESSAGE_COLUMN, DATETIME_COLUMN }, MESSAGES_TABLE, {},
                                                    { SqlFilter( MESSAGE_COLUMN, GLOBALS::STAGE_MSGS ) } ) ) );

    messagesSelector->init( db->exec( SqlSelectQuery::buildSelectQuery( { MESSAGE_COLUMN }, MESSAGES_TABLE ) ) );
    ui->sendQuery->setEnabled( true );
    ui->queryEdit->setEnabled( GLOBALS::EDIT_QUERY );
    ui->queryEdit->setVisible( GLOBALS::SHOW_QUERY );
    updateQuery();
    sendQueryClicked();
    if ( GLOBALS::HIDE_COLUMNS_BY_DEFAULT )
      ui->tableView->setHiddenColumns( SQL_GLOBALS::DEFAULT_HIDDEN_COLUMNS );
    statusBar()->showMessage( UI_GLOBALS::STATUS_DB_OPENED );
  }
else
  {
    QMessageBox::warning( this, UI_GLOBALS::ERROR_TITLE, UI_GLOBALS::ERROR_OPENING_DB );
    statusBar()->showMessage( UI_GLOBALS::STATUS_INTERFACE_READY );
  }
}

//--------------------------------------------------------
//инициализация модели представления данных
void MainWindow::initModel()
{
toDebug( "setModel()", DT_TRACE );
model = new CustomQueryModel( this );
delegate = new CustomDelegate( this );

//сортировка при нажатии на заголовок столбца
proxy = new CustomSortModel( model );
proxy->setSourceModel( model );

//инициализация таблицы
ui->tableView->init( proxy, delegate );
}

//инициализация графика
void MainWindow::initPlot()
{
toDebug( "setPlot()", DT_TRACE );
QSharedPointer<QCPAxisTickerDateTime> dateTicker( new QCPAxisTickerDateTime );
dateTicker->setDateTimeFormat( UI_GLOBALS::PLOT_DATETIME_FORMAT );
ui->plot->legend->setVisible( true );
ui->plot->xAxis->setTicker( dateTicker );
ui->plot->setInteraction( QCP::iRangeDrag, true );
ui->plot->setInteraction( QCP::iRangeZoom, true );
ui->plot->axisRect()->setRangeZoomAxes( ui->plot->xAxis, nullptr );
}

//--------------------------------------------------------
//создание главного меню окна
void MainWindow::createMenuBar()
{
toDebug( "createMenuBar()", DT_TRACE );
//Файл->{Открыть БД, Закрыть БД, Настройки, Выход}
QMenu* fileMenu = menuBar()->addMenu( "Файл" );
QAction* openDBAction = fileMenu->addAction( "Открыть архив..." );
QAction* closeDBAction = fileMenu->addAction( "Закрыть архив" );
QAction* optionsAction = fileMenu->addAction( "Настройки..." );
QAction* quitAction = fileMenu->addAction( "Выход" );
connect( openDBAction, &QAction::triggered, this, &MainWindow::showOpenDBDialog );
connect( closeDBAction, &QAction::triggered, this, &MainWindow::closeDB );
connect( optionsAction, &QAction::triggered, this, &MainWindow::showOptionsDialog );
connect( quitAction, &QAction::triggered, this, &QMainWindow::close );

QMenu* editMenu = menuBar()->addMenu( "Правка" );
QAction* resetAction = editMenu->addAction( "Сбросить запрос" );
connect( resetAction, &QAction::triggered, this, &MainWindow::resetQuery );

//Вид->Сменить
QMenu* viewMenu = menuBar()->addMenu( "Вид" );
QAction* changeAction = viewMenu->addAction( "Сменить" );
connect( changeAction, &QAction::triggered, this, &MainWindow::changeLayout );
//Справка->О программе
QMenu* helpMenu = menuBar()->addMenu( "Справка" );
QAction* aboutAction = helpMenu->addAction( "О программе..." );
connect( aboutAction, &QAction::triggered, this,
          [=]() { QMessageBox::about( this, "О программе", GLOBALS::ABOUT_TEXT ); } );
}

//--------------------------------------------------------
//построение графика
void MainWindow::updatePlot()
{
toDebug( "updatePlot()", DT_TRACE );
using namespace SQL_GLOBALS;
QCPGraph* graph;
QSqlQuery* query = db->exec( SqlSelectQuery::buildSelectQuery(
    DEFAULT_PLOT_ITEMS, VALUES_TABLE, { SqlJoin( DESCRIPTIONS_TABLE, VARID, DESCRIPTIONS_ID ) },
    { SqlFilter( DATETIME, intervalSelector->getInterval() ), SqlFilter( VARNAME, itemSelector->varSet() ) } ) );
ui->plot->clearGraphs();
QMap<QString, QSharedPointer<QCPGraphDataContainer>> plot_data;
toDebug( query->lastQuery(), DT_PLOT );
foreach ( const QString s, itemSelector->varSet() )
  {
    QSharedPointer<QCPGraphDataContainer> data( new QCPGraphDataContainer );
    toDebug( "Created dataContainer for " + s, DT_PLOT );
    plot_data.insert( s, data );
  }

while ( query->next() )
  {
    toDebug( "Adding to container " + query->value( 0 ).toString() + " " + query->value( 1 ).toString() + " " +
                  query->value( 2 ).toString(),
              DT_PLOT );

    plot_data[query->value( 1 ).toString()]->add( QCPGraphData(
        QDateTime::fromString( query->value( 0 ).toString(), GLOBALS::DEFAULT_DATETIME_FORMAT ).toSecsSinceEpoch(),
        query->value( 2 ).toDouble() ) );
  }
int i = 0;
foreach ( const QString s, itemSelector->varSet() )
  {
    qDebug() << s << plot_data[s];
    graph = ui->plot->addGraph();
    graph->setData( plot_data[s] );
    graph->setName( s );
    graph->setPen( QPen( QColor( Qt::GlobalColor( 7 + i % 11 ) ) ) );
    i++;
  }
ui->plot->rescaleAxes();
ui->plot->replot();
delete query;
}

//обновление текста запроса в текстовом поле
void MainWindow::updateQuery()
{
toDebug( "updateQuery()", DT_TRACE );
using namespace SQL_GLOBALS;
ui->sendQuery->setEnabled( true );
if ( itemSelector->varSet().isEmpty() )
  {
    if ( messagesSelector->isChecked() )
      ui->queryEdit->setPlainText(
          SqlSelectQuery::buildSelectQuery( buildMessageItems( DEFAULT_VALS_ITEMS ), MESSAGES_TABLE ) );
    else
      {
        ui->queryEdit->setPlainText( UI_GLOBALS::QUERY_EDIT_EMPTY );
        ui->sendQuery->setEnabled( false );
      }
    return;
  }

QList<SqlFilter> filters = {};

filters.append( SqlFilter( DATETIME, intervalSelector->getInterval() ) );
if ( itemSelector->varSet().count() != itemSelector->fullSet().count() )
  filters.append( SqlFilter( VARNAME, itemSelector->varSet() ) );

QString additional = nullptr;
if ( messagesSelector->isChecked() )
  additional = SqlSelectQuery::buildSelectQuery( buildMessageItems( DEFAULT_VALS_ITEMS ), MESSAGES_TABLE, {},
                                                  { filters.at( 0 ) } );

ui->queryEdit->setPlainText( SqlSelectQuery::buildUnion(
    SqlSelectQuery::buildSelectQuery(
        DEFAULT_VALS_ITEMS, VALUES_TABLE,
        { SqlJoin( DESCRIPTIONS_TABLE, VARID, DESCRIPTIONS_ID ), SqlJoin( GROUPS_TABLE, GROUPID, GROUPS_ID ) },
        filters ),
    additional ) );

statusBar()->showMessage( UI_GLOBALS::STATUS_QUERY_UPDATED );
}

//СЛОТЫ
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------
//слот, обновляющий запрос к БД при изменении фильтра по имени переменной
void MainWindow::itemSelectorChanged()
{
toDebug( "itemSelectorChanged()", DT_TRACE );
updateQuery();
}

//--------------------------------------------------------
//слот, обновляющий запрос к БД при изменении временного интервала
void MainWindow::intervalSelectorChanged()
{
toDebug( "intervalSelectorChanged()", DT_TRACE );
updateQuery();
}

//--------------------------------------------------------
void MainWindow::messagesSelectorChanged()
{
toDebug( "messsageSelectorChanged()", DT_TRACE );
updateQuery();
}

//--------------------------------------------------------
void MainWindow::queryChanged()
{
toDebug( "queryChanged()", DT_TRACE );
button_stylesheet( ui->sendQuery, UI_GLOBALS::QUERY_CHANGED_COLOR );
statusBar()->showMessage( UI_GLOBALS::STATUS_QUERY_UPDATED );
}

//--------------------------------------------------------
//слот, выполняющий запрос к БД нажатии на кнопку
void MainWindow::sendQueryClicked()
{
toDebug( "sendQueryClicked()", DT_TRACE );
if ( !db->isConnected() )
  {
    ( new QErrorMessage( this ) )->showMessage( "База данных не подключена" );
    return;
  }
if ( ui->queryEdit->toPlainText().split( " " ).at( 0 ).toUpper() == "SELECT" )
  {
    //первое слово запроса=SELECT - обновить модель
	model->updateQuery( ui->queryEdit->toPlainText(), SQL_GLOBALS::DEFAULT_ALIASES,* db->getDbPointer() );
    button_stylesheet( ui->sendQuery, UI_GLOBALS::QUERY_EXECUTED_COLOR );
    ui->tableView->updateColumns();
    updatePlot();
  }
else
  {
    //для прочих запросов просто выполнить запрос
    db->exec( ui->queryEdit->toPlainText() );
    updateQuery();
  }
statusBar()->showMessage( UI_GLOBALS::STATUS_QUERY_EXECUTED );
}

//--------------------------------------------------------
//слот, меняющий лейаут
void MainWindow::changeLayout()
{
toDebug( "changeLayout()", DT_TRACE );
QLayout* layout;
delete ui->centralwidget->layout();
if ( currentLayout )
  {
    layout = new QHBoxLayout( ui->centralwidget );
    ui->view_controls_splitter->setOrientation( Qt::Horizontal );
  }
else
  {
    layout = new QVBoxLayout( ui->centralwidget );
    ui->view_controls_splitter->setOrientation( Qt::Vertical );
  }
layout->addWidget( ui->view_controls_splitter );
ui->centralwidget->setLayout( layout );
currentLayout = !currentLayout;
ui->centralwidget->update();
}

//--------------------------------------------------------
void MainWindow::resetQuery()
{
toDebug( "resetQuery()", DT_TRACE );
if ( db->isConnected() )
  {
    itemSelector->reset();
    intervalSelector->reset();
    messagesSelector->reset();
    updateQuery();
  }
}

//--------------------------------------------------------
void MainWindow::optionsAccepted()
{
}

//--------------------------------------------------------
void MainWindow::optionsRejected()
{
}

//--------------------------------------------------------
void MainWindow::showOpenDBDialog()
{
toDebug( "showOpenDBDialog()", DT_TRACE );
OpenDBDialog* dialog = new OpenDBDialog(* db->getConnectParams(), this );
DBConnectParams* params = dialog->getDBParams();
if ( params != nullptr )
  {
    if ( db->isConnected() )
      closeDB();
	setDataBase(* params );
  }
delete dialog;
}

//--------------------------------------------------------
void MainWindow::showOptionsDialog()
{
toDebug( "showOptionsDialog()", DT_TRACE );
OptionsWindow* dialog = new OptionsWindow( this );
dialog->exec();
resetInterface();
}

//--------------------------------------------------------
void MainWindow::closeDB()
{
toDebug( "closeDB()", DT_TRACE );
resetInterface();
db->close();
dbInfoLabel->setText( "" );
statusBar()->showMessage( UI_GLOBALS::STATUS_DB_CLOSED );
}

//--------------------------------------------------------
void MainWindow::initInterface()
{
toDebug( "initInterface()", DT_TRACE );
itemSelector->init();
intervalSelector->init();
messagesSelector->init();
ui->queryEdit->setPlainText( "" );
ui->queryEdit->setEnabled( false );
button_stylesheet( ui->sendQuery, UI_GLOBALS::QUERY_UNKNOWN_COLOR );
ui->sendQuery->setEnabled( false );
model->clear();
ui->plot->clearGraphs();
ui->tableView->setHiddenColumns( SQL_GLOBALS::DEFAULT_HIDDEN_COLUMNS );
statusBar()->showMessage( UI_GLOBALS::STATUS_INTERFACE_READY );
}

//--------------------------------------------------------
void MainWindow::resetInterface()
{
toDebug( "resetInterface()", DT_TRACE );
itemSelector->reset();
intervalSelector->reset();
messagesSelector->reset();
ui->tableView->setHiddenColumns( SQL_GLOBALS::DEFAULT_HIDDEN_COLUMNS );
ui->queryEdit->setEnabled( GLOBALS::EDIT_QUERY );
ui->queryEdit->setVisible( GLOBALS::SHOW_QUERY );
statusBar()->showMessage( UI_GLOBALS::STATUS_INTERFACE_READY );
}
