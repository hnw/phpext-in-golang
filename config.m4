dnl $Id$
dnl config.m4 for extension goext

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(goext, for goext support,
dnl Make sure that the comment is aligned:
dnl [  --with-goext             Include goext support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(goext, whether to enable goext support,
Make sure that the comment is aligned:
[  --enable-goext           Enable goext support])

if test "$PHP_GOEXT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-goext -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/goext.h"  # you most likely want to change this
  dnl if test -r $PHP_GOEXT/$SEARCH_FOR; then # path given as parameter
  dnl   GOEXT_DIR=$PHP_GOEXT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for goext files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GOEXT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GOEXT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the goext distribution])
  dnl fi

  dnl # --with-goext -> add include path
  dnl PHP_ADD_INCLUDE($GOEXT_DIR/include)

  dnl # --with-goext -> check for lib and symbol presence
  dnl LIBNAME=goext # you may want to change this
  dnl LIBSYMBOL=goext # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GOEXT_DIR/$PHP_LIBDIR, GOEXT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GOEXTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong goext lib version or lib not found])
  dnl ],[
  dnl   -L$GOEXT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GOEXT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(goext, goext_phpimpl.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
