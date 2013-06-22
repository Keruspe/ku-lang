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

#ifndef __KU_RESERVED_KEYWORDS_H__
#define __KU_RESERVED_KEYWORDS_H__

#ifdef KU_COMPILATION
#include "config.h"
#endif

#include <stdbool.h>

typedef enum {
    /* Types */
    CHAR,
    INT,
    LONG,
    UNSIGNED,
    FLOAT,
    DOUBLE,
    /* Branches */
    IF,
    ELSE,
    ELIF,
    /* Loops */
    DO,
    WHILE,
    FOR,
    /* The token is not a reserved keyword */
    NONE
} KuReservedKeyword;

KuReservedKeyword ku_token_cstring_to_reserved_keyword (const char *token);
bool              ku_token_cstring_is_reserved_keyword (const char *token);

#endif /*__KU_RESERVED_KEYWORDS_H__*/
