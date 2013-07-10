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

#include "ku-lexer-private.h"

#include <assert.h>
#include <stdio.h>

KU_VISIBLE KuLexer *
ku_lexer_new (KuStream *stream)
{
    KuLexer *lexer = (KuLexer *) malloc (sizeof (KuLexer));
    lexer->stream = stream;
    lexer->buffer[0] = '\0';
    lexer->index = 0;
    lexer->backup = '\0';
    return lexer;
}

KU_VISIBLE KuToken *
ku_lexer_read_token (KuLexer *lexer)
{
    if (!lexer)
        return NULL;

    bool buf_eq_sep;
    char sep[3] = "";

    if (lexer->backup)
    {
        if (lexer->buffer[0])
            sep[0] = lexer->backup;
        else
            lexer->buffer[0] = lexer->backup;
        buf_eq_sep = false;
        lexer->backup = '\0';
    }
    else if (!ku_token_cstring_is_separator (lexer->buffer) ||
             ku_token_cstring_may_be_unfinished_separator (lexer->buffer))
    {
        do {
            assert (lexer->index <= 254);
            sep[0] = ku_stream_read_char (lexer->stream);
            if (sep[0] == '\0')
                break;
            lexer->buffer[lexer->index++] = sep[0];

            sep[1] = '\0';
            if (ku_token_cstring_may_be_unfinished_separator (sep))
            {
                sep[1] = ku_stream_read_char (lexer->stream);
                if (!sep[1])
                    break;
                else if (ku_token_cstring_is_separator (sep))
                {
                    assert (lexer->index <= 254);
                    lexer->buffer[lexer->index++] = sep[1];
                    break;
                }
                else
                {
                    lexer->backup = sep[1];
                    sep[1] = '\0';
                    break;
                }
            }
            if (ku_token_cstring_is_separator (lexer->buffer))
            {
                buf_eq_sep = true;
                break;
            }
        } while (!ku_token_cstring_is_separator (sep));

        size_t sep_len = strlen (sep);
        buf_eq_sep = !memcmp (lexer->buffer, sep, sep_len);
        if (buf_eq_sep)
            lexer->buffer[lexer->index] = '\0';
        else
            lexer->buffer[lexer->index - strlen (sep)] = '\0';
    }
    else
        buf_eq_sep = true;

    KuToken *token;
    if (buf_eq_sep)
    {
        if (ku_token_cstring_is_separator (lexer->buffer))
            token = ku_token_new_separator (ku_token_cstring_to_separator (lexer->buffer));
        else
            token = ku_token_new_string (ku_string_new (lexer->buffer));
        lexer->buffer[0] = '\0';
    }
    else if (ku_token_cstring_is_reserved_keyword (lexer->buffer))
    {
        token = ku_token_new_reserved_keyword (ku_token_cstring_to_reserved_keyword (lexer->buffer));
        strcpy (lexer->buffer, sep);
    }
    else if (ku_token_cstring_is_separator (lexer->buffer))
    {
        token = ku_token_new_separator (ku_token_cstring_to_separator (lexer->buffer));
        strcpy (lexer->buffer, sep);
    }
    else
    {
        token = ku_token_new_string (ku_string_new (lexer->buffer));
        strcpy (lexer->buffer, sep);
    }

    lexer->index = strlen (lexer->buffer);
    return token;
}

KU_VISIBLE void
ku_lexer_free (KuLexer *lexer)
{
    if (lexer)
    {
        ku_stream_free (lexer->stream);
        free (lexer);
    }
}
