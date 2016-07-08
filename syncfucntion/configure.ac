#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([jelly_sync_input.c])
AC_CONFIG_HEADERS([config.h])

# Check host
AC_CANONICAL_HOST
AS_CASE([$host],
		[avr-*-*], [],
		[AC_MSG_ERROR([Unsupported host. Use --host=avr option])]
	)

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_UINT32_T

# Checks for library functions.

# Checks for tools
AC_CHECK_TOOL([OBJCOPY], [objcopy], [:])
AC_CHECK_TOOL([OBJDUMP], [objdump], [:])

# Check for MCU
AC_ARG_VAR([MCU_TARGET], [select target MCU. Default = attiny85])
AC_MSG_CHECKING([for selected MCU])
AS_IF([test "x$MCU_TARGET" = x],
		[MCU_TARGET="attiny85"]
		[AC_MSG_RESULT([$MCU_TARGET (override with env. variable MCU_TARGET)])]
		,
		[AC_MSG_RESULT([$MCU_TARGET])]
	)

# Checks for programs
AC_ARG_VAR([AVRDUDE_MCU], [select target MCU for avrdude. Default = t85])
AC_ARG_VAR([AVRDUDE_PROGRAMMER], [select programmer options for avrdude. Default = -c avrispmkII -P usb])
AC_CHECK_PROG([AVRDUDE_CHECK], [avrdude], [yes])
AS_IF([test "x$AVRDUDE_CHECK" = xyes],
		[ AC_SUBST([AVRDUDE], [avrdude]) ]
		[AC_MSG_CHECKING([for avrdude selected MCU])]
		[AS_IF([test "x$AVRDUDE_MCU" = x],
			[AVRDUDE_MCU="t85"]
			[AC_MSG_RESULT([$AVRDUDE_MCU (override with env. variable AVRDUDE_MCU)])]
			,
			[AC_MSG_RESULT([$AVRDUDE_MCU])],
		)]
		[AC_MSG_CHECKING([for avrdude programmer options])]
		[AS_IF([test "x$AVRDUDE_PROGRAMMER" = x],
			[AVRDUDE_PROGRAMMER="-c avrispmkII -P usb"]
			[AC_MSG_RESULT([$AVRDUDE_PROGRAMMER (override with env. variable AVRDUDE_PROGRAMMER)])]
			,
			[AC_MSG_RESULT([$AVRDUDE_PROGRAMMER])],
		)]
		,
		[ AC_MSG_WARN([avrdude not found. You will not be able to upload this program to any chip.])]
	)
AM_CONDITIONAL([WITH_AVRDUDE], [test "x$AVRDUDE_CHECK" = xyes])

AC_OUTPUT([Makefile])
