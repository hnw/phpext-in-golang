# phpext-in-golang

PHP extension written in Go

## INSTALL

```
git clone https://github.com/hnw/phpext-in-golang.git
cd phpext-in-golang
phpize
perl -i.bak -pe 's/^enable_static=no/enable_static=yes/;s/enable_shared=yes/enable_shared=no/' ./configure
./configure
make
mv modules/goext.a modules/libgoext.a
go build -buildmode=c-shared -o modules/goext.so goext.go
install modules/goext.so $(php-config --extension-dir)
```

After install, add these lines to your php.ini

```ini
extension=goext.so
```

## SYSTEM REQUIREMENTS

- PHP 7.0.0+
- Mac OS X 10.x

## USAGE

```php
<?php
var_dump(fib(30));
var_dump(php_version());
```

## LICENSE

The MIT License

Copyright (c) 2015 Yoshio HANAWA

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
