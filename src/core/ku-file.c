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

#include <string.h>
#include <unistd.h>

static const char *
ku_file_mode_to_mode (KuFileMode mode)
{
    switch (mode)
    {
        case READ_WRITE:
            return "rw+";
        case WRITE:
            return "w+";
        default:
            return "r";
    }
}

KU_VISIBLE KuFile *
ku_file_new (const char *filename,
             KuFileMode  mode)
{
    if (!filename)
        return NULL;

    FILE *f = fopen (filename, ku_file_mode_to_mode (mode));
    if (!f)
        return NULL;

    KuFile *file = (KuFile *) malloc (sizeof (KuFile));
    file->file = f;
    file->filename = strdup (filename);
    file->mode = mode;
    file->read = EOF;
    return file;
}

KU_VISIBLE bool
ku_file_is_empty (KuFile *file)
{
    if (!file || !(file->mode & READ))
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
ku_file_write (KuFile     *file,
               const char *content)
{
    if (file && content && (file->mode & WRITE))
        fprintf (file->file, "%s", content);
}

static void
ku_file_free_full (KuFile *file,
                   bool    delete)
{
    if (file)
    {
        fclose (file->file);
        if (delete)
            unlink (file->filename);
        free (file->filename);
        free (file);
    }
}

KU_VISIBLE void
ku_file_delete (KuFile **file)
{
    if (file && *file)
    {
        ku_file_free_full (*file, true);
        *file = NULL;
    }
}

KU_VISIBLE void
ku_file_free (KuFile *file)
{
    ku_file_free_full (file, false);
}
