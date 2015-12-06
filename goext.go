package main

/*
#cgo LDFLAGS: -L${SRCDIR}/modules -lgoext
extern void get_module();
#include "php.h"
#include "php_ini.h"
#include "zend_interfaces.h"

extern char *z_strval(zval zv);
*/
import "C"
import "runtime"

//export fib
func fib(n int) int {
	if n < 2 {
		return n
	}
	return fib(n-2) + fib(n-1)
}

//export go_version
func go_version() *C.char {
	return C.CString(runtime.Version())
}

//export php_version
func php_version() *C.char {
	var version_string *C.char
	var retval C.zval
	C.zend_call_method(nil, nil, nil,
		C.CString("phpversion"),
		C.size_t(len("phpversion")),
		&retval, 0, nil, nil)
	version_string = C.CString("PHP " + C.GoString(C.z_strval(retval)))
	return version_string
}

func main() {
	C.get_module() /* PHP extensionの*.oをリンクするためのトリック */
}
