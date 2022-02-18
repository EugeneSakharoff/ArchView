#include "ui.h"

QSettings ui("ArchView.ini",QSettings::IniFormat);

namespace UI_GLOBALS {
const QString ALIAS_FOR_ALL      = ui.value("ui/ALIAS_FOR_ALL","...").toString();
const QString ALIAS_FOR_MESSAGES = ui.value("ui/ALIAS_FOR_MESSAGES","Сообщения").toString();
const QString ALIAS_FOR_ADD      = ui.value("ui/ALIAS_FOR_ADD","+").toString();
const QString ALIAS_FOR_REMOVE   = ui.value("ui/ALIAS_FOR_ADD","-").toString();
const QString ALIAS_FOR_SOLO     = ui.value("ui/ALIAS_FOR_ADD","S").toString();
const QString ALIAS_FOR_MUTE     = ui.value("ui/ALIAS_FOR_ADD","M").toString();
const QString ALIAS_FOR_RESET    = ui.value("ui/ALIAS_FOR_ADD",QString(QChar(8634))).toString();
const QString PLACEHOLDER        = ui.value("ui/ALIAS_FOR_ADD","").toString();

const int ELEMENT_HEIGHT          = ui.value("ui/ELEMENT_HEIGHT","22").toInt();
const int LABEL_WIDTH             = ui.value("ui/LABEL_WIDTH","70").toInt();
const int BUTTON_WIDTH            = ui.value("ui/BUTTON_WIDTH","18").toInt();
const int CONTROLS_TIMER_INTERVAL = ui.value("ui/CONTROLS_TIMER_INTERVAL","100").toInt();

const QColor COMBOBOX_SELECTED_FOREGROUND    = QColor(Qt::black);
const QColor COMBOBOX_SELECTED_BACKGROUND    = QColor(Qt::white);
const QColor COMBOBOX_NONSELECTED_FOREGROUND = QColor(Qt::gray);
const QColor COMBOBOX_NONSELECTED_BACKGROUND = QColor(Qt::white);

const QString QUERY_EXECUTED_COLOR = "lime";
const QString QUERY_FAILED_COLOR   = "red";
const QString QUERY_CHANGED_COLOR  = "yellow";
const QString QUERY_UNKNOWN_COLOR  = "gray";

const QString ERROR_TITLE = "Ошибка!";
const QString ERROR_OPENING_DB = "Не удалось открыть базу данных";

const QString QUERY_EDIT_EMPTY = "Не выбранны элементы для отображения";


const QString STATUS_DB_OPENED = "База данных подключенна";
const QString STATUS_DB_CLOSED = "База данных отключенна";
const QString STATUS_QUERY_EXECUTED = "Запрос выполнен";
const QString STATUS_QUERY_UPDATED = "Запрос обновлен";
const QString STATUS_INTERFACE_READY = "Готовность";
const QString STATUS_CURRENT_DB = QString("Текущая БД: %1 на %2");



bool DEFAULT_LAYOUT = true;
bool SHOW_QUERY_FIELD = true;

const QString PLOT_DATETIME_FORMAT = "hh:mm:ss";

QList<int> VIEW_CONTROLS_SPLITTER_SIZES = {500,1};
QList<int> CONTROLS_QUERY_SPLITTER_SIZES = {1,500};
}

void button_stylesheet(QWidget *object,QString color, int width,int radius)
{
object->setStyleSheet(QString("#%1 {border-style: outset;"
                              "border-width: %2 px;"
                              "border-radius: %3 px;"
                              "border-color: %4}").arg(object->objectName()).arg(width).arg(radius).arg(color));

}

