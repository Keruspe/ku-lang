#include "ku-reserved-keywords.h"

#include <assert.h>
#include <stdlib.h>

#define TEST_KEYWORD(token, keyword)                         \
    assert (ku_token_cstring_to_reserved_keyword (token) == keyword)

static void
test_ku_reserved_keywords_full (void)
{
    TEST_KEYWORD ("char", CHAR);
    TEST_KEYWORD ("int", INT);
    TEST_KEYWORD ("long", LONG);
    TEST_KEYWORD ("unsigned", UNSIGNED);
    TEST_KEYWORD ("float", FLOAT);
    TEST_KEYWORD ("double", DOUBLE);
    TEST_KEYWORD ("bool", BOOL);
    TEST_KEYWORD ("NULL", PNULL);
    TEST_KEYWORD ("TRUE", BTRUE);
    TEST_KEYWORD ("FALSE", BFALSE);
    TEST_KEYWORD ("if", IF);
    TEST_KEYWORD ("else", ELSE);
    TEST_KEYWORD ("elif", ELIF);
    TEST_KEYWORD ("let", LET);
    TEST_KEYWORD ("break", BREAK);
    TEST_KEYWORD ("return", RETURN);
    TEST_KEYWORD ("do", DO);
    TEST_KEYWORD ("while", WHILE);
    TEST_KEYWORD ("for", FOR);
    TEST_KEYWORD ("abc", K_NONE);
}

static void
test_ku_is_reserved_keyword_full (void)
{
    assert (ku_token_cstring_is_reserved_keyword ("char"));
    assert (ku_token_cstring_is_reserved_keyword ("for"));
    assert (!ku_token_cstring_is_reserved_keyword ("abc"));
    assert (!ku_token_cstring_is_reserved_keyword ("fora"));
    assert (!ku_token_cstring_is_reserved_keyword ("aif"));
    assert (!ku_token_cstring_is_reserved_keyword ("ifchar"));
    assert (!ku_token_cstring_is_reserved_keyword (""));
    assert (!ku_token_cstring_is_reserved_keyword (NULL));
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_reserved_keywords_full ();
    test_ku_is_reserved_keyword_full ();
    return 0;
}
