#include "ku-parser-private.h"

#include "ku-null-statement-private.h"
#include "ku-type-private.h"
#include "ku-variable-private.h"
#include "ku-context.h"

#include <assert.h>

#define EXPECT_VARIABLE(x_name, x_type, x_mutable)                                                     \
    tmp = ku_string_new (x_name);                                                                      \
    sym = ku_context_get (p->current_ctx, tmp);                                                        \
    ku_string_free (tmp);                                                                              \
    assert (sym);                                                                                      \
    assert (!strcmp (x_name, ku_string_get_cstring (ku_symbol_get_name (sym))));                       \
    assert (sym->type == VARIABLE);                                                                    \
    var = (const KuVariable *) sym;                                                                    \
    if (x_type[0])                                                                                     \
    {                                                                                                  \
        assert (var->type);                                                                            \
        assert (!strcmp (x_type, ku_string_get_cstring (ku_symbol_get_name (KU_SYMBOL (var->type))))); \
    }                                                                                                  \
    else                                                                                               \
        assert (!var->type);                                                                           \
    assert (x_mutable == var->mutable);

#define EXPECT_BOOLEAN_LET_STATEMENT(x_name, x_value)             \
    assert (stmt == KU_NOOP_STATEMENT);                           \
    ls = KU_LET_STATEMENT (stmt);                                 \
    assert (ls->name);                                            \
    assert (!strcmp (ku_string_get_cstring (ls->name), x_name));  \
    ku_string_free (ls->name);                                    \
    assert (!ls->type);                                           \
    assert (ls->rvalue);                                          \
    assert (ls->rvalue->type == BOOL_STMT);                       \
    assert (!ls->rvalue->next);                                   \
    assert (KU_BOOLEAN_STATEMENT (ls->rvalue)->value == x_value); \
    free (ls->rvalue);

#define EXPECT_NULL_LET_STATEMENT(x_name, type_name)                      \
    assert (stmt == KU_NOOP_STATEMENT);                                   \
    ls = KU_LET_STATEMENT (stmt);                                         \
    assert (ls->name);                                                    \
    assert (!strcmp (ku_string_get_cstring (ls->name), x_name));          \
    ku_string_free (ls->name);                                            \
    assert (ls->type);                                                    \
    free (ls->type);                                                      \
    assert (ls->rvalue);                                                  \
    assert (ls->rvalue->type == NULL_STMT);                               \
    assert (!ls->rvalue->next);                                           \
    assert (!KU_NULL_STATEMENT (ls->rvalue)->value);                      \
    free (ls->rvalue)

static void
test_let_bool (void)
{
    KuParser *p = ku_parser_new (ku_stream_new_from_string (ku_string_new (
                    "let foo = TRUE;"
                    "let bar = FALSE;"
                )));
    KuStatement *stmt = ku_parser_parse (p);
    assert (stmt == KU_NOOP_STATEMENT);
    const KuSymbol *sym;
    const KuVariable *var;
    KuString *tmp;
    // TODO: type, value
    EXPECT_VARIABLE ("foo", "", false);
    EXPECT_VARIABLE ("bar", "", false);
    ku_parser_free (p);
}

static void
test_let_null (void)
{
#if 0
    KuParser *p = ku_parser_new (ku_stream_new_from_string (ku_string_new ("let f : *Foo = NULL;")));
    KuStatement *stmt = ku_parser_parse (p);
    KuLetStatement *ls;
    EXPECT_NULL_LET_STATEMENT ("f", "Foo");
    assert (!stmt->next);
    free (stmt);
    ku_parser_free (p);
#endif
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
