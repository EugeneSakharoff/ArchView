#include "customsortmodel.h"
//класс нужен для "правильной" сортировки столбцов, переопределяет функцию lessThan()
CustomSortModel::CustomSortModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

//корректное сравнение значений
bool CustomSortModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) {
QString a;
QString b;
if (sortCaseSensitivity()  == Qt::CaseSensitive)
  {
  a = sourceModel()->data(source_left).toString();
  b = sourceModel()->data(source_right).toString();
  }
else
  {
  a = sourceModel()->data(source_left).toString().toLower();
  b = sourceModel()->data(source_right).toString().toLower();
  }

const QChar* currA = a.unicode(); // iterator over a
const QChar* currB = b.unicode(); // iterator over b

if (currA == currB) return false;

while (!currA->isNull() && !currB->isNull())
  {
  const QChar* begSeqA = currA; // beginning of a new character sequence of a
  const QChar* begSeqB = currB;

  if (currA->unicode() == QChar::ObjectReplacementCharacter) return true;

  if (currB->unicode() == QChar::ObjectReplacementCharacter) return false;

  if (currA->unicode() == QChar::ReplacementCharacter) return true;

  if (currB->unicode() == QChar::ReplacementCharacter) return false;

  // find sequence of characters ending at the first non-character
  while (!currA->isNull() && !currA->isDigit() && !currA->isPunct() && !currA->isSpace()) ++currA;

  while (!currB->isNull() && !currB->isDigit() && !currB->isPunct() && !currB->isSpace()) ++currB;

  // compare these sequences
  const QStringRef & subA(a.midRef(begSeqA - a.unicode(), currA - begSeqA));
  const QStringRef& subB(b.midRef(begSeqB - b.unicode(), currB - begSeqB));
  const int cmp = QStringRef::localeAwareCompare(subA, subB);

  if (cmp != 0) return cmp < 0 ? -1 : +1;

  if (currA->isNull() || currB->isNull()) break;

  // find sequence of characters ending at the first non-character
  while ((currA->isPunct() || currA->isSpace()) && (currB->isPunct() || currB->isSpace()))
    {
    if (*currA != *currB) return (*currA < *currB) ? -1 : +1;

    ++currA;
    ++currB;
    if (currA->isNull() || currB->isNull()) break;
    }

  // now some digits follow...
  if ((*currA == QLatin1Char('0')) || (*currB == QLatin1Char('0')))
    // one digit-sequence starts with 0 -> assume we are in a fraction part
    // do left aligned comparison (numbers are considered left aligned)
    while (1)
      {
      if (!currA->isDigit() && !currB->isDigit()) break;

      else if (!currA->isDigit()) return true;

      else if (!currB->isDigit()) return false;

      else if (*currA < *currB) return false;

      else if (*currA > *currB) return true;
      ++currA;
      ++currB;
      }
  else
    {
    // No digit-sequence starts with 0 -> assume we are looking at some integer
    // do right aligned comparison.
    //
    // The longest run of digits wins. That aside, the greatest
    // value wins, but we can't know that it will until we've scanned
    // both numbers to know that they have the same magnitude.

    bool isFirstRun = true;
    int weight = 0;
    while (1)
      {
      if (!currA->isDigit() && !currB->isDigit())
        {
        if (weight != 0) return weight;
                    break;
        }
      else
        if (!currA->isDigit())
          {
          if (isFirstRun) return *currA < *currB ? -1 : +1;
          else return false;
          }
        else
          if (!currB->isDigit())
            {
            if (isFirstRun) return *currA < *currB ? -1 : +1;
            else return +1;
            }
          else
            if (( *currA < *currB) && (weight == 0 )) weight = -1;
            else if (( *currA > *currB) && (weight == 0 )) weight = +1;

        ++currA;
        ++currB;
        isFirstRun = false;
        }
      }
  }

  if (currA->isNull() && currB->isNull()) return 0;

  return currA->isNull() ? -1 : + 1;
}

//индекс столбца по псевдониму
int CustomSortModel::aliasToHeaderIndex(const QString &alias) const
{
CustomQueryModel *m = dynamic_cast<CustomQueryModel*>(sourceModel());
return m->aliasToHeaderIndex(alias);
}

int CustomSortModel::headerToIndex(const QString &header) const
{
CustomQueryModel *m = dynamic_cast<CustomQueryModel*>(sourceModel());
return m->headerToIndex(header);
}


QStringList CustomSortModel::headersAliases() const
{
CustomQueryModel *m = dynamic_cast<CustomQueryModel*>(sourceModel());
return m->headersAliases();
}

