/**
 * cmdsqlite.cpp
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

#include "cmdsqlite.h"

QString CmdSqlite::CmdInt(QString name, bool bAutoIncrement, bool bPrimaryKey)
{
    QString field;

    field = QString::fromUtf8("%1 INTEGER ").arg(name);

    if( bPrimaryKey )
        field += QString::fromUtf8(" PRIMARY KEY ");

    if( bAutoIncrement )
        field += QString::fromUtf8(" AUTOINCREMENT ");


    return field;
}

QString CmdSqlite::CmdLong(QString name, bool bAutoIncrement, bool bPrimaryKey)
{
    return CmdInt(name,bAutoIncrement,bPrimaryKey);

}

QString CmdSqlite::CmdDouble(QString name, int precision, int decimals)
{
    Q_UNUSED(precision);
    Q_UNUSED(decimals);

    return QString::fromUtf8(" %1 REAL ").arg(name);
}

QString CmdSqlite::CmdDate(QString name)
{
    return CmdString(name,0);
}

QString CmdSqlite::CmdTime(QString name)
{
    return CmdString(name,0);
}

QString CmdSqlite::CmdBool(QString name)
{
    return CmdInt(name, false, false);
}

QString CmdSqlite::CmdString(QString name, int nSize)
{
    Q_UNUSED(nSize);

    return QString::fromUtf8(" %1 TEXT ").arg(name);
}
