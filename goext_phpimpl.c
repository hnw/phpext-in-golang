/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_goext.h"

/* Go側でexportした関数のプロトタイプ宣言 */
extern int fib(int n);
extern char *go_version(void);
extern char *php_version(void);

/* Go側から呼んでもらうため。本来ならヘッダファイルに入れて両方から呼び出すべき */
extern char *z_strval(zval zv);

/* If you declare any globals in php_goext.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(goext)
*/

/* True global resources - no need for thread safety here */
static int le_goext;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("goext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_goext_globals, goext_globals)
    STD_PHP_INI_ENTRY("goext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_goext_globals, goext_globals)
PHP_INI_END()
*/
/* }}} */

char *z_strval(zval zv) {
    return Z_STRVAL(zv);
}

/* {{{ proto integer fib(integer n)
   Return a Fibo number */
PHP_FUNCTION(fib)
{
	int n;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &n) == FAILURE) {
		return;
	}

	RETURN_LONG(fib(n));
}
/* }}} */

/* {{{ proto integer fib(integer n)
   Return a Fibo number */
PHP_FUNCTION(php_version)
{
	RETURN_STRING(php_version());
}
/* }}} */

/* {{{ php_goext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_goext_init_globals(zend_goext_globals *goext_globals)
{
	goext_globals->global_value = 0;
	goext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(goext)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(goext)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(goext)
{
#if defined(COMPILE_DL_GOEXT) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(goext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(goext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "goext support", "enabled");
	php_info_print_table_row(2, "Go version", go_version());
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ goext_functions[]
 *
 * Every user visible function must have an entry in goext_functions[].
 */
const zend_function_entry goext_functions[] = {
	PHP_FE(fib,	NULL)
	PHP_FE(php_version, NULL)
	PHP_FE_END	/* Must be the last line in goext_functions[] */
};
/* }}} */

/* {{{ goext_module_entry
 */
zend_module_entry goext_module_entry = {
	STANDARD_MODULE_HEADER,
	"goext",
	goext_functions,
	PHP_MINIT(goext),
	PHP_MSHUTDOWN(goext),
	PHP_RINIT(goext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(goext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(goext),
	PHP_GOEXT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GOEXT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(goext)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
