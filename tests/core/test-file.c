#include "ku-file.h"

#include <assert.h>

static void
test_ku_file_null (void)
{
    KuFile *f = ku_file_new (NULL, READ);
    assert (ku_file_is_empty (f));
    ku_file_free (f);
}

static void
test_ku_file_full (void)
{
    KuFile *f = ku_file_new ("tests/data/test-file.txt", READ);
    assert (!ku_file_is_empty (f));
    assert (ku_file_read_char (f) == 'a');
    assert (ku_file_read_char (f) == 'b');
    assert (!ku_file_is_empty (f));
    assert (ku_file_read_char (f) == 'c');
    assert (ku_file_is_empty (f));
    assert (ku_file_read_char (f) == '\0');
    assert (ku_file_is_empty (f));
    assert (ku_file_read_char (f) == '\0');
    assert (ku_file_is_empty (f));
    ku_file_free (f);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_file_null ();
    test_ku_file_full ();
    return 0;
}
