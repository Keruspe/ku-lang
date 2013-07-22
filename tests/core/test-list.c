#include "ku-list.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void
test_ku_list_full (void)
{
    KuList *list = ku_list_new (NULL);
    assert (!list);
    assert (!ku_list_get_data_raw (list));
    list = ku_list_prepend (list, strdup ("foo"));
    list = ku_list_append  (list, strdup ("bar"));
    list = ku_list_prepend (list, strdup ("baz"));
    assert (!ku_list_prev (list));
    KuList *test = list;
    assert (!strcmp (ku_list_get_data (test, char *), "baz"));
    test = ku_list_next (test);
    assert (!strcmp (ku_list_get_data (test, char *), "foo"));
    test = ku_list_prev (test);
    assert (!strcmp (ku_list_get_data (test, char *), "baz"));
    test = ku_list_next (test);
    test = ku_list_next (test);
    assert (!strcmp (ku_list_get_data (test, char *), "bar"));
    assert (!ku_list_next (test));
    ku_list_free (list, free);
}

static void
test_ku_list_null_append (void)
{
    KuList *list = ku_list_new (NULL);
    assert (!list);
    list = ku_list_append (list, (char *)"foo");
    assert (!ku_list_prev (list));
    assert (!ku_list_next (list));
    ku_list_free (list, NULL);
}

int
main (int KU_UNUSED argc, char KU_UNUSED *argv[]) {
    test_ku_list_full ();
    test_ku_list_null_append ();
    return 0;
}
