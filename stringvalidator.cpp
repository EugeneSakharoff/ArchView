#include "stringvalidator.h"

stringValidator::stringValidator(QSet<QString> &list, QObject *parent) : QValidator(parent)
{
allowed_list = list;
m_model = nullptr;
}

stringValidator::stringValidator(QSqlQueryModel *model, QObject *parent) : QValidator(parent)
{
allowed_list = QSet<QString>();
m_model = model;
}

QValidator::State stringValidator::validate(QString &input, int &pos) const
{
if (m_model)
  {
    try
      {
      QString tmp;
      for (int i=0;i<m_model->rowCount();++i)
        {
        tmp = m_model->data(m_model->index(i,0)).toString();
        if (tmp==input) return QValidator::Acceptable;
        if(tmp.startsWith(input)) return QValidator::Intermediate;
        }
      return QValidator::Invalid;
      }
    catch (...)
      {
       toDebug("Validator error",DT_WARNING);
       return QValidator::Acceptable;
      }
  }
if (!allowed_list.isEmpty())
  {
  if (allowed_list.contains(input)) return QValidator::Acceptable;
  for (const QString &item: qAsConst(allowed_list))
    {
    if(item.startsWith(input)) return QValidator::Intermediate;
    }
  return QValidator::Invalid;
  }
return QValidator::Acceptable;
}
