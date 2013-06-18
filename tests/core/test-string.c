#include "ku-string.h"

#include <assert.h>

static void
test_ku_string_null (void)
{
    KuString *s = ku_string_new (0);
    assert (ku_string_is_empty (s));
    ku_string_free (s);
}

static void
test_ku_string_full (void)
{
    KuString *s = ku_string_new ("abc");
    assert (!ku_string_is_empty (s));
    assert (ku_string_read_char (s) == 'a');
    assert (ku_string_read_char (s) == 'b');
    assert (!ku_string_is_empty (s));
    assert (ku_string_read_char (s) == 'c');
    assert (ku_string_is_empty (s));
    assert (ku_string_read_char (s) == '\0');
    assert (ku_string_is_empty (s));
    assert (ku_string_read_char (s) == '\0');
    assert (ku_string_is_empty (s));
    ku_string_free (s);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_string_null ();
    test_ku_string_full ();
    return 0;
}
