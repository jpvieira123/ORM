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

#include "cmdinterface.h"


class CmdSqlite : CmdInterface
{
public:
     QString CmdInt(QString name, bool bAutoIncrement=0, bool bPrimaryKey=0);
     QString CmdLong(QString name, bool bAutoIncrement=0, bool bPrimaryKey=0);
     QString CmdDouble(QString name, int precision=0, int decimals=0);
     QString CmdDate(QString name);
     QString CmdTime(QString name);
     QString CmdBool(QString name);
     QString CmdString(QString name, int nSize=ORM_LARGE_SIZE);
};
