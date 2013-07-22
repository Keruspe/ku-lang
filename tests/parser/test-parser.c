#include "ku-parser.h"

#include "ku-boolean-statement-private.h"
#include "ku-null-statement-private.h"
#include "ku-let-statement-private.h"
#include "ku-type-private.h"

#include <assert.h>

#define EXPECT_BOOLEAN_LET_STATEMENT(x_name, x_value)            \
    assert (stmt->type == LET_STMT);                             \
    ls = KU_LET_STATEMENT (stmt);                                \
    assert (ls->name);                                           \
    assert (!strcmp (ku_string_get_cstring (ls->name), x_name)); \
    assert (!ls->type);                                          \
    assert (ls->rvalue);                                         \
    assert (ls->rvalue->type == BOOL_STMT);                      \
    assert (!ls->rvalue->next);                                  \
    assert (KU_BOOLEAN_STATEMENT (ls->rvalue)->value == x_value)

#define EXPECT_NULL_LET_STATEMENT(x_name, type_name)                      \
    assert (stmt->type == LET_STMT);                                      \
    ls = KU_LET_STATEMENT (stmt);                                         \
    assert (ls->name);                                                    \
    assert (!strcmp (ku_string_get_cstring (ls->name), x_name));          \
    assert (ls->type);                                                    \
    assert (!strcmp (ku_string_get_cstring (ls->type->name), type_name)); \
    assert (ls->type->mutable);                                           \
    assert (ls->rvalue);                                                  \
    assert (ls->rvalue->type == NULL_STMT);                               \
    assert (!ls->rvalue->next);                                           \
    assert (!KU_NULL_STATEMENT (ls->rvalue)->value);

static void
test_let_bool (void)
{
    KuParser *p = ku_parser_new (ku_stream_new_from_string (ku_string_new (
                    "let foo = TRUE;"
                    "let bar = FALSE;"
                )));
    KuStatement *stmt = ku_parser_parse (p);
    KuLetStatement *ls;
    EXPECT_BOOLEAN_LET_STATEMENT ("foo", true);
    assert (stmt->next);
    stmt = stmt->next;
    EXPECT_BOOLEAN_LET_STATEMENT ("bar", false);
    assert (!stmt->next);
    ku_parser_free (p);
    // TODO: check vars index
}

static void
test_let_null (void)
{
    KuParser *p = ku_parser_new (ku_stream_new_from_string (ku_string_new ("let f : *Foo = NULL;")));
    KuStatement *stmt = ku_parser_parse (p);
    KuLetStatement *ls;
    EXPECT_NULL_LET_STATEMENT ("f", "Foo");
    assert (!stmt->next);
    ku_parser_free (p);
    // TODO: check vars index
}

static void
test_real_world_one (void)
{
    KuParser *p = ku_parser_new (ku_stream_new_from_file (ku_file_new (SRC_DIR "/tests/data/test-one.ku", READ)));
    //ku_parser_parse (p);
    ku_parser_free (p);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[])
{
    test_let_bool ();
    test_let_null ();
    test_real_world_one ();
    return 0;
}
