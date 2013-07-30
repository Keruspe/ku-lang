/*
 *      This file is part of ku.
 *
 *      Copyright 2013 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 *
 *      ku is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      ku is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with ku.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ku-type-private.h"

KU_VISIBLE KuType *
ku_type_new (KuString *name,
             bool      mutable)
{
    KuType *type = (KuType *) malloc (sizeof (KuType));
    type->name = name;
    type->mutable = mutable;
    return type;
}

KU_VISIBLE const char *
ku_type_get_name (KuType *type)
{
    return (type) ? type->name : NULL;
}
