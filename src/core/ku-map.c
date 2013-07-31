/*
 *      This file is part of ku.
 *
 *      Copyright 2013 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 *
 *      ku is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      ku is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with ku.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ku-map-private.h"
#include "ku-list-private.h" // FIXME: remove me

#include "ku-string.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

KU_VISIBLE KuMap *
ku_map_new (KuMapKeyHashFn    hash_fn,
            KuMapKeyCompareFn compare_fn)
{
    assert (hash_fn);
    assert (compare_fn);
    KuMap *map = (KuMap *) malloc (sizeof (KuMap));
    map->hash_fn = hash_fn;
    map->compare_fn = compare_fn;
    return map;
}

static unsigned int
string_hash (const void *data)
{
    const char *str = ku_string_get_cstring ((const KuString *) data);

    /* DJB's hash func */
    unsigned int hash = 5381;
    const char *c;

    for (c = str; *c; ++c)
        hash = (hash << 5) + hash + (unsigned int) *c;

    return hash;
}

static int
string_compare (const void *s1,
                const void *s2)
{
    return !ku_string_equals ((const KuString *) s1, (const KuString *) s2);
}

KU_VISIBLE KuMap *
ku_string_map_new (void)
{
    return ku_map_new (string_hash, string_compare);
}

static KuMapEntry *
ku_map_entry_new (void *key,
                  void *value)
{
    assert (key);
    assert (value);
    KuMapEntry *entry = (KuMapEntry *) malloc (sizeof (KuMapEntry));
    entry->key = key;
    entry->value = value;
    return entry;
}

static void
insert (KuMap       *map,
        unsigned int hash,
        void        *key,
        void        *value)
{
    KuList *bucket = map->buckets[hash];
    while (bucket)
    {
        KuMapEntry *entry = ku_list_get_data (bucket, KuMapEntry *);
        if (entry)
        {
            if (!map->compare_fn (key, entry->key))
            {
                entry->value = value;
                return;
            }
        }
        bucket = ku_list_next (bucket);
    }
    map->buckets[hash] = ku_list_append (bucket, ku_map_entry_new (key, value));
}

KU_VISIBLE void
ku_map_put (KuMap *map,
            void  *key,
            void  *value)
{
    assert (map);
    assert (key);
    unsigned int hash = map->hash_fn (key) % NB_BUCKETS;
    insert (map, hash, key, value);
}

KU_VISIBLE void *
ku_map_get_raw (KuMap      *map,
                const void *key)
{
    assert (map);
    assert (key);
    unsigned int hash = map->hash_fn (key) % NB_BUCKETS;
    KuList *bucket = map->buckets[hash];
    while (bucket)
    {
        KuMapEntry *entry = ku_list_get_data (bucket, KuMapEntry *);
        if (entry)
        {
            if (!map->compare_fn (key, entry->key))
                return entry->value;
        }
        bucket = ku_list_next (bucket);
    }
    return NULL;
}

static void
remove (KuMap       *map,
        unsigned int hash,
        const void  *key)
{
    KuList *bucket = map->buckets[hash];
    while (bucket)
    {
        KuMapEntry *entry = ku_list_get_data (bucket, KuMapEntry *);
        if (entry)
        {
            if (!map->compare_fn (key, entry->key))
            {
                /* FIXME: ku_list_remove */
                KuList *prev = ku_list_prev (bucket);
                KuList *next = ku_list_next (bucket);
                if (prev)
                    prev->next = next;
                else
                    map->buckets[hash] = next;
                if (next)
                    next->prev = prev;
                free (ku_list_get_data_raw (bucket));
                free (bucket);
                return;
            }
        }
        bucket = ku_list_next (bucket);
    }
}
KU_VISIBLE void
ku_map_remove (KuMap      *map,
               const void *key)
{
    assert (map);
    assert (key);
    unsigned int hash = map->hash_fn (key) % NB_BUCKETS;
    remove (map, hash, key);
}

KU_VISIBLE void
ku_map_free (KuMap *map)
{
    if (map)
    {
        for (unsigned int i = 0; i < NB_BUCKETS; ++i)
            ku_list_free (map->buckets[i], free);
        free (map);
    }
}
