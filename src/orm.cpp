/**
 * orm.cpp
 *
 *  Copyright 2016 by Joao Pedro Vieira Pereira Silva <jpvieirapereira@hotmail.com>
 *  Copyright 2015 by Victor Vieira Pereira Silva <victordoctorx@hotmail.com>
 *  Copyright 2014 by Marco Bueno <bueno.marco@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later.
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 */


#include "orm.h"
#include <QDebug>

#include <QSqlDriver>
#include <QSqlField>
#include "fieldfactory.h"


#define ATTR_VALUE(attr) IS_STRING_VALUE(attr) ? ("\'" + attr->toString().replace("\'", "\'\'") + "\'") : attr->toString()

#define TABLE_EXISTS() getDatabase().tables().contains(m_tableName)
#define FIELD_EXISTS(field) getDatabase().record(m_tableName).contains(field)

QMap<QString, QString> ORM::m_fieldMap;


ORM::ORM()
{

}

void ORM::setLastError(QSqlError error)
{
    m_lastError = error;
}

QSqlError ORM::lastError()
{
    return m_lastError;
}

void ORM::InitAttribute(ORMAttribute *attr)
{
    switch (attr->type())
    {
        case ATTR_QString: attr->setValue("");                     break;
        case ATTR_Serial:
        case ATTR_int:     attr->setValue(0);                      break;
        case ATTR_double:  attr->setValue(0.0);                    break;
        case ATTR_bool:    attr->setValue(false);                  break;
        case ATTR_QDate:   attr->setValue(QDate(2000, 1, 1));      break;
        case ATTR_QTime:   attr->setValue(QTime(0, 0, 0, 0));      break;
        case ATTR_QChar:   attr->setValue('0');                    break;
        case ATTR_char:    attr->setValue(0);                    break;
        default:
            qDebug() << "Attribute Failed: " << attr->fieldName().toUtf8().data();
            return;
    }
}

QList<ORMAttribute*> ORM::attributes()
{
    return m_attrList;
}

void ORM::EnsureFieldsExist()
{
    foreach(ORMAttribute *attr, m_attrList)
    {
       if( !FIELD_EXISTS( attr->fieldName() ) )
       {
            QString strCreate = QString::fromUtf8("ALTER TABLE %1 ADD COLUMN %2").arg(m_tableName).arg(CreateFieldTxt( attr ) + ";");

            QSqlQuery *query = new QSqlQuery(getDatabase());

            if( query->exec( QString(strCreate) ) < 1 )
            {
                if( !query->lastError().text().contains("exists"))
                    setLastError(query->lastError());
            }
            delete query;
       }
    }
}

QString ORM::CreateFieldTxt( ORMAttribute *attr )
{
    QString field;

    CmdInterface *builder = FieldFactory::Create(getDatabase().driver()->dbmsType());

    if( attr == m_primaryKey)
    {
        field = builder->CmdInt(attr->fieldName(),true,true);
    }
    else
    {
        switch( attr->type() )
        {
            case ATTR_int    :
                               field = builder->CmdInt(attr->fieldName());
                break;
            case ATTR_double:
                               field = builder->CmdDouble(attr->fieldName(),11,3);
                break;
            case ATTR_bool:
                               field = builder->CmdBool(attr->fieldName());
                break;
            case ATTR_QDate:
                               field = builder->CmdDate(attr->fieldName());
                break;
            case ATTR_QTime:
                               field = builder->CmdTime(attr->fieldName());
                break;
            case ATTR_QString:
            default:
                               field = builder->CmdString(attr->fieldName());
                break;
        }
    }
    delete builder;
    return field;
}

void ORM::CreateTable()
{
    bool bFirst =  true;
    ORMAttribute *pKey = NULL;

    QString strCreate = QString::fromUtf8("CREATE TABLE %1 ( ").arg(m_tableName);

    foreach(ORMAttribute *attr, m_attrList)
    {
        if( !bFirst )
            strCreate +=  " , ";

        if( attr == m_primaryKey )
        {
            pKey =  attr;
        }

        strCreate += CreateFieldTxt( attr );
        bFirst = false;
    }

    if(pKey && getDatabase().driverName() != "QSQLITE")
       strCreate += QString::fromUtf8(" , CONSTRAINT %1_pkey PRIMARY KEY (%2) ")
                                      .arg(m_tableName)
                                      .arg(pKey->fieldName());

    strCreate += QString::fromUtf8(");");

    QSqlQuery *newTable =  new QSqlQuery(getDatabase());
    if( newTable->exec( strCreate ) < 1 )
    {
        setLastError(newTable->lastError());
    }
    delete newTable;
}

void ORM::copyFrom(ORM* ORM)
{
    for (int i = 0; i < m_attrList.length(); i++)
    {
        ORMAttribute* attrTo = m_attrList.at(i);
        ORMAttribute* attrFrom = ORM->attributes().at(i);

        if ((attrFrom->fieldName() != attrTo->fieldName()) || (attrFrom->type() != attrTo->type()))
        {
            continue;
        }

        attrTo->setValue(attrFrom->value());
    }
}

void ORM::fillORM(QSqlRecord record)
{
    foreach(ORMAttribute *attr, m_attrList)
    {
        QVariant value = record.value(attr->fieldName().remove("\""));
        attr->setValue(value);
    }
}

