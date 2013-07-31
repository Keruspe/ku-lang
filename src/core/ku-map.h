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

#ifndef __KU_MAP_H__
#define __KU_MAP_H__

#ifdef KU_COMPILATION
#include "config.h"
#endif

typedef struct _KuMap KuMap;

typedef unsigned int (*KuMapKeyHashFn) (const void *);
typedef int (*KuMapKeyCompareFn) (const void *, const void *);

KuMap *ku_map_new (KuMapKeyHashFn    hash_fn,
                   KuMapKeyCompareFn compare_fn);

KuMap *ku_string_map_new (void);

void ku_map_put (KuMap *map,
                 void  *key,
                 void  *value);

void *ku_map_get_raw (KuMap      *map,
                      const void *key);

#define ku_map_get(map, key, Type) ((Type *) ku_map_get_raw (map, key))

void ku_map_remove (KuMap      *map,
                    const void *key);

void ku_map_free (KuMap *map);

#endif /*__KU_MAP_H__*/
