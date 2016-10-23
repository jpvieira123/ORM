/**
 * easter.cpp
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

#ifndef EASTER_H
#define EASTER_H

#include "orm.h"

DECLARE_ORM(Easter)

DECLARE_CLASS(Easter)
    ORM_DECLARE_ATTRIBUTE(Easter, int, Id)
    ORM_DECLARE_ATTRIBUTE(Easter, int, Year)
    ORM_DECLARE_ATTRIBUTE(Easter, QDate, Date)
    ORM_DECLARE_ATTRIBUTE(Easter, QDate, Carnival)
    ORM_DECLARE_ATTRIBUTE(Easter, QDate, CorpusChrist)

    ORM_MATCH_TABLE(Easter, "easter")

ORM_END_MAP()

#endif // EASTER_H
