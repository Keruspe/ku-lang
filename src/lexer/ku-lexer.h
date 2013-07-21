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

#ifndef __KU_LEXER_H__
#define __KU_LEXER_H__

#include "ku-stream.h"
#include "ku-token.h"

typedef struct _KuLexer KuLexer;

KuLexer *ku_lexer_new (KuStream *stream);

KuToken *ku_lexer_read_token (KuLexer *lexer);

KuToken *ku_lexer_read_token_no_spaces (KuLexer *lexer);

void ku_lexer_free (KuLexer *lexer);

#endif /*__KU_LEXER_H__*/
