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
#include "ku-string.h"

#include <string.h>

static KuString *tokens[S_NONE];

static __attribute__((constructor)) void
tokens_setup (void)
{
    tokens[SPACE] =         ku_string_new (" ");
    tokens[NEWLINE] =       ku_string_new ("\n");
    tokens[TAB] =           ku_string_new ("\t");
    tokens[COLON] =         ku_string_new (":");
    tokens[SEMI_COLON] =    ku_string_new (";");
    tokens[LEFT_PAREN] =    ku_string_new ("(");
    tokens[RIGHT_PAREN] =   ku_string_new (")");
    tokens[LEFT_CURLY] =    ku_string_new ("{");
    tokens[RIGHT_CURLY] =   ku_string_new ("}");
    tokens[LEFT_BRACKET] =  ku_string_new ("[");
    tokens[RIGHT_BRACKET] = ku_string_new ("]");
    tokens[DOT] =           ku_string_new (".");
    tokens[COMMA] =         ku_string_new (",");
    tokens[MINUS] =         ku_string_new ("-");
    tokens[PLUS] =          ku_string_new ("+");
    tokens[DIVIDE] =        ku_string_new ("/");
    tokens[TIMES] =         ku_string_new ("*");
    tokens[SQUOTE] =        ku_string_new ("'");
    tokens[DQUOTE] =        ku_string_new ("\"");
    tokens[BQUOTE] =        ku_string_new ("`");
    tokens[EQUALS] =        ku_string_new ("=");
    tokens[ARROW] =         ku_string_new ("->");
    tokens[DEC] =           ku_string_new ("--");
    tokens[INC] =           ku_string_new ("++");
    tokens[OR] =            ku_string_new ("||");
    tokens[AND] =           ku_string_new ("&&");
    tokens[NOT] =           ku_string_new ("!");
}

static __attribute__((destructor)) void
tokens_cleanup (void)
{
    for (KuSeparator s = SPACE; s < S_NONE; ++s)
        ku_string_free (tokens[s]);
}

KU_VISIBLE KuSeparator
ku_token_cstring_to_separator (const char *token)
{
    if (token)
    {
        for (KuSeparator s = SPACE; s < S_NONE; ++s)
        {
            if (!strcmp (token, ku_string_get_cstring (tokens[s])))
                return s;
        }
    }

    return S_NONE;
}

KU_VISIBLE bool
ku_token_cstring_may_be_unfinished_separator (const char *token)
{
    if (token)
    {
        size_t len = strlen (token);

        if (len)
        {
            for (KuSeparator s = SPACE; s < S_NONE; ++s)
            {
                if (len < ku_string_get_length (tokens[s]) &&
                    !memcmp (token, ku_string_get_cstring (tokens[s]), len))
                        return true;
            }
        }
    }

    return false;
}

KU_VISIBLE bool
ku_token_cstring_is_separator (const char *token)
{
    return (ku_token_cstring_to_separator (token) != S_NONE);
}
