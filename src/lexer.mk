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

libku_lexer_la_file = src/lexer/libku-lexer.la

LIBKU_LEXER_CURRENT=0
LIBKU_LEXER_REVISION=0
LIBKU_LEXER_AGE=0

libku_lexer_public_headers = \
	src/lexer/ku-lexer.h \
	src/lexer/ku-token.h \
	$(NULL)

libku_lexer_private_headers =        \
	src/lexer/ku-lexer-private.h \
	src/lexer/ku-token-private.h \
	$(NULL)

src_lexer_libku_lexer_la_SOURCES =     \
	$(libku_lexer_public_headers)  \
	$(libku_lexer_private_headers) \
	src/lexer/ku-lexer.c           \
	src/lexer/ku-token.c           \
	$(NULL)

libku_lexer_symbols_file = $(srcdir)/src/lexer/libku-lexer.sym

src_lexer_libku_lexer_la_LDFLAGS =                                                      \
	-version-info $(LIBKU_LEXER_CURRENT):$(LIBKU_LEXER_REVISION):$(LIBKU_LEXER_AGE) \
	-Wl,--version-script=$(libku_lexer_symbols_file)                                \
	$(NULL)

src_lexer_libku_lexer_la_DEPENDENCIES = \
	$(libku_lexer_symbols_file)     \
	$(libku_core_la_file)           \
	$(NULL)

src_lexer_libku_lexer_la_LIBADD = \
	$(libku_core_la_file)     \
	$(NULL)

pkginclude_HEADERS +=                \
	$(libku_lexer_public_headers) \
	$(NULL)

lib_LTLIBRARIES +=             \
	$(libku_lexer_la_file) \
	$(NULL)

EXTRA_DIST +=                      \
	$(libku_lexer_symbols_file) \
	$(NULL)
