/**
 * fieldfactory.cpp
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

#include "fieldfactory.h"
#include <QSqlDriver>
#include "cmdmysql.h"
#include "cmdsqlite.h"
#include "cmdpostgres.h"

CmdInterface *FieldFactory::Create(int dbmstype)
{
    switch( dbmstype )
    {
       case QSqlDriver::SQLite:      {return (CmdInterface*)new CmdSqlite;}
       case QSqlDriver::MySqlServer: {return (CmdInterface*)new CmdMysql;}
       case QSqlDriver::PostgreSQL:
       default:                      {return (CmdInterface*)new CmdPostgres;}


    }

    return (CmdInterface*)new CmdPostgres;
}
