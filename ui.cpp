#include "ui.h"

QSettings ui("ArchView.ini",QSettings::IniFormat);

namespace UI_GLOBALS {
//Константы для интерфейса, внешнего вида программы

//Надписи на кнопках
const QString ALIAS_FOR_ALL      = ui.value("ui/ALIAS_FOR_ALL","...").toString();
const QString ALIAS_FOR_MESSAGES = ui.value("ui/ALIAS_FOR_MESSAGES","Сообщения").toString();
const QString ALIAS_FOR_ADD      = ui.value("ui/ALIAS_FOR_ADD","+").toString();
const QString ALIAS_FOR_ADD_ALL  = ui.value("ui/ALIAS_FOR_ADD_ALL","+").toString();
const QString ALIAS_FOR_REMOVE   = ui.value("ui/ALIAS_FOR_REMOVE","-").toString();
const QString ALIAS_FOR_REMOVE_ALL = ui.value("ui/ALIAS_FOR_REMOVE_ALL","-").toString();
const QString ALIAS_FOR_SOLO     = ui.value("ui/ALIAS_FOR_SOLO","S").toString();
const QString ALIAS_FOR_MUTE     = ui.value("ui/ALIAS_FOR_MUTE","M").toString();
const QString ALIAS_FOR_RESET    = ui.value("ui/ALIAS_FOR_RESET",QString(QChar(8634))).toString();
const QString PLACEHOLDER        = ui.value("ui/PLACEHOLDER","").toString();

//Размеры элементов для ControlElement
const int ELEMENT_HEIGHT          = ui.value("ui/ELEMENT_HEIGHT","22").toInt();
const int LABEL_WIDTH             = ui.value("ui/LABEL_WIDTH","70").toInt();
const int BUTTON_WIDTH            = ui.value("ui/BUTTON_WIDTH","18").toInt();
const int BIG_BUTTON_WIDTH        = ui.value("ui/BIG_BUTTON_WIDTH","18").toInt();
const int CONTROLS_TIMER_INTERVAL = ui.value("ui/CONTROLS_TIMER_INTERVAL","100").toInt();

//Цвета айтемсов в комбобоксах для ComboboxSelector
const QColor COMBOBOX_SELECTED_FOREGROUND    = QColor(Qt::black);
const QColor COMBOBOX_SELECTED_BACKGROUND    = QColor(Qt::white);
const QColor COMBOBOX_NONSELECTED_FOREGROUND = QColor(Qt::gray);
const QColor COMBOBOX_NONSELECTED_BACKGROUND = QColor(Qt::white);

//Цвета рамки для кнопки "Выполнить запрос"
const QString QUERY_EXECUTED_COLOR = "lime";
const QString QUERY_FAILED_COLOR   = "red";
const QString QUERY_CHANGED_COLOR  = "yellow";
const QString QUERY_UNKNOWN_COLOR  = "gray";

//некоторые сообщения для пользователя
const QString ERROR_TITLE = "Ошибка!";
const QString ERROR_OPENING_DB = "Не удалось открыть базу данных";
const QString QUERY_EDIT_EMPTY = "Не выбранны элементы для отображения";
const QString STATUS_DB_OPENED = "База данных подключенна";
const QString STATUS_DB_CLOSED = "База данных отключенна";
const QString STATUS_QUERY_EXECUTED = "Запрос выполнен";
const QString STATUS_QUERY_UPDATED = "Запрос обновлен";
const QString STATUS_INTERFACE_READY = "Готовность";
const QString STATUS_CURRENT_DB = QString("Текущая БД: %1 на %2");

//расположение элементов по умолчанию (вертикальное либо горизонтальное)
bool DEFAULT_LAYOUT = true;
//показывать поле запроса
bool SHOW_QUERY_FIELD = true;
//формат даты и времени на графике
const QString PLOT_DATETIME_FORMAT = "hh:mm:ss";
//параметры для начального расположения Splitter-ов
QList<int> VIEW_CONTROLS_SPLITTER_SIZES = {500,1};
QList<int> CONTROLS_QUERY_SPLITTER_SIZES = {1,500};
}

//отрисовка кнопки "выполнить запрос "
void button_stylesheet(QWidget *object,const QString& color,const int width,const int radius)
{
object->setStyleSheet(QString("#%1 {border-style: inset;"
                              "margin-left: 10px;"
                              "margin-right: 10px;"
                              "border-width: %2 px;"
                              "border-radius: %3 px;"
                              "border-color: %4}").arg(object->objectName()).arg(width).arg(radius).arg(color));

}

