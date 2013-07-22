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

#include "ku-list-private.h"

#include <stdlib.h>

static KuList *
_ku_list_new (KuList *prev,
              KuList *next,
              void   *data)
{
    KuList *list = (KuList *) malloc (sizeof (KuList));
    list->prev = prev;
    list->next = next;
    list->data = data;
    return list;
}

KU_VISIBLE KuList *
ku_list_new (void *data)
{
    if (!data)
        return NULL;
    return _ku_list_new (NULL, NULL, data);
}

KU_VISIBLE KuList *
ku_list_prepend (KuList *list,
                 void   *data)
{
    if (!data)
        return list;
    if (!list)
        return ku_list_new (data);
    return list->prev = _ku_list_new (list->prev, list, data);
}

KU_VISIBLE KuList *
ku_list_append (KuList *list,
                void   *data)
{
    if (!data)
        return list;
    if (!list)
        return ku_list_new (data);
    KuList *last = list;
    while (list->next)
        last = list->next;
    last->next = _ku_list_new (last, NULL, data);
    return list;
}

KU_VISIBLE KuList *
ku_list_prev (KuList *list)
{
    return (list) ? list->prev : NULL;
}

KU_VISIBLE KuList *
ku_list_next (KuList *list)
{
    return (list) ? list->next : NULL;
}

KU_VISIBLE void *
ku_list_get_data_raw (KuList *list)
{
    return (list) ? list->data : NULL;
}

KU_VISIBLE void
ku_list_free (KuList      *list,
              KuListFreeFn free_fn)
{
    if (list)
    {
        while (list->prev)
            list = list->prev;
        if (list->next)
        {
            list->next->prev = NULL;
            ku_list_free (list->next, free_fn);
        }
        if (free_fn)
            free_fn (list->data);
        free (list);
    }
}
