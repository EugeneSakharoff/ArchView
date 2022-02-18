#ifndef STRINGVALIDATOR_H
#define STRINGVALIDATOR_H

#include <QValidator>
#include <QObject>
#include <QSet>
#include <QSqlQueryModel>
#include <QDebug>
#include "globals.h"

class stringValidator : public QValidator
{
    Q_OBJECT
public:
    stringValidator(QSet<QString> &list, QObject *parent = nullptr);
    stringValidator(QSqlQueryModel *model, QObject *parent = nullptr);
    QValidator::State validate(QString &input, int &pos) const;
private:
    QSet<QString> allowed_list;
    QSqlQueryModel *m_model;
};

#endif // STRINGVALIDATOR_H
