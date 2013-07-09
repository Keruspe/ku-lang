#include "ku-lexer.h"

#include <assert.h>

#define EXPECT_SEPARATOR(s)                             \
    token = ku_lexer_read_token (l);                    \
    assert (ku_token_is_separator (token));             \
    assert (ku_token_get_separator_value (token) == s); \
    ku_token_free (token);

#define EXPECT_KEYWORD(k)                                      \
    token = ku_lexer_read_token (l);                           \
    assert (ku_token_is_reserved_keyword (token));             \
    assert (ku_token_get_reserved_keyword_value (token) == k); \
    ku_token_free (token);                                     \
    EXPECT_SEPARATOR (SPACE);

static void
test_token_reserved_keywords (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_cstring ("char int long unsigned float double bool NULL TRUE FALSE if else elif return do while for "));
    KuToken *token;
    EXPECT_KEYWORD (CHAR);
    EXPECT_KEYWORD (INT);
    EXPECT_KEYWORD (LONG);
    EXPECT_KEYWORD (UNSIGNED);
    EXPECT_KEYWORD (FLOAT);
    EXPECT_KEYWORD (DOUBLE);
    EXPECT_KEYWORD (BOOL);
    EXPECT_KEYWORD (PNULL);
    EXPECT_KEYWORD (BTRUE);
    EXPECT_KEYWORD (BFALSE);
    EXPECT_KEYWORD (IF);
    EXPECT_KEYWORD (ELSE);
    EXPECT_KEYWORD (ELIF);
    EXPECT_KEYWORD (RETURN);
    EXPECT_KEYWORD (DO);
    EXPECT_KEYWORD (WHILE);
    EXPECT_KEYWORD (FOR);
    ku_lexer_free (l);
}

static void
test_token_separators (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_cstring (" \n\t:;(){}[].,-+/*'\"`=->"));
    KuToken *token;
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (NEWLINE);
    EXPECT_SEPARATOR (TAB);
    EXPECT_SEPARATOR (COLON);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (LEFT_PAREN);
    EXPECT_SEPARATOR (RIGHT_PAREN);
    EXPECT_SEPARATOR (LEFT_CURLY);
    EXPECT_SEPARATOR (RIGHT_CURLY);
    EXPECT_SEPARATOR (LEFT_BRACKET);
    EXPECT_SEPARATOR (RIGHT_BRACKET);
    EXPECT_SEPARATOR (DOT);
    EXPECT_SEPARATOR (COMMA);
    EXPECT_SEPARATOR (MINUS);
    EXPECT_SEPARATOR (PLUS);
    EXPECT_SEPARATOR (DIVIDE);
    EXPECT_SEPARATOR (TIMES);
    EXPECT_SEPARATOR (SQUOTE);
    EXPECT_SEPARATOR (DQUOTE);
    EXPECT_SEPARATOR (BQUOTE);
    EXPECT_SEPARATOR (EQUALS);
    EXPECT_SEPARATOR (ARROW);
    ku_lexer_free (l);
}

static void
test_real_world_one (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_file (ku_file_new ("tests/data/test-one.ku", READ)));
    KuToken *token;

    EXPECT_KEYWORD   (BOOL);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_STRING    ("test");
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (EQUALS);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_KEYWORD   (BTRUE);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_STRING    ("Foo");
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (STAR);
    EXPECT_STRING    ("f");
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (EQUALS);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_KEYWORD   (PNULL);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_KEYWORD   (IF);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (LEFT_PAREN);
    EXPECT_STRING    ("test");
    EXPECT_SEPARATOR (RIGHT_PAREN);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_STRING    ("f");
    EXPECT_SEPARATOR (ARROW);
    EXPECT_STRING    ("bar");
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_KEYWORD   (ELIF);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (LEFT_PAREN);
    EXPECT_STRING    ("f");
    EXPECT_SEPARATOR (ARROW);
    EXPECT_STRING    ("baz");
    EXPECT_SEPARATOR (RIGHT_PAREN);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_STRING    ("f");
    EXPECT_SEPARATOR (PLUS);
    EXPECT_SEPARATOR (PLUS);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_KEYWORD   (ELSE);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_SEPARATOR (LEFT_CURLY);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_STRING    ("f");
    EXPECT_SEPARATOR (MINUS);
    EXPECT_SEPARATOR (MINUS);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_SEPARATOR (RIGHT_CURLY);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_KEYWORD   (RETURN);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_INT       (0);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    ku_lexer_free (l);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[])
{
    test_token_reserved_keywords ();
    test_token_separators ();
    test_real_world_one ();
    return 0;
}
