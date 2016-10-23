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

#include "easter.h"

ORM_BEGIN_MAP(Easter)
    ORM_MAP_PRIMARYKEY(Id, "id");
    ORM_MAP_FIELD(Year, "year");
    ORM_MAP_FIELD(Date, "date");
    ORM_MAP_FIELD(Carnival, "carnival");
    ORM_MAP_FIELD(CorpusChrist, "corpuschrist");
ORM_END_MAP()

