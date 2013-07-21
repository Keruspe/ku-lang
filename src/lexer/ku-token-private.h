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

#ifndef __KU_TOKEN_PRIVATE_H__
#define __KU_TOKEN_PRIVATE_H__

#include "ku-token.h"

typedef enum
{
    KU_TOKEN_RESERVED_KEYWORD,
    KU_TOKEN_SEPARATOR,
    KU_TOKEN_LITERAL,
    KU_TOKEN_STRING
} KuTokenType;

struct _KuToken
{
    KuTokenType type;
    union {
        KuReservedKeyword reserved_keyword;
        KuSeparator       separator;
        KuString         *literal;
        KuString         *string;
    } value;
    bool type_check_ok;
};

#endif /*__KU_TOKEN_PRIVATE_H__*/
