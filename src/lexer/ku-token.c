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

#include "ku-token-private.h"

#include <assert.h>

static KuToken *
_ku_token_new (KuTokenType type)
{
    KuToken *token = (KuToken *) malloc (sizeof (KuToken));
    token->type = type;
    token->type_check_ok = false;
    return token;
}

KU_VISIBLE KuToken *
ku_token_new_end_of_file (void)
{
    KuToken *token = _ku_token_new (KU_TOKEN_END_OF_FILE);
    return token;
}

KU_VISIBLE KuToken *
ku_token_new_reserved_keyword (KuReservedKeyword keyword)
{
    KuToken *token = _ku_token_new (KU_TOKEN_RESERVED_KEYWORD);
    token->value.reserved_keyword = keyword;
    return token;
}

KU_VISIBLE KuToken *
ku_token_new_separator (KuSeparator separator)
{
    KuToken *token = _ku_token_new (KU_TOKEN_SEPARATOR);
    token->value.separator = separator;
    return token;
}

KU_VISIBLE KuToken *
ku_token_new_literal (KuString *string)
{
    KuToken *token = _ku_token_new (KU_TOKEN_LITERAL);
    token->value.literal = string;
    return token;
}

KU_VISIBLE KuToken *
ku_token_new_string (KuString *string)
{
    KuToken *token = _ku_token_new (KU_TOKEN_STRING);
    token->value.string = string;
    return token;
}

KU_VISIBLE bool
ku_token_is_end_of_file (KuToken *token)
{
    if (!token || token->type != KU_TOKEN_END_OF_FILE)
        return false;
    token->type_check_ok = true;
    return true;
}

KU_VISIBLE bool
ku_token_is_reserved_keyword (KuToken *token)
{
    if (!token || token->type != KU_TOKEN_RESERVED_KEYWORD)
        return false;
    token->type_check_ok = true;
    return true;
}

KU_VISIBLE bool
ku_token_is_separator (KuToken *token)
{
    if (!token || token->type != KU_TOKEN_SEPARATOR)
        return false;
    token->type_check_ok = true;
    return true;
}

KU_VISIBLE bool
ku_token_is_literal (KuToken *token)
{
    if (!token || token->type != KU_TOKEN_LITERAL)
        return false;
    token->type_check_ok = true;
    return true;
}

KU_VISIBLE bool
ku_token_is_string (KuToken *token)
{
    if (!token || token->type != KU_TOKEN_STRING)
        return false;
    token->type_check_ok = true;
    return true;
}

KU_VISIBLE KuReservedKeyword
ku_token_get_reserved_keyword_value (const KuToken *token)
{
    assert (token && token->type_check_ok);
    return token->value.reserved_keyword;
}

KU_VISIBLE KuSeparator
ku_token_get_separator_value (const KuToken *token)
{
    assert (token && token->type_check_ok);
    return token->value.separator;
}

KU_VISIBLE const KuString *
ku_token_get_literal_value (const KuToken *token)
{
    assert (token && token->type_check_ok);
    return token->value.literal;
}

KU_VISIBLE const KuString *
ku_token_get_string_value (const KuToken *token)
{
    assert (token && token->type_check_ok);
    return token->value.string;
}

KU_VISIBLE void
ku_token_free (KuToken *token)
{
    if (token)
    {
        if (ku_token_is_string (token))
            ku_string_free (token->value.string);
        if (ku_token_is_literal (token))
            ku_string_free (token->value.literal);
        free (token);
    }
}
