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

#ifndef __KU_STRING_H__
#define __KU_STRING_H__

#ifdef KU_COMPILATION
#include "config.h"
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _KuString KuString;

KuString *ku_string_new (const char *string);

bool ku_string_is_empty  (KuString *string);
char ku_string_read_char (KuString *string);

const char *ku_string_get_cstring (KuString *string);
size_t      ku_string_get_length  (KuString *string);

void ku_string_free (KuString *string);

#endif /*__KU_STRING_H__*/
