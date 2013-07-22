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

#ifndef __KU_LIST_H__
#define __KU_LIST_H__

#ifdef KU_COMPILATION
#include "config.h"
#endif

typedef struct _KuList KuList;

typedef void (*KuListFreeFn) (void *);

KuList *ku_list_new (void *data);

KuList *ku_list_prepend (KuList *list,
                         void   *data);
KuList *ku_list_append (KuList *list,
                        void   *data);

KuList *ku_list_prev (KuList *list);
KuList *ku_list_next (KuList *list);

void *ku_list_get_data_raw (KuList *list);

#define ku_list_get_data(list, Type) ((Type) ku_list_get_data_raw (list))

void ku_list_free (KuList      *list,
                   KuListFreeFn free_fn);

#endif /*__KU_LIST_H__*/
