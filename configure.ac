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

AC_PREREQ([2.69])
AC_INIT([ku],[0.1],[Marc-Antoine@Perennou.com])

# INTLTOOL_REQUIRED="0.50.0"
PKGCONFIG_REQUIRED="0.22"

AC_SUBST([PACKAGE_NAME], ["$PACKAGE_NAME"])
AC_SUBST([PACKAGE_VERSION], ["$PACKAGE_VERSION"])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_PREFIX_DEFAULT([/usr])

AM_PROG_AR
LT_PREREQ([2.2.6])
LT_INIT([disable-static pic-only])

AM_INIT_AUTOMAKE([1.12 subdir-objects check-news foreign no-dist-gzip dist-xz tar-ustar -Wall])
AM_SILENT_RULES([yes])

AC_PROG_SED
AC_PROG_MKDIR_P
AC_PROG_INSTALL

AC_PROG_CC
AC_PROG_CC_C11
AM_PROG_CC_C_O

AC_CHECK_HEADER_STDBOOL

CC_ATTRIBUTE_UNUSED
CC_ATTRIBUTE_VISIBILITY([default])

CC_CHECK_CFLAGS_APPEND([ \
                         -pipe \
                         -pedantic \
                         -DANOTHER_BRICK_IN_THE \
                         -Wall \
                         -W \
                         -Wextra \
                         -Wvla \
                         -Wundef \
                         -Wformat=2 \
                         -Wlogical-op \
                         -Wsign-compare \
                         -Wformat-security \
                         -Wmissing-include-dirs \
                         -Wformat-nonliteral \
                         -Wold-style-definition \
                         -Wpointer-arith \
                         -Winit-self \
                         -Wfloat-equal \
                         -Wmissing-prototypes \
                         -Wstrict-prototypes \
                         -Wredundant-decls \
                         -Wmissing-declarations \
                         -Wmissing-noreturn \
                         -Wshadow \
                         -Wendif-labels \
                         -Wcast-align \
                         -Wstrict-aliasing=2 \
                         -Wwrite-strings \
                         -Werror=overflow \
                         -Wp,-D_FORTIFY_SOURCE=2 \
                         -ffast-math \
                         -fno-common \
                         -fdiagnostics-show-option \
                         -fno-strict-aliasing \
                         -fvisibility=hidden \
                         -ffunction-sections \
                         -fdata-sections \
                       ])

CC_CHECK_LDFLAGS_APPEND([ \
                          -Wl,--as-needed \
                          -Wl,--gc-sections \
                        ])

AC_DEFINE_UNQUOTED([KU_VISIBLE], [__attribute__((visibility("default")))], [Export symbol])

# GETTEXT_PACKAGE=$PACKAGE_NAME
# AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [Gettext Package])
# AC_SUBST(GETTEXT_PACKAGE)
# IT_PROG_INTLTOOL([$INTLTOOL_REQUIRED])

PKG_PROG_PKG_CONFIG([$PKGCONFIG_REQUIRED])

AC_CONFIG_FILES([
    Makefile
])
#    po/Makefile.in
AC_OUTPUT
AC_MSG_RESULT([
    $PACKAGE_NAME $VERSION
    ========

    prefix:                 ${prefix}
    exec_prefix:            ${exec_prefix}
    sysconfdir:             ${sysconfdir}
    libdir:                 ${libdir}
    includedir:             ${includedir}

    compiler:               ${CC}
    cflags:                 ${CFLAGS}
    ldflags:                ${LDFLAGS}
])
