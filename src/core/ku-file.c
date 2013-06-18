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

#include "ku-file-private.h"

KU_VISIBLE KuFile *
ku_file_new (const char *filename)
{
    if (!filename)
        return NULL;

    FILE *f = fopen (filename, "r+");
    if (!f)
        return NULL;

    KuFile *file = (KuFile *) malloc (sizeof (KuFile));
    file->file = f;
    file->read = EOF;
    return file;
}

KU_VISIBLE bool
ku_file_is_empty (KuFile *file)
{
    if (!file)
        return true;

    if (file->read != EOF)
        return false;

    file->read = fgetc (file->file);
    return (file->read == EOF);
}

KU_VISIBLE char
ku_file_read_char (KuFile *file)
{
    if (ku_file_is_empty (file))
        return '\0';

    char read = file->read;
    file->read = EOF;
    return read;
}

KU_VISIBLE void
ku_file_free (KuFile *file)
{
    if (file)
    {
        fclose (file->file);
        free (file);
    }
}
