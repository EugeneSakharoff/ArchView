#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

class CustomDelegate : public QStyledItemDelegate {

//Класс для отображения содержимого ячеек таблицы, нужен, чтобы отображать HTML
    Q_OBJECT

public:
    explicit CustomDelegate(QObject *parent = 0);

    QString anchorAt(QString html, const QPoint &point) const; //вспомогательная функция для позиционирования содержимого ячейки

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const; //отрисовывает содержимое ячейки
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;    //размер содержимого
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const;
};
#endif // CUSTOMDELEGATE_H
