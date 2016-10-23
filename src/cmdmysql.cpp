/**
 * cmdmysql.cpp
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

#include "cmdmysql.h"


QString CmdMysql::CmdInt(QString name, bool bAutoIncrement, bool bPrimaryKey)
{
    QString field;

    field = QString::fromUtf8(" %1 integer ").arg(name);
    if( bAutoIncrement )
        field += QString::fromUtf8(" AUTO_INCREMENT ");

    if( bPrimaryKey )
        field += QString::fromUtf8(" PRIMARY KEY ");

    return field;
}

QString CmdMysql::CmdLong(QString name, bool bAutoIncrement, bool bPrimaryKey)
{
    QString field;

    field = QString::fromUtf8(" %1 bigint ").arg(name);

    if( bAutoIncrement )
        field += QString::fromUtf8(" AUTO_INCREMENT ");

    if( bPrimaryKey )
        field += QString::fromUtf8(" PRIMARY KEY ");

    return field;

}

QString CmdMysql::CmdDouble(QString name, int precision, int decimals)
{
    return QString::fromUtf8(" %1 numeric(%2,%3)").arg(name).arg(precision).arg(decimals);
}

QString CmdMysql::CmdDate(QString name)
{
    return QString::fromUtf8(" %1 DATE ").arg(name);

}

QString CmdMysql::CmdTime(QString name)
{

    return QString::fromUtf8(" %1 TIME ").arg(name);
}

QString CmdMysql::CmdBool(QString name)
{
    return QString::fromUtf8(" %1 boolean ").arg(name);

}

QString CmdMysql::CmdString(QString name, int nSize)
{
    QString field;

    if( nSize == ORM_LARGE_SIZE)
        field = QString::fromUtf8(" %1 TEXT ").arg(name);
    else
        field = QString::fromUtf8(" %1 character varying(%2) ").arg(name).arg(nSize);

    return field;
}
