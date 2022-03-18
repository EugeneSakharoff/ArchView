#include "customtableview.h"


CustomTableView::CustomTableView(QWidget *parent):
    QTableView(parent)
{

}

void CustomTableView::init(QSortFilterProxyModel *model, CustomDelegate *delegate)
{
setModel(model);

//соединение сигналов по нажатию на заголовок для сортировки
horizontalHeader()->setSortIndicatorShown(true);
disconnect(horizontalHeader(),SIGNAL(sectionEntered(int)),this,SLOT(_q_selectColumn(int)));
disconnect(horizontalHeader(),SIGNAL(sectionPressed(int)),this,SLOT(selectColumn(int)));
sortByColumn(horizontalHeader()->sortIndicatorSection(),horizontalHeader()->sortIndicatorOrder());
connect(horizontalHeader(),SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this,SLOT(sortingRequested(int,Qt::SortOrder)),Qt::UniqueConnection);

//масштабирование столбцов
resizeColumnsToContents();
horizontalHeader()->setStretchLastSection(true);

//привязка правого клика мыши к слоту отображения контекстного меню
horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
connect(horizontalHeader(),&QHeaderView::customContextMenuRequested,this,&CustomTableView::customMenuRequested);

//перетаскивание столбцов
horizontalHeader()->setSectionsMovable(true);
horizontalHeader()->setDragEnabled(true);
horizontalHeader()->setDragDropMode(QAbstractItemView::InternalMove);

//отслеживание движения мыши
setMouseTracking(true);
connect(this,SIGNAL(hoverIndexChanged(QModelIndex&)),this,SLOT(onHoverIndexChanged(QModelIndex&)));

//отображение HTML
setItemDelegate(delegate);
}

//отслеживание движения мыши, посылает сигнал о смене ячейки
void CustomTableView::mouseMoveEvent(QMouseEvent *event)
{
QModelIndex index = this->indexAt(event->pos());
emit hoverIndexChanged(index);
}

//при смене ячейки, над которой указатель мыши, выводит всплывающую подсказку
void CustomTableView::onHoverIndexChanged(QModelIndex& index)
{
CustomSortModel* m = dynamic_cast<CustomSortModel*>(model());
//для столбца с именем переменной отображать описание
if (index.column() == m->aliasToHeaderIndex(SQL_GLOBALS::ALIAS_VARNAME))
  setToolTip(model()->data(model()->index(index.row(),m->aliasToHeaderIndex(SQL_GLOBALS::ALIAS_DESCR))).toString());
else
  setToolTip(model()->data(index).toString());
}

//слот, отображающий всплывающее меню при щелчке правой кнопкой мыши по заголовку таблицы
void CustomTableView::customMenuRequested(QPoint pos)
{
int index=horizontalHeader()->logicalIndexAt(pos); //индекс столбца, по которому клик
QMenu *menu=new QMenu(this);    //основное меню
QMenu *submenu;                 //подменю "показать"

CustomSortModel* m = dynamic_cast<CustomSortModel*>(model());
//соединяем действие "Скрыть" с лямбдой, скрывающей столбец по индексу
QAction *hide = menu->addAction("Скрыть");
connect(hide,&QAction::triggered,this,[=](){hideColumn(index);
                                            hidden_columns.append(m->headerData(index,Qt::Horizontal).toString());});

//добавляем подменю в основное меню
submenu = menu->addMenu("Показать");

//цикл по всем столбцам, чтобы составить список спрятанных и создать для них действие
foreach (const QString s, hidden_columns)
{
  hide = submenu->addAction(s); //добавляем действие. Параметр - имя столюца из модели
  connect(hide,&QAction::triggered,this,[=](){showColumn(m->headerToIndex(s));hidden_columns.removeAll(s);});//соединяем с лямбдой

}
//отобразить меню на нужной позиции
menu->popup(horizontalHeader()->viewport()->mapToGlobal(pos));
}

//при нажатии на заголовок таблицы вызывает сортировку
void CustomTableView::sortingRequested(int logicalIndex, Qt::SortOrder order)
{
CustomSortModel* m = dynamic_cast<CustomSortModel*>(model());
//если нажаты дата или время, то сортировка по столбцу "дата и время"
if(logicalIndex == m->aliasToHeaderIndex(SQL_GLOBALS::ALIAS_DATE) || logicalIndex == m->aliasToHeaderIndex(SQL_GLOBALS::ALIAS_TIME))
  {
  toDebug("Sorting by time",DT_TABLE);
  horizontalHeader()->setSortIndicator(logicalIndex, order);
  model()->sort(logicalIndex, order);
  }
else
  {
  toDebug("Default sorting",DT_TABLE);
  sortByColumn(logicalIndex,order);
  }
}

void CustomTableView::updateColumns()
{
CustomSortModel *md = dynamic_cast<CustomSortModel*>(model());
foreach (const QString item,hidden_columns)
  {
  toDebug(QString("hiding %1 at index %2").arg(item,md->headerToIndex(item)),DT_TABLE);
  hideColumn(md->headerToIndex(item));
  }
}

void CustomTableView::setHiddenColumns(const QStringList &list)
{
toDebug("setting hidden columns:",DT_TABLE);
//CustomSortModel *md = dynamic_cast<CustomSortModel*>(model());
//hidden_columns.clear();
/*for (int i=0; i<md->columnCount();i++)
{
  toDebug(QString(i)+ md->headerData(i,Qt::Horizontal).toString(),DT_TABLE);
  if (list.contains(md->headerData(i,Qt::Horizontal).toString()))
    hidden_columns.append(md->headerData(i,Qt::Horizontal).toString());
}
*/
hidden_columns=list;
updateColumns();
}

QStringList CustomTableView::hiddenColumns()
{
return hidden_columns;
}
