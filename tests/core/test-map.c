#include "ku-map.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void
test_ku_map_full (void)
{
    KuMap *map = ku_string_map_new ();
    ku_map_put (map, (char *) "foo", (char *) "foo");
    ku_map_put (map, (char *) "foo", (char *) "Foo");
    ku_map_put (map, (char *) "bar", (char *) "Bar");
    ku_map_put (map, (char *) "baz", (char *) "Baz");
    assert (!strcmp ("Foo", ku_map_get (map, "foo", char *)));
    assert (!strcmp ("Bar", ku_map_get (map, "bar", char *)));
    assert (!strcmp ("Baz", ku_map_get (map, "baz", char *)));
    ku_map_remove (map, "foo");
    assert (!ku_map_get_raw (map, "foo"));
    ku_map_free (map);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_map_full ();
    return 0;
}
