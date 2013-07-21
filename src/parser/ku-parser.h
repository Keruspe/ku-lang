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

#ifndef __KU_PARSER_H__
#define __KU_PARSER_H__

#include "ku-lexer.h"
#include "ku-statement.h"

typedef struct _KuParser KuParser;

KuParser *ku_parser_new (KuStream *stream);

KuStatement *ku_parser_parse (KuParser *parser);

void ku_parser_free (KuParser *parser);

#endif /*__KU_PARSER_H__*/
