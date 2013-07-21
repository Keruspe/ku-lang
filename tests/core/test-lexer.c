#include "ku-lexer.h"

#include <assert.h>

#define EQUALS(a, b) a == b
#define STREQ(s1, s2) !strcmp(ku_string_get_cstring (s1), s2)

#define EXPECT_FULL(type, value, cmp)                          \
    token = ku_lexer_read_token (l);                           \
    assert (ku_token_is_##type (token));                       \
    assert (cmp (ku_token_get_##type##_value (token), value)); \
    ku_token_free (token)

#define EXPECT(type, value) \
    EXPECT_FULL (type, value, EQUALS)

#define EXPECT_SEPARATOR(s) EXPECT (separator, s)

#define EXPECT_KEYWORD(k)   EXPECT (reserved_keyword, k)

#define EXPECT_STRING(s)    EXPECT_FULL (string, s, STREQ)

#define EXPECT_KEYWORD_AND_SPACE(k) \
    EXPECT_KEYWORD (k);             \
    EXPECT_SEPARATOR (SPACE)

static void
test_token_reserved_keywords (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_cstring ("char int long unsigned float double bool NULL TRUE FALSE if else elif let break return do while for"));
    KuToken *token;
    EXPECT_KEYWORD_AND_SPACE (CHAR);
    EXPECT_KEYWORD_AND_SPACE (INT);
    EXPECT_KEYWORD_AND_SPACE (LONG);
    EXPECT_KEYWORD_AND_SPACE (UNSIGNED);
    EXPECT_KEYWORD_AND_SPACE (FLOAT);
    EXPECT_KEYWORD_AND_SPACE (DOUBLE);
    EXPECT_KEYWORD_AND_SPACE (BOOL);
    EXPECT_KEYWORD_AND_SPACE (PNULL);
    EXPECT_KEYWORD_AND_SPACE (BTRUE);
    EXPECT_KEYWORD_AND_SPACE (BFALSE);
    EXPECT_KEYWORD_AND_SPACE (IF);
    EXPECT_KEYWORD_AND_SPACE (ELSE);
    EXPECT_KEYWORD_AND_SPACE (ELIF);
    EXPECT_KEYWORD_AND_SPACE (LET);
    EXPECT_KEYWORD_AND_SPACE (BREAK);
    EXPECT_KEYWORD_AND_SPACE (RETURN);
    EXPECT_KEYWORD_AND_SPACE (DO);
    EXPECT_KEYWORD_AND_SPACE (WHILE);
    EXPECT_KEYWORD           (FOR);
    ku_lexer_free (l);
}

static void
test_token_separators (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_cstring (" \n\t:;(){}[].,-+/*''\"\"``=->--++||&&!"));
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
    EXPECT_SEPARATOR (SQUOTE);
    EXPECT_SEPARATOR (DQUOTE);
    EXPECT_SEPARATOR (DQUOTE);
    EXPECT_SEPARATOR (BQUOTE);
    EXPECT_SEPARATOR (BQUOTE);
    EXPECT_SEPARATOR (EQUALS);
    EXPECT_SEPARATOR (ARROW);
    EXPECT_SEPARATOR (DEC);
    EXPECT_SEPARATOR (INC);
    EXPECT_SEPARATOR (OR);
    EXPECT_SEPARATOR (AND);
    EXPECT_SEPARATOR (NOT);
    ku_lexer_free (l);
}

static void
test_token_dec_arrow (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_cstring ("--->"));
    KuToken *token;
    EXPECT_SEPARATOR (DEC);
    EXPECT_SEPARATOR (ARROW);
    ku_lexer_free (l);
}

static void
test_token_backslash (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_cstring ("\"\\\"foo\\\"bar\\\\baz\""));
    KuToken *token;
    EXPECT_SEPARATOR (DQUOTE);
    EXPECT_STRING    ("\"foo\"bar\\baz");
    EXPECT_SEPARATOR (DQUOTE);
    ku_lexer_free (l);
}

static void
test_token_string_with_seps (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_cstring ("\"foo bar-baz\""));
    KuToken *token;
    EXPECT_SEPARATOR (DQUOTE);
    EXPECT_STRING    ("foo bar-baz");
    EXPECT_SEPARATOR (DQUOTE);
    ku_lexer_free (l);
}

static void
test_real_world_one (void)
{
    KuLexer *l = ku_lexer_new (ku_stream_new_from_file (ku_file_new (SRC_DIR "/tests/data/test-one.ku", READ)));
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
    EXPECT_SEPARATOR (INC);
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
    EXPECT_SEPARATOR (DEC);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_SEPARATOR (RIGHT_CURLY);
    EXPECT_SEPARATOR (NEWLINE);

    EXPECT_KEYWORD   (RETURN);
    EXPECT_SEPARATOR (SPACE);
    EXPECT_STRING    ("0");
//    EXPECT_INT       (0);
    EXPECT_SEPARATOR (SEMI_COLON);
    EXPECT_SEPARATOR (NEWLINE);

    ku_lexer_free (l);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[])
{
    test_token_reserved_keywords ();
    test_token_separators ();
    test_token_dec_arrow ();
    test_token_backslash ();
    test_token_string_with_seps ();
    test_real_world_one ();
    return 0;
}
