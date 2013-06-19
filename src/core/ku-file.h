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

#ifndef __KU_FILE_H__
#define __KU_FILE_H__

#ifdef KU_COMPILATION
#include "config.h"
#endif

#include <stdbool.h>
#include <stdlib.h>

typedef struct _KuFile KuFile;

typedef enum {
    READ =  1 << 0,
    WRITE = 1 << 1,
    READ_WRITE = READ|WRITE
} KuFileMode;

KuFile *ku_file_new (const char *filename,
                     KuFileMode  mode);

bool ku_file_is_empty  (KuFile *file);
char ku_file_read_char (KuFile *file);

void ku_file_write (KuFile     *file,
                    const char *content);

void ku_file_free (KuFile *file);

#endif /*__KU_FILE_H__*/
