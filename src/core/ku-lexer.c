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

static void
append (KuLexer *lexer,
        char     c)
{
    assert (++lexer->index <= 254 + !c);
    lexer->buffer[lexer->index] = c;
}

KU_VISIBLE KuLexer *
ku_lexer_new (KuStream *stream)
{
    KuLexer *lexer = (KuLexer *) malloc (sizeof (KuLexer));
    lexer->stream = stream;
    lexer->buffer[0] = '\0';
    lexer->index = 0;
    lexer->backup = '\0';
    lexer->delim = S_NONE;
    return lexer;
}

KU_VISIBLE KuToken *
ku_lexer_read_token (KuLexer *lexer)
{
    if (!lexer)
        return NULL;

    bool buf_eq_sep;
    char sep[3] = "";
    lexer->index = -1;

continue_str:
    if (lexer->backup)
    {
        if (lexer->buffer[0])
        {
            sep[0] = lexer->backup;
            append (lexer, '\0'); /* simulate index incrementation from \0 appending which we decrease at continue_str */
        }
        else
            lexer->buffer[0] = lexer->backup;
        buf_eq_sep = false;
        lexer->backup = '\0';
    }
    else if (!ku_token_cstring_is_separator (lexer->buffer) ||
              ku_token_cstring_may_be_unfinished_separator (lexer->buffer))
    {
        do {
            bool escaped = false;
            char read = ku_stream_read_char (lexer->stream);
            if (!read)
            {
                size_t len = strlen (sep);
                for (unsigned int i = 0; i < len; ++i)
                    append (lexer, sep[i]);
                break;
            }
            if (read == '\\')
            {
                read = ku_stream_read_char (lexer->stream);
                escaped = true;
            }
            else
                sep[0] = read;
            append (lexer, read);

            sep[1] = '\0';
            if (ku_token_cstring_may_be_unfinished_separator (sep))
            {
                // TODO: handle backslash here. Syntax error ?
                sep[1] = ku_stream_read_char (lexer->stream);
                if (sep[1])
                {
                    if (ku_token_cstring_is_separator (sep))
                        append (lexer, sep[1]);
                    else
                    {
                        lexer->backup = sep[1];
                        sep[1] = '\0';
                    }
                }
                break;
            }
            if (!escaped && ku_token_cstring_is_separator (lexer->buffer))
                break;
        } while (!ku_token_cstring_is_separator (sep));

        size_t sep_len = strlen (sep);
        buf_eq_sep = sep_len == (lexer->index + 1) && !memcmp (lexer->buffer, sep, sep_len);
        if (!buf_eq_sep)
            lexer->index -= strlen (sep);
        append (lexer, '\0');
    }
    else
        buf_eq_sep = true;

    KuToken *token = NULL;
    KuSeparator _sep = S_NONE;
    if (buf_eq_sep)
    {
        assert (ku_token_cstring_is_separator (lexer->buffer));

        _sep = ku_token_cstring_to_separator (lexer->buffer);
        lexer->buffer[0] = '\0';
    }
    else if (ku_token_cstring_is_separator (lexer->buffer))
    {
        _sep = ku_token_cstring_to_separator (lexer->buffer);
        strcpy (lexer->buffer, sep);
    }
    else if (ku_token_cstring_is_reserved_keyword (lexer->buffer))
    {
        token = ku_token_new_reserved_keyword (ku_token_cstring_to_reserved_keyword (lexer->buffer));
        strcpy (lexer->buffer, sep);
    }
    else if (lexer->delim == S_NONE)
    {
        assert (strlen (lexer->buffer));
        token = ku_token_new_string (ku_string_new (lexer->buffer));
        strcpy (lexer->buffer, sep);
    }

    if (!token)
    {
        if (ku_separator_is_delimitation (_sep) && lexer->delim == S_NONE)
        {
            lexer->delim = _sep;
            token = ku_token_new_separator (_sep);
        }
        else if (lexer->delim == _sep)
        {
            token = ku_token_new_separator (_sep);
            lexer->delim = S_NONE;
        }
        else if (lexer->delim != S_NONE && lexer->delim == ku_token_cstring_to_separator (sep))
        {
            token = ku_token_new_string (ku_string_new (lexer->buffer));
            strcpy (lexer->buffer, sep);
            lexer->delim = S_NONE;
        }
        else
        {
            const KuString *sep_str = ku_separator_to_string (_sep);
            const char *sep_cstr = (_sep == S_NONE) ? sep : ku_string_get_cstring (sep_str);
            size_t len = (_sep == S_NONE) ? strlen (sep) : ku_string_get_length (sep_str);
            if (lexer->delim == S_NONE)
            {
                assert (_sep != S_NONE);
                token = ku_token_new_separator (_sep);
                lexer->buffer[0] = '\0';
            }
            else
            {
                --lexer->index; // erase the \0
                for (unsigned int i = 0; i < len; ++i)
                    append (lexer, sep_cstr[i]); /* TODO: optimize */
                goto continue_str;
            }
        }
    }

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
