#include "ku-file.h"

#include <assert.h>
#include <string.h>

static void
test_ku_file_null (void)
{
    KuFile *f = ku_file_new (NULL, READ);
    assert (ku_file_is_empty (f));
    ku_file_free (f);
}

static void
test_ku_file_read_full (KuFile *f)
{
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
}

static void
test_ku_file_read (void)
{
    KuFile *f = ku_file_new ("tests/data/test-file.txt", READ);
    test_ku_file_read_full (f);
    ku_file_free (f);
}

static void
test_ku_file_full (void)
{
    char filename[18];
    strcpy (filename, "ku-file-rw-XXXXXX");
    mktemp (filename);
    KuFile *wf = ku_file_new (filename, WRITE);
    ku_file_write (wf, "abc");
    ku_file_free (wf);
    KuFile *rwf = ku_file_new (filename, READ_WRITE);
    test_ku_file_read_full (rwf);
    ku_file_write (rwf, "abc");
    ku_file_free (rwf);
    KuFile *rf = ku_file_new (filename, READ);
    ku_file_skip (rf, 3);
    test_ku_file_read_full (rf);
    ku_file_free (rf);
    KuFile *df = ku_file_new (filename, WRITE);
    ku_file_delete (&df);
    assert (df == NULL);
    assert (ku_file_new (filename, READ) == NULL);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_file_null ();
    test_ku_file_read ();
    test_ku_file_full ();
    return 0;
}