bool ORM::refresh()
{
    QString query = (IS_STRING_VALUE(m_primaryKey) ?
                    QString("select * from %1 where %2 = \'%3\'") :
                    QString("select * from %1 where %2 = %3"))
                    .arg(m_tableName)
                    .arg(m_primaryKey->fieldName())
                    .arg(m_primaryKey->toString());

    QSqlQueryModel *ORM = new QSqlQueryModel();

    ORM->setQuery(query);

    if (ORM->rowCount() == 0)
    {
        delete ORM;
        return false;
    }

    fillORM(ORM->record(0));

    delete ORM;
    return true;
}

///
/// \brief ORM::lastInsertId - Only for QSQLITE
/// \return
///
int ORM::lastInsertId()
{
    int id = 0;
    QString query = QString( "select %1 from %2 order by %1 desc limit 1").arg(m_primaryKey->fieldName()).arg(m_tableName);
    QSqlQueryModel *ORM = new QSqlQueryModel ;
    ORM->setQuery(query, getDatabase());
    if( ORM->rowCount())
    {
        id = ORM->record(0).field(0).value().toInt();
    }
    delete ORM;
    return id;
}

bool ORM::do_insert()
{
    QString query;
    bool ret = false;
    for( int i = 0; i < 2; i++)
    {
        QString fields = "";
        QString values = "";
        int count = 0;

        query = "";

        foreach(ORMAttribute *attr, m_attrList)
        {
            if ((attr == m_primaryKey) && (attr->value().toInt() == 0))
                continue;

            if (attr->value().isNull())
                continue;

            if (count > 0)
            {
                fields += ",";
                values += ",";
            }

            fields += attr->fieldName();
            values += "?";

            count++;
        }

        if(getDatabase().driverName() == "QSQLITE")
            query = QString("insert into %1 (%2)values(%3)")
                    .arg(m_tableName)
                    .arg(fields)
                    .arg(values);
        else
            query = QString("insert into %1 (%2)values(%3) RETURNING %4 ")
                    .arg(m_tableName)
                    .arg(fields)
                    .arg(values)
                    .arg(m_primaryKey->fieldName());


        QSqlQuery *insert;

        insert = new QSqlQuery(getDatabase());

        insert->prepare(query);

        foreach(ORMAttribute *attr, m_attrList)
        {
            if ((attr == m_primaryKey) && (attr->value().toInt() == 0))
                continue;

            if (attr->value().isNull())
                continue;

            insert->addBindValue(attr->value());
        }

        ret = insert->exec();


        if (ret)
        {
            if( getDatabase().driverName() == "QSQLITE")
            {
                m_primaryKey->setValue(lastInsertId());
            }
            else
            {
                insert->next();
                m_primaryKey->setValue( insert->record().value( m_primaryKey->fieldName() ).toInt());
            }
            delete insert;

            break;
        }
        else
        {
            setLastError( insert->lastError() );

            TABLE_EXISTS()?EnsureFieldsExist():CreateTable();
        }
        delete insert;
    }
    return ret;
}

bool ORM::do_update()
{
    bool ret = false;

    if (NULL == m_primaryKey)
        return false;

    for( int i = 0; i < 2; i++)
    {
        QString query;
        QString fields = "";
        QString values = "";
        int count = 0;


        foreach(ORMAttribute *attr, m_attrList)
        {
            if (attr == m_primaryKey)
                continue;

            if (attr->value().isNull())
                continue;

            if (count > 0)
            {
                fields += ",";
                values += ",";
            }

            fields += attr->fieldName();
            values += "?";

            count++;
        }

        query = QString("update %1 set (%2)=(%3) where %4 = %5")
                .arg(m_tableName)
                .arg(fields)
                .arg(values)
                .arg(m_primaryKey->fieldName())
                .arg(ATTR_VALUE(m_primaryKey));

        QSqlQuery *update;

        update = new QSqlQuery(getDatabase());

        update->prepare(query);

        foreach(ORMAttribute *attr, m_attrList)
        {
            if (attr == m_primaryKey)
                continue;

            if (attr->value().isNull())
                continue;

            update->addBindValue(attr->value());
        }

        ret = update->exec();

        if(ret)
        {
            if( update->numRowsAffected() < 1)
                ret = false;

            delete update;
            break;
        }
        else
        {
            setLastError( update->lastError() );

            TABLE_EXISTS()?EnsureFieldsExist():CreateTable();
        }
        delete update;
    }
    return ret;
}

bool ORM::do_delete()
{
    if (NULL == m_primaryKey)
        return false;

    QString delQuery = QString ("delete from %1 where %2 = %3")
                       .arg(m_tableName)
                       .arg(m_primaryKey->fieldName())
                       .arg(ATTR_VALUE(m_primaryKey));

    QSqlQuery *query = new QSqlQuery(getDatabase());

    bool ret = query->exec(delQuery);
    
    m_lastError =query->lastError();

    delete query;

    return ret;
}

bool ORM::Save()
{
    return m_primaryKey->value().toInt()?Update() || Create():Create();
}


bool ORM::Create()
{
    return do_insert();
}

bool ORM::Update()
{
    return do_update();
}

bool ORM::Delete()
{
    return do_delete();
}
