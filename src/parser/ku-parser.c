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

#include "ku-parser-private.h"

#include "ku-boolean-statement.h"
#include "ku-null-statement.h"
#include "ku-let-statement-private.h"

#include <assert.h>

static KuStatement *parse_statement (KuParser *parser);

KU_VISIBLE KuParser *
ku_parser_new (KuStream *stream)
{
    KuParser *parser = (KuParser *) malloc (sizeof (KuParser));
    parser->lexer = ku_lexer_new (stream);
    return parser;
}

static KuType *
parse_type (KuParser *parser)
{
    KuToken *token = ku_lexer_read_token_no_spaces (parser->lexer);
    bool mutable = false;
    if (ku_token_is_separator (token))
    {
        assert (ku_token_get_separator_value (token) == STAR);
        mutable = true;
        ku_token_free (token);
        token = ku_lexer_read_token_no_spaces (parser->lexer);
    }
    assert (ku_token_is_literal (token)); // FIXME: suport built-in types
    KuType *type = ku_type_new (ku_string_dup (ku_token_get_literal_value (token)), mutable);
    ku_token_free (token);
    return type;
}

static KuStatement *
parse_let_statement (KuParser *parser)
{
    KuLetStatement *stmt = ku_let_statement_new ();

    KuToken *token = ku_lexer_read_token_no_spaces (parser->lexer);
    assert (ku_token_is_literal (token));
    stmt->name = ku_string_dup (ku_token_get_literal_value (token));
    ku_token_free (token);

    token = ku_lexer_read_token_no_spaces (parser->lexer);
    assert (ku_token_is_separator (token)); // FIXME: args
    KuSeparator sep = ku_token_get_separator_value (token);
    if (sep == COLON) /* Type */
    {
        stmt->type = parse_type (parser);
        token = ku_lexer_read_token_no_spaces (parser->lexer);
        assert (ku_token_is_separator (token));
        sep = ku_token_get_separator_value (token);
    }
    assert (sep == EQUALS);
    ku_token_free (token);

    stmt->rvalue = parse_statement (parser);
    assert (stmt->rvalue);
    assert (stmt->rvalue->valuable); // FIXME: more asserts ?

    return KU_STATEMENT (stmt);
}

static KuStatement *
parse_statement (KuParser *parser)
{
    KuToken *t = ku_lexer_read_token_no_spaces (parser->lexer); // FIXME: free
    KuStatement *stmt;
    if (ku_token_is_end_of_file (t))
        return NULL;
    else if (ku_token_is_reserved_keyword (t))
    {
        switch (ku_token_get_reserved_keyword_value (t))
        {
        /* Values */
        case BTRUE:
            stmt = KU_STATEMENT (ku_boolean_statement_new (true));
            break;
        case BFALSE:
            stmt = KU_STATEMENT (ku_boolean_statement_new (false));
            break;
        case PNULL:
            stmt = KU_STATEMENT (ku_null_statement_new ());
            break;
        /* Builtins */
        case LET:
            return parse_let_statement (parser);
            break;
        default:
            assert (!"FIXME: other keyword");
        }
    }
    else
    {
        assert (!"FIXME: not a keyword");
    }

    t = ku_lexer_read_token_no_spaces (parser->lexer);
    assert (ku_token_is_separator (t));
    assert (ku_token_get_separator_value (t) == SEMI_COLON);
    ku_token_free (t);

    return stmt;
}

static KuStatement *
parse_statements (KuParser *parser)
{
    KuStatement *first = NULL, *prev = NULL, *stmt;
    while ((stmt = parse_statement (parser)))
    {
        if (!first)
            prev = first = stmt;
        else
        {
            prev->next = stmt;
            prev = stmt;
        }
    }
    return first;
}

KU_VISIBLE KuStatement *
ku_parser_parse (KuParser *parser)
{
    if (!parser)
        return NULL;

    return parse_statements (parser);
}

KU_VISIBLE void
ku_parser_free (KuParser *parser)
{
    if (parser)
    {
        ku_lexer_free (parser->lexer);
        free (parser);
    }
}
