dnl Process this file with autoconf to produce a configure script.

AC_INIT(playtzx.c, [0.12d])
AM_CONFIG_HEADER(config.h)

dnl Use automake to produce `Makefile.in'
AM_INIT_AUTOMAKE

dnl Checks for programs.
AC_PROG_CC

dnl Check for PortAudio
AC_CHECK_LIB([portaudio], [Pa_Initialize], [], [AC_MSG_ERROR([Can't find or link to the PortAudio library.])])

dnl Do we want lots of warning messages?
AC_MSG_CHECKING(whether lots of warnings requested)
AC_ARG_ENABLE(warnings,
[  --enable-warnings       give lots of warnings if using gcc],
if test "$enableval" = yes; then
    warnings=yes;
else
    warnings=no;
fi,
warnings=no)
AC_MSG_RESULT($warnings)

dnl If it appears we're using gcc as our compiler, turn on warnings
if test "$ac_cv_prog_cc_g" = yes; then
    CFLAGS="$CFLAGS -Wall -Wno-unused-result"
    dnl And possibly lots of warnings
    if test "$warnings" = yes; then
        CFLAGS="$CFLAGS -Wstrict-prototypes -Wmissing-prototypes -Winline -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Waggregate-return -W -Wsign-compare"
    fi
fi

AC_OUTPUT(Makefile)
