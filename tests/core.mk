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

TESTS +=                                  \
	tests/core/test-file              \
	tests/core/test-reserved-keywords \
	tests/core/test-stream            \
	tests/core/test-string            \
	$(NULL)

tests_core_test_file_SOURCES = \
	tests/core/test-file.c \
	$(NULL)

tests_core_test_file_LDADD =  \
	$(libku_core_la_file) \
	$(NULL)

tests_core_test_reserved_keywords_SOURCES = \
	tests/core/test-reserved-keywords.c \
	$(NULL)

tests_core_test_reserved_keywords_LDADD =  \
	$(libku_core_la_file)              \
	$(NULL)

tests_core_test_stream_SOURCES = \
	tests/core/test-stream.c \
	$(NULL)

tests_core_test_stream_LDADD = \
	$(libku_core_la_file)  \
	$(NULL)

tests_core_test_string_SOURCES = \
	tests/core/test-string.c \
	$(NULL)

tests_core_test_string_LDADD = \
	$(libku_core_la_file)  \
	$(NULL)
