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

#include "ku-string-private.h"

static KuString *
_ku_string_new (size_t length)
{
    KuString *s = (KuString *) malloc (sizeof (KuString) + (length + 1) * sizeof (char));
    s->length = length;
    return s;
}

KU_VISIBLE KuString *
ku_string_new (const char *string)
{
    if (!string)
        return NULL;

    size_t length = strlen (string);
    KuString *s = _ku_string_new (length);
    strcpy (s->string, string);
    s->pos = 0;
    return s;
}

KU_VISIBLE bool
ku_string_is_empty (const KuString *string)
{
    return (!string || string->pos >= string->length);
}

KU_VISIBLE char
ku_string_read_char (KuString *string)
{
    if (ku_string_is_empty (string))
        return '\0';

    return string->string[string->pos++];
}

KU_VISIBLE const char *
ku_string_get_cstring (const KuString *string)
{
    return (string) ? string->string : NULL;
}

KU_VISIBLE size_t
ku_string_get_length (const KuString *string)
{
    return (string) ? string->length : 0;
}

KU_VISIBLE bool
ku_string_equals (const KuString *str1,
                  const KuString *str2)
{
    if (str1 == str2)
        return true;
    if (!str1 || !str2)
        return false;
    return str1->length == str2->length && !strcmp (str1->string, str2->string);
}

KU_VISIBLE KuString *
ku_string_dup (const KuString *string)
{
    if (!string)
        return NULL;

    KuString *s = _ku_string_new (string->length);
    strcpy (s->string, string->string);
    s->pos = string->pos;
    return s;
}

KU_VISIBLE void
ku_string_free (KuString *string)
{
    if (string)
        free (string);
}
