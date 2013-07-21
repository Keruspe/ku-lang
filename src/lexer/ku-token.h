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

#ifndef __KU_TOKEN_H__
#define __KU_TOKEN_H__

#include "ku-reserved-keywords.h"
#include "ku-separator.h"
#include "ku-string.h"

#include <stdbool.h>

typedef struct _KuToken KuToken;

KuToken *ku_token_new_reserved_keyword (KuReservedKeyword keyword);
KuToken *ku_token_new_separator        (KuSeparator       separator);
KuToken *ku_token_new_literal          (KuString         *literal);
KuToken *ku_token_new_string           (KuString         *string);

bool ku_token_is_reserved_keyword (KuToken *token);
bool ku_token_is_separator        (KuToken *token);
bool ku_token_is_literal          (KuToken *token);
bool ku_token_is_string           (KuToken *token);

KuReservedKeyword ku_token_get_reserved_keyword_value (const KuToken *token);
KuSeparator       ku_token_get_separator_value        (const KuToken *token);
const KuString   *ku_token_get_literal_value          (const KuToken *token);
const KuString   *ku_token_get_string_value           (const KuToken *token);

void ku_token_free (KuToken *token);

#endif /*__KU_TOKEN_H__*/
