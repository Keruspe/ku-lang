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

#ifndef __KU_SEPARATOR_H__
#define __KU_SEPARATOR_H__

#ifdef KU_COMPILATION
#include "config.h"
#endif

#include "ku-string.h"

typedef enum {
    SPACE,
    NEWLINE,
    TAB,
    COLON,
    SEMI_COLON,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_CURLY,
    RIGHT_CURLY,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    DOT,
    COMMA,
    MINUS,
    PLUS,
    DIVIDE,
    TIMES,
    STAR = TIMES,
    SQUOTE,
    DQUOTE,
    BQUOTE,
    EQUALS,
    ARROW,
    DEC,
    INC,
    OR,
    AND,
    NOT,
    /* The token is not a reserved keyword */
    S_NONE
} KuSeparator;

KuSeparator ku_token_cstring_to_separator (const char *token);

bool ku_token_cstring_may_be_unfinished_separator (const char *token);

bool ku_token_cstring_is_separator (const char *token);

bool ku_separator_is_delimitation (KuSeparator sep);

const KuString *ku_separator_to_string (KuSeparator sep);

#endif /*__KU_SEPARATOR_H__*/
