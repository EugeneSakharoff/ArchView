#ifndef UI_H
#define UI_H

#include <QtGlobal>
#include <QString>
#include <QMap>
#include <QColor>
#include <QWidget>
#include <QDebug>
#include <QSettings>

extern QSettings ui;
namespace UI_GLOBALS {

//названия (лейблы) элементов интерфейса
extern const QString ALIAS_FOR_ALL;
extern const QString ALIAS_FOR_MESSAGES;
extern const QString ALIAS_FOR_ADD;
extern const QString ALIAS_FOR_REMOVE;
extern const QString ALIAS_FOR_ADD_ALL;
extern const QString ALIAS_FOR_REMOVE_ALL;
extern const QString ALIAS_FOR_SOLO;
extern const QString ALIAS_FOR_MUTE;
extern const QString ALIAS_FOR_RESET;
extern const QString PLACEHOLDER;

extern const int ELEMENT_HEIGHT;
extern const int LABEL_WIDTH;
extern const int BUTTON_WIDTH;
extern const int BIG_BUTTON_WIDTH;
extern const int CONTROLS_TIMER_INTERVAL;
extern const QColor COMBOBOX_SELECTED_FOREGROUND;
extern const QColor COMBOBOX_SELECTED_BACKGROUND;
extern const QColor COMBOBOX_NONSELECTED_FOREGROUND;
extern const QColor COMBOBOX_NONSELECTED_BACKGROUND;

extern const QString QUERY_EXECUTED_COLOR;
extern const QString QUERY_FAILED_COLOR;
extern const QString QUERY_CHANGED_COLOR;
extern const QString QUERY_UNKNOWN_COLOR;

extern const QString PLOT_DATETIME_FORMAT;

extern bool DEFAULT_LAYOUT;
extern bool SHOW_QUERY_FIELD;

extern QList<int> VIEW_CONTROLS_SPLITTER_SIZES;
extern QList<int> CONTROLS_QUERY_SPLITTER_SIZES;

extern const QString ERROR_TITLE;
extern const QString ERROR_OPENING_DB;

extern const QString QUERY_EDIT_EMPTY;

extern const QString STATUS_DB_OPENED;
extern const QString STATUS_DB_CLOSED;
extern const QString STATUS_QUERY_EXECUTED;
extern const QString STATUS_QUERY_UPDATED;
extern const QString STATUS_INTERFACE_READY;
extern const QString STATUS_CURRENT_DB;

}

void button_stylesheet(QWidget *object,const QString& color,const int width=1,const int radius=0);
#endif // UI_H
