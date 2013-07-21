#include "ku-parser.h"

#include <assert.h>

static void
test_real_world_one (void)
{
    KuParser *p = ku_parser_new (ku_stream_new_from_file (ku_file_new (SRC_DIR "/tests/data/test-one.ku", READ)));
    ku_parser_free (p);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[])
{
    test_real_world_one ();
    return 0;
}
