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

#include "ku-separator.h"

#include <string.h>

static const char *tokens[S_NONE] = {
    [SPACE] =         " ",
    [NEWLINE] =       "\n",
    [TAB] =           "\t",
    [COLON] =         ":",
    [SEMI_COLON] =    ";",
    [LEFT_PAREN] =    "(",
    [RIGHT_PAREN] =   ")",
    [LEFT_CURLY] =    "{",
    [RIGHT_CURLY] =   "}",
    [LEFT_BRACKET] =  "[",
    [RIGHT_BRACKET] = "]",
    [DOT] =           ".",
    [COMMA] =         ",",
    [MINUS] =         "-",
    [PLUS] =          "+",
    [TIMES] =         "*",
    [DIVIDE] =        "/",
    [SQUOTE] =        "'",
    [DQUOTE] =        "\"",
    [BQUOTE] =        "`"
};

KU_VISIBLE KuSeparator
ku_token_cstring_to_separator (const char *token)
{
    if (token)
    {
        for (KuSeparator s = SPACE; s < S_NONE; ++s)
        {
            if (!strcmp (token, tokens[s]))
                return s;
        }
    }

    return S_NONE;
}

KU_VISIBLE bool
ku_token_cstring_is_separator (const char *token)
{
    return (ku_token_cstring_to_separator (token) != S_NONE);
}
