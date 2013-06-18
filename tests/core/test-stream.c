#include "ku-stream.h"

#include <assert.h>

static void
test_ku_stream_null (void)
{
    KuStream *s = ku_stream_new_from_cstring (NULL);
    assert (ku_stream_is_empty (s));
    ku_stream_free (s);
}

static void
_test_ku_stream_full(KuStream *s)
{
    assert (!ku_stream_is_empty (s));
    assert (ku_stream_read_char (s) == 'a');
    assert (ku_stream_read_char (s) == 'b');
    assert (!ku_stream_is_empty (s));
    assert (ku_stream_read_char (s) == 'c');
    assert (ku_stream_is_empty (s));
    assert (ku_stream_read_char (s) == '\0');
    assert (ku_stream_is_empty (s));
    assert (ku_stream_read_char (s) == '\0');
    assert (ku_stream_is_empty (s));
    ku_stream_free (s);
}

static void
test_ku_stream_string_full (void)
{
    _test_ku_stream_full (ku_stream_new_from_string (ku_string_new ("abc")));
}

static void
test_ku_stream_cstring_full (void)
{
    _test_ku_stream_full (ku_stream_new_from_cstring ("abc"));
}

static void
test_ku_stream_file_full (void)
{
    _test_ku_stream_full (ku_stream_new_from_file (ku_file_new ("tests/data/test-file.txt")));
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_stream_null();
    test_ku_stream_string_full ();
    test_ku_stream_cstring_full ();
    test_ku_stream_file_full ();
    return 0;
}
