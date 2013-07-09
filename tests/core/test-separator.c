#include "ku-separator.h"

#include <assert.h>
#include <stdlib.h>

#define TEST_SEPARATOR(token, separator) \
    assert (ku_token_cstring_to_separator (token) == separator)

static void
test_ku_separators_full (void)
{
    TEST_SEPARATOR (" ",   SPACE);
    TEST_SEPARATOR ("\n",  NEWLINE);
    TEST_SEPARATOR ("\t",  TAB);
    TEST_SEPARATOR (":",   COLON);
    TEST_SEPARATOR (";",   SEMI_COLON);
    TEST_SEPARATOR ("(",   LEFT_PAREN);
    TEST_SEPARATOR (")",   RIGHT_PAREN);
    TEST_SEPARATOR ("{",   LEFT_CURLY);
    TEST_SEPARATOR ("}",   RIGHT_CURLY);
    TEST_SEPARATOR ("[",   LEFT_BRACKET);
    TEST_SEPARATOR ("]",   RIGHT_BRACKET);
    TEST_SEPARATOR (".",   DOT);
    TEST_SEPARATOR (",",   COMMA);
    TEST_SEPARATOR ("-",   MINUS);
    TEST_SEPARATOR ("+",   PLUS);
    TEST_SEPARATOR ("*",   TIMES);
    TEST_SEPARATOR ("/",   DIVIDE);
    TEST_SEPARATOR ("'",   SQUOTE);
    TEST_SEPARATOR ("\"",  DQUOTE);
    TEST_SEPARATOR ("`",   BQUOTE);
    TEST_SEPARATOR ("abc", S_NONE);
}

static void
test_ku_is_separator_full (void)
{
    assert (ku_token_cstring_is_separator (" "));
    assert (ku_token_cstring_is_separator (":"));
    assert (!ku_token_cstring_is_separator ("a:c"));
    assert (!ku_token_cstring_is_separator ("for.a"));
    assert (!ku_token_cstring_is_separator ("a,f"));
    assert (!ku_token_cstring_is_separator (".,"));
    assert (!ku_token_cstring_is_separator (""));
    assert (!ku_token_cstring_is_separator (NULL));
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_separators_full ();
    test_ku_is_separator_full ();
    return 0;
}
