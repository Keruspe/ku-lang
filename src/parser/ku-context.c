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

#include "ku-context-private.h"
#include "ku-symbol-private.h"

#include <stdlib.h>

KU_VISIBLE KuContext *
ku_context_new (KuContext *parent)
{
    KuContext *context = (KuContext *) malloc (sizeof (KuContext));
    context->parent = parent;
    context->symbols = ku_string_map_new ();
    context->types = ku_list_new (NULL);
    return context;
}

KU_VISIBLE const KuSymbol *
ku_context_get (KuContext  *context,
                const char *name)
{
    if (!context || !name)
        return NULL;
    return ku_map_get (context->symbols, name, KuSymbol *);
}

KU_VISIBLE void
ku_context_register_type (KuContext *context,
                          KuType    *type)
{
    if (context && type)
    {
        ku_map_put (context->symbols, (char *)ku_string_get_cstring (ku_symbol_get_name (KU_SYMBOL (type))), type);
        context->types = ku_list_prepend (context->types, type);
    }
}

KU_VISIBLE void
ku_context_register_variable (KuContext  *context,
                              KuVariable *variable)
{
    if (context && variable)
    {
        ku_map_put (context->symbols, (char *)ku_string_get_cstring (ku_symbol_get_name (KU_SYMBOL (variable))), variable);
        context->vars = ku_list_prepend (context->vars, variable);
    }
}
