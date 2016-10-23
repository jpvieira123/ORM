/**
 * cmdpostgres.cpp
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

#include "cmdpostgres.h"



QString CmdPostgres::CmdInt(QString name, bool bAutoIncrement, bool bPrimaryKey)
{
    QString field;

    if( bAutoIncrement )
        field = QString::fromUtf8("%1 serial NOT NULL ").arg(name);
    else
        field = QString::fromUtf8(" %1 integer ").arg(name);

    if( bPrimaryKey )
        field += QString::fromUtf8(" PRIMARY KEY ");

    return field;
}

QString CmdPostgres::CmdLong(QString name, bool bAutoIncrement, bool bPrimaryKey)
{
    QString field;

    if( bAutoIncrement )
        field = QString::fromUtf8("%1 bigserial NOT NULL ").arg(name);
    else
        field = QString::fromUtf8(" %1 bigint ").arg(name);

    if( bPrimaryKey )
        field += QString::fromUtf8(" PRIMARY KEY ");

    return field;

}

QString CmdPostgres::CmdDouble(QString name, int precision, int decimals)
{
    QString field = QString::fromUtf8(" %1 numeric(").arg(name);

    if( precision )
        field += QString::fromUtf8("%1").arg( precision);

    if( decimals )
        field += QString::fromUtf8(",%1").arg(decimals);

    field += ") ";

    return field;

}

QString CmdPostgres::CmdDate(QString name)
{
    return QString::fromUtf8(" %1 date ").arg(name);

}

QString CmdPostgres::CmdTime(QString name)
{

    return QString::fromUtf8(" %1 time without time zone ").arg(name);
}

QString CmdPostgres::CmdBool(QString name)
{
    return QString::fromUtf8(" %1 boolean ").arg(name);

}

QString CmdPostgres::CmdString(QString name, int nSize)
{
    QString field = QString::fromUtf8(" %1 character varying ").arg(name);
    if( nSize > ORM_LARGE_SIZE)
        field += QString::fromUtf8("(%1)").arg(nSize);

    return field;

}
