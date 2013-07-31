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

#include "ku-statement-private.h"
#include "ku-variable-private.h"

#include <assert.h>

static KuStatement *parse_statement (KuParser *parser);

KU_VISIBLE KuParser *
ku_parser_new (KuStream *stream)
{
    KuParser *parser = (KuParser *) malloc (sizeof (KuParser));
    parser->lexer = ku_lexer_new (stream);
    parser->current_ctx = ku_context_new (NULL);
    return parser;
}

static bool
parse_rvalue (KuParser   *parser,
              KuVariable *var)
{
    KuToken *t = ku_lexer_read_token_no_spaces (parser->lexer); // FIXME: free
    if (ku_token_is_reserved_keyword (t))
    {
        switch (ku_token_get_reserved_keyword_value (t))
        {
            case BFALSE:
                // TODO: assert type is bool
                var->value.boolean = false;
                return true;;
            case BTRUE:
                // TODO: assert type is bool
                var->value.boolean = true;
                return true;;
            case PNULL:
                // TODO: assert type is mutable
                var->value.null_pointer = NULL;
                return true;;
            default:
                assert (!"other rval");
        }
    }
    return false;
}

static KuStatement *
parse_let_statement (KuParser *parser)
{
    KuToken *token = ku_lexer_read_token_no_spaces (parser->lexer);
    assert (ku_token_is_literal (token));
    KuString *name = ku_string_dup (ku_token_get_literal_value (token));
    ku_token_free (token);

    token = ku_lexer_read_token_no_spaces (parser->lexer);
    assert (ku_token_is_separator (token)); // FIXME: args
    KuSeparator sep = ku_token_get_separator_value (token);
    bool mutable = false;
    KuType *type = NULL;
    if (sep == COLON) /* Type */
    {
        ku_token_free (token);
        token = ku_lexer_read_token_no_spaces (parser->lexer);
        if (ku_token_is_separator (token))
        {
            assert (ku_token_get_separator_value (token) == STAR);
            mutable = true;
            ku_token_free (token);
            token = ku_lexer_read_token_no_spaces (parser->lexer);
        }
        assert (ku_token_is_literal (token)); // FIXME: suport built-in types
        type = ku_type_new (ku_string_dup (ku_token_get_literal_value (token)));
        ku_token_free (token);
        token = ku_lexer_read_token_no_spaces (parser->lexer);
        assert (ku_token_is_separator (token));
        sep = ku_token_get_separator_value (token);
    }
    assert (sep == EQUALS);
    ku_token_free (token);

    KuVariable *var = ku_variable_new (type, name, mutable);

    assert (parse_rvalue (parser, var));
    ku_context_register_variable (parser->current_ctx, var);

    token = ku_lexer_read_token_no_spaces (parser->lexer);
    assert (ku_token_is_separator (token) && ku_token_get_separator_value (token) == SEMI_COLON);
    ku_token_free (token);

    return KU_NOOP_STATEMENT;
}

static KuStatement *
parse_statement (KuParser *parser)
{
    KuToken *t = ku_lexer_read_token_no_spaces (parser->lexer); // FIXME: free
    KuStatement *stmt;
    if (ku_token_is_end_of_file (t))
    {
        ku_token_free (t);
        return NULL;
    }
    else if (ku_token_is_reserved_keyword (t))
    {
        switch (ku_token_get_reserved_keyword_value (t))
        {
        case LET:
            ku_token_free (t);
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

    ku_token_free (t);
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
        if (stmt == KU_NOOP_STATEMENT)
            continue;
        if (!first)
            prev = first = stmt;
        else
        {
            prev->next = stmt;
            prev = stmt;
        }
    }
    return (first) ? first : KU_NOOP_STATEMENT;
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
