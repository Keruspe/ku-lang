# This file is part of ku.
#
# Copyright 2013 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
#
# ku is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ku is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ku.  If not, see <http://www.gnu.org/licenses/>.

libku_parser_la_file = src/parser/libku-parser.la

LIBKU_PARSER_CURRENT=0
LIBKU_PARSER_REVISION=0
LIBKU_PARSER_AGE=0

libku_parser_public_headers =             \
	src/parser/ku-context.h           \
	src/parser/ku-parser.h            \
	src/parser/ku-type.h              \
	src/parser/ku-statement.h         \
	src/parser/ku-boolean-statement.h \
	src/parser/ku-let-statement.h     \
	src/parser/ku-null-statement.h    \
	$(NULL)

libku_parser_private_headers =                    \
	src/parser/ku-context-private.h           \
	src/parser/ku-parser-private.h            \
	src/parser/ku-type-private.h              \
	src/parser/ku-statement-private.h         \
	src/parser/ku-boolean-statement-private.h \
	src/parser/ku-let-statement-private.h     \
	src/parser/ku-null-statement-private.h    \
	$(NULL)

src_parser_libku_parser_la_SOURCES =      \
	$(libku_parser_public_headers)    \
	$(libku_parser_private_headers)   \
	src/parser/ku-context.c           \
	src/parser/ku-parser.c            \
	src/parser/ku-type.c              \
	src/parser/ku-statement.c         \
	src/parser/ku-boolean-statement.c \
	src/parser/ku-let-statement.c     \
	src/parser/ku-null-statement.c    \
	$(NULL)

libku_parser_symbols_file = $(srcdir)/src/parser/libku-parser.sym

src_parser_libku_parser_la_LDFLAGS =                                                       \
	-version-info $(LIBKU_PARSER_CURRENT):$(LIBKU_PARSER_REVISION):$(LIBKU_PARSER_AGE) \
	-Wl,--version-script=$(libku_parser_symbols_file)                                  \
	$(NULL)

src_parser_libku_parser_la_DEPENDENCIES = \
	$(libku_parser_symbols_file)      \
	$(libku_lexer_la_file)            \
	$(NULL)

src_parser_libku_parser_la_LIBADD = \
	$(libku_lexer_la_file)      \
	$(NULL)

pkginclude_HEADERS +=                  \
	$(libku_parser_public_headers) \
	$(NULL)

lib_LTLIBRARIES +=              \
	$(libku_parser_la_file) \
	$(NULL)

EXTRA_DIST +=                        \
	$(libku_parser_symbols_file) \
	$(NULL)
