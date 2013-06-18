dnl This file is part of Autoconf.                        -*- Autoconf -*-
dnl Programming languages support.
dnl Copyright (C) 2001-2012 Free Software Foundation, Inc.

dnl This file is part of Autoconf.  This program is free
dnl software; you can redistribute it and/or modify it under the
dnl terms of the GNU General Public License as published by the
dnl Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl Under Section 7 of GPL version 3, you are granted additional
dnl permissions described in the Autoconf Configure Script Exception,
dnl version 3.0, as published by the Free Software Foundation.
dnl
dnl You should have received a copy of the GNU General Public License
dnl and a copy of the Autoconf Configure Script Exception along with
dnl this program; see the files COPYINGv3 and COPYING.EXCEPTION
dnl respectively.  If not, see <http://www.gnu.org/licenses/>.

dnl Written by David MacKenzie, with help from
dnl Akim Demaille, Paul Eggert,
dnl Franc,ois Pinard, Karl Berry, Richard Pixley, Ian Lance Taylor,
dnl Roland McGrath, Noah Friedman, david d zuhn, and many others.

dnl _AC_PROG_CC_C11 ([ACTION-IF-AVAILABLE], [ACTION-IF-UNAVAILABLE])
dnl ----------------------------------------------------------------
dnl If the C compiler is not in ISO C11 mode by default, try to add an
dnl option to output variable CC to make it so.  This macro tries
dnl various options that select ISO C11 on some system or another.  It
dnl considers the compiler to be in ISO C11 mode if it handles _Alignas,
dnl _Alignof, _Noreturn, _Static_assert, UTF-8 string literals,
dnl duplicate typedefs, and anonymous structures and unions.
AC_DEFUN([_AC_PROG_CC_C11],
[_AC_C_STD_TRY([c11],
[_AC_C_C99_TEST_HEADER[
// Check _Alignas.
char _Alignas (double) aligned_as_double;
char _Alignas (0) no_special_alignment;
extern char aligned_as_int;
char _Alignas (0) _Alignas (int) aligned_as_int;

// Check _Alignof.
enum
{
  int_alignment = _Alignof (int),
  int_array_alignment = _Alignof (int[100]),
  char_alignment = _Alignof (char)
};
_Static_assert (0 < -_Alignof (int), "_Alignof is signed");

// Check _Noreturn.
int _Noreturn does_not_return (void) { for (;;) continue; }

// Check _Static_assert.
struct test_static_assert
{
  int x;
  _Static_assert (sizeof (int) <= sizeof (long int),
                  "_Static_assert does not work in struct");
  long int y;
};

// Check UTF-8 literals.
dnldefine u8 syntax error!
char const utf8_literal[] = u8"happens to be ASCII" "another string";

// Check duplicate typedefs.
typedef long *long_ptr;
typedef long int *long_ptr;
typedef long_ptr long_ptr;

// Anonymous structures and unions -- taken from C11 6.7.2.1 Example 1.
struct anonymous
{
  union {
    struct { int i; int j; };
    struct { int k; long int l; } w;
  };
  int m;
} v1;
]],
[_AC_C_C99_TEST_BODY[
  v1.i = 2;
  v1.w.k = 5;
  _Static_assert (&v1.i == &v1.w.k, "Anonymous union alignment botch");
]],
dnl Try
dnl GCC		-std=gnu11 (unused restrictive mode: -std=c11)
dnl with extended modes being tried first.
[[-std=gnu11]], [$1], [$2])[]dnl
])dnl _AC_PROG_CC_C11
