#include "ku-map.h"
#include "ku-string.h"

#include <assert.h>
#include <stdlib.h>

static void
test_ku_map_full (void)
{
    KuMap *map = ku_string_map_new ();
    KuString *Foo = ku_string_new ("Foo");
    KuString *foo = ku_string_new ("foo");
    KuString *bar = ku_string_new ("bar");
    KuString *baz = ku_string_new ("baz");
    ku_map_put (map, foo, foo);
    ku_map_put (map, foo, Foo);
    ku_map_put (map, bar, bar);
    ku_map_put (map, baz, baz);
    assert (ku_string_equals (Foo, ku_map_get (map, foo, KuString)));
    assert (ku_string_equals (bar, ku_map_get (map, bar, KuString)));
    assert (ku_string_equals (baz, ku_map_get (map, baz, KuString)));
    ku_map_remove (map, foo);
    assert (!ku_map_get_raw (map, foo));
    ku_map_free (map);
    ku_string_free (Foo);
    ku_string_free (foo);
    ku_string_free (bar);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_map_full ();
    return 0;
}
