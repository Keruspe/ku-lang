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

#include "ku-let-statement-private.h"

KU_VISIBLE KuLetStatement *
ku_let_statement_new (void)
{
    KuLetStatement *stmt = (KuLetStatement *) malloc (sizeof (KuLetStatement));
    ku_statement_init (KU_STATEMENT (stmt), LET_STMT);
    stmt->name = NULL;
    stmt->rvalue = NULL;
    return stmt;
}
