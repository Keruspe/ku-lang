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

#include "ku-stream-private.h"

static KuStream *
ku_stream_new_full (KuFile   *file,
                    KuString *string)
{
    if (!file && !string)
        return NULL;

    KuStream *s = (KuStream *) malloc (sizeof (KuStream));
    s->file = file;
    s->string = string;
    return s;
}

KU_VISIBLE KuStream *
ku_stream_new_from_file (KuFile *file)
{
    return ku_stream_new_full (file, NULL);
}

KU_VISIBLE KuStream *
ku_stream_new_from_string (KuString *string)
{
    return ku_stream_new_full (NULL, string);
}

KU_VISIBLE KuStream *
ku_stream_new_from_cstring (const char *string)
{
    return ku_stream_new_from_string (ku_string_new (string));
}

KU_VISIBLE bool
ku_stream_is_empty (KuStream *stream)
{
    return (!stream || (ku_file_is_empty (stream->file) && ku_string_is_empty (stream->string)));
}

KU_VISIBLE char
ku_stream_read_char (KuStream *stream)
{
    return (stream->file)
        ? ku_file_read_char (stream->file)
        : ku_string_read_char (stream->string);
}

KU_VISIBLE void
ku_stream_skip (KuStream    *stream,
                unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i)
        ku_stream_read_char (stream);
}

KU_VISIBLE void
ku_stream_free (KuStream *stream)
{
    if (stream)
    {
        ku_file_free (stream->file);
        ku_string_free (stream->string);
        free (stream);
    }
}
