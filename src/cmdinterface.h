/**
 * cmdinterface.cpp
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

#ifndef _Cmd_INTERFACE_
#define _Cmd_INTERFACE_

#include <QString>

#define ORM_LARGE_SIZE -1
class CmdInterface
{
public:
    virtual  ~CmdInterface() {;}
    virtual  QString CmdInt(QString name, bool bAutoIncrement=0, bool bPrimaryKey=0) = 0;
    virtual  QString CmdLong(QString name, bool bAutoIncrement=0, bool bPrimaryKey=0) = 0;
    virtual  QString CmdDouble(QString name, int precision=0, int decimals=0) = 0;
    virtual  QString CmdDate(QString name) = 0;
    virtual  QString CmdTime(QString name) = 0;
    virtual  QString CmdBool(QString name) = 0;
    virtual  QString CmdString(QString name, int nSize=ORM_LARGE_SIZE) = 0;
};
#endif
