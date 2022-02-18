#ifndef SQL_QUERY_H
#define SQL_QUERY_H

#include <QObject>
#include <QSet>
#include "sql_globals.h"

class SqlEntity
{
public:
    virtual QString toString() const = 0;
};

class SqlJoin : public SqlEntity
{
public:
    SqlJoin(const QString &table,const QString &col1,const QString &col2);
    SqlJoin(const char* table,const char* col1,const char* col2);
    virtual QString toString() const;
private:
    QString m_table;
    QString m_col1;
    QString m_col2;
};

class SqlFilter : public SqlEntity
{
public:
    SqlFilter(const QString &item, const QStringList &values);
    SqlFilter(const QString &item, const QSet<QString> &values);
    SqlFilter(const QString &item, const QString &min,const QString &max);
    SqlFilter(const QString &item, const QPair<QString,QString> &interval);
    virtual QString toString() const;

private:
    QPair<QString,QStringList> data;
    bool type;
};

class SqlSelectQuery : public SqlEntity
{
public:
    SqlSelectQuery();
    SqlSelectQuery(const QStringList &items,
                   const QString &table,
                   const QList<SqlJoin> &joins={},
                   const QList<SqlFilter> &filters={},
                   const bool distinct=false,
                   const QString &orderby=nullptr,
                   const bool order_desc=false);
    static QString buildSelectQuery(const QStringList &items,
                                    const QString &table,
                                    const QList<SqlJoin> &joins={},
                                    const QList<SqlFilter> &filters={},
                                    const bool distinct=false,
                                    const QString &orderby=nullptr,
                                    const bool order_desc=false);
    static QString buildSelectQueryS(const QStringList &items,
                                    const QString &table,
                                    const QString &joins={},
                                    const QString &filters={},
                                    const bool distinct=false,
                                    const QString &orderby=nullptr,
                                    const bool order_desc=false);
    static QString buildUnion(const QString &query1, const QString &query2,
                              const QString &orderby=nullptr,
                              const bool order_desc=false);
    virtual QString toString() const;
    void resetFilters(const QList<SqlFilter> &filters={});
private:
    QStringList m_items;
    QString m_table;
    QList<SqlJoin> m_joins;
    QList<SqlFilter> m_filters;
    bool m_distinct;
    QString m_orderby;
    bool m_order_desc;


};

#endif // SQL_QUERY_H
