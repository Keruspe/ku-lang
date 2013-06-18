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

#ifndef __KU_STREAM_H__
#define __KU_STREAM_H__

#include <ku-file.h>
#include <ku-string.h>

/*
FIXME: use it when ready
#define ku_stream_new(x)                      \
    _Generic ((x),                            \
        KuFile*  : ku_stream_new_from_file    \
        KuString*: ku_stream_new_from_string  \
        default  : ku_stream_new_from_cstring \
    ) (x)
*/

typedef struct _KuStream KuStream;

KuStream *ku_stream_new_from_cstring (const char *string);
KuStream *ku_stream_new_from_string  (KuString   *string);
KuStream *ku_stream_new_from_file    (KuFile     *file);

bool ku_stream_is_empty  (KuStream *stream);
char ku_stream_read_char (KuStream *stream);

void ku_stream_free (KuStream *stream);

#endif /*__KU_STREAM_H__*/
