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

libku_core_la_file = src/core/libku-core.la

LIBKU_CORE_CURRENT=0
LIBKU_CORE_REVISION=0
LIBKU_CORE_AGE=0

libku_core_public_headers =  \
	src/core/ku-string.h \
	$(NULL)

libku_core_private_headers =         \
	src/core/ku-string-private.h \
	$(NULL)

src_core_libku_core_la_SOURCES =      \
	$(libku_core_public_headers)  \
	$(libku_core_private_headers) \
	src/core/ku-string.c          \
	$(NULL)

libku_core_symbols_file = $(srcdir)/src/core/libku-core.sym

src_core_libku_core_la_LDFLAGS =                                                     \
	-version-info $(LIBKU_CORE_CURRENT):$(LIBKU_CORE_REVISION):$(LIBKU_CORE_AGE) \
	-Wl,--version-script=$(libku_core_symbols_file)                              \
	$(NULL)

src_core_libku_core_la_DEPENDENCIES = \
	$(libku_core_symbols_file)    \
	$(NULL)

pkginclude_HEADERS +=                \
	$(libku_core_public_headers) \
	$(NULL)

lib_LTLIBRARIES +=            \
	$(libku_core_la_file) \
	$(NULL)

EXTRA_DIST +=                      \
	$(libku_core_symbols_file) \
	$(NULL)
