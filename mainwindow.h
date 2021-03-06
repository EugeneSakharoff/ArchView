#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtWidgets/QWidget>
#include <QSqlQueryModel>
#include <qcustomplot.h>

#include "database.h"
#include "sql_globals.h"
#include "globals.h"
#include "customdelegate.h"
#include "ui_mainwindow.h"
#include "customsortmodel.h"
#include "customquerymodel.h"
#include "stringvalidator.h"
#include "itemselector.h"
#include "checkboxselector.h"
#include "intervalselector.h"
#include "optionswindow.h"
#include "opendbdialog.h"
#include "test_tables.h"

typedef QPair<QVector<double>,QVector<double>> PlotValues;
typedef QPair<QPair<double,double>,PlotValues> PlotData;

/////////////////////////////////////////////////////////////////////////////
// class MainWindow
/////////////////////////////////////////////////////////////////////////////

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void resetQuery();
    void itemSelectorChanged();
    void messagesSelectorChanged();
    void intervalSelectorChanged();
    void queryChanged();
    void sendQueryClicked();
    void optionsAccepted();
    void optionsRejected();
    void showOpenDBDialog();
    void showOptionsDialog();
    void closeDB();
	void afterInit();

private:
	Ui::MainWindow* ui;         //Интерфейс
	CustomQueryModel* model;      //модель представления данных
	CustomDelegate* delegate;
	DataBase* db;               //соединение с БД
	CustomSortModel* proxy;//класс для сортировки столбцов

	ItemSelector* itemSelector;
	CheckBoxSelector* messagesSelector;
	IntervalSelector* intervalSelector;

	QLabel* dbInfoLabel;

    bool currentLayout;

    void updatePlot();          //обновить график
    void createMenuBar();       //создание главного меню окна
    void setDataBase(const CONNECTION_PARAMS &params, const CONNECTION_PARAMS &service);         //инициализация БД
    void initModel();            //инициализация модели представления данных
    void initPlot();             //инициализация графика
    void changeLayout(); //сменить вид
    void initInterface();
    void resetInterface();
    void timerEvent(QTimerEvent *event);

    //получить список переменных для отображения в таблице и на графике
    void updateQuery();         //обновление текста запроса в текстовом поле
    int timer_num;  // номер таймера для автообновления
};

#endif
