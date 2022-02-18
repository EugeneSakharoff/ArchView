#include "customdelegate.h"

CustomDelegate::CustomDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

//вспомогательная функция для позиционирования содержимого ячейки
QString CustomDelegate::anchorAt(QString html, const QPoint &point) const
{
QTextDocument doc;
doc.setHtml(html);

auto textLayout = doc.documentLayout();
Q_ASSERT(textLayout != 0);
return textLayout->anchorAt(point);
}

//отрисовывает содержимое ячейки
void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
auto options = option;
initStyleOption(&options, index);
painter->save();
//painter->setBackgroundMode(Qt::OpaqueMode);
//painter->setBrush(Qt::cyan);
//painter->setBackground(*br);
QTextDocument doc;
doc.setHtml(options.text);
options.text = "";
options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &option, painter);

painter->translate(options.rect.left(), options.rect.top());
QRect clip(0, 0, options.rect.width(), options.rect.height());
doc.drawContents(painter, clip);
//QStyledItemDelegate::paint(painter, options, index);
painter->restore();
}

void CustomDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
QStyledItemDelegate::initStyleOption(option,index);
//option->palette.setColor(QPalette::Normal, QPalette::Background, Qt::red);
//option->font.setBold(true);
//option->palette.setColor(QPalette::Normal, QPalette::Background, Qt::black);
//option->palette.setColor(QPalette::Normal, QPalette::Foreground, Qt::white);
}

//размер содержимого
QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
QStyleOptionViewItem options = option;
initStyleOption(&options, index);

QTextDocument doc;
doc.setHtml(options.text);
doc.setTextWidth(options.rect.width());
return QSize(doc.idealWidth(), doc.size().height());
}
