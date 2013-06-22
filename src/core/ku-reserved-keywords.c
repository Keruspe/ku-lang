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

#include "ku-reserved-keywords.h"

#include <string.h>

static const char *tokens[NONE] = {
    /* Types */
    [CHAR]     = "char",
    [INT]      = "int",
    [LONG]     = "long",
    [UNSIGNED] = "unsigned",
    [FLOAT]    = "float",
    [DOUBLE]   = "double",
    /* Branches */
    [IF]       = "if",
    [ELSE]     = "else",
    [ELIF]     = "elif",
    /* Loops */
    [DO]       = "do",
    [WHILE]    = "while",
    [FOR]      = "for"
};

KU_VISIBLE KuReservedKeyword
ku_token_cstring_to_reserved_keyword (const char *token)
{
    if (token)
    {
        for (KuReservedKeyword k = CHAR; k < NONE; ++k)
        {
            if (!strcmp (token, tokens[k]))
                return k;
        }
    }

    return NONE;
}

KU_VISIBLE bool
ku_token_cstring_is_reserved_keyword (const char *token)
{
    return (ku_token_cstring_to_reserved_keyword (token) != NONE);
}
