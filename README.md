PHP Happiness
=============

PHP Happiness sets out to correct many of the evils of PHP using the C / C++
preprocessor language and a stream wrapper to transform code behind the scenes.
If your initial reaction to that statement if "WTF?," please read the FAQ at
the bottom of this document.

Introduction
------------

Various macros are defined in the header files distributed with PHP Happiness,
and they are located under `PHPHappiness/headers` relative to the repository
root. Some of the macros simply wrap existing functions to change their
behaviour whereas others are used to supplement existing syntax. For full
documentation of the macros and function overrides, review the header files'
contents, but a few examples will be covered here.

### Parameter Type Enforcement ###

Functions with strictly enforced parameter types can be created using the
FUNCTION macro, used for declaring the function, and the REQ macro, used for
specifying type restrictions. In the this example, the function `multiply` is
created with strict enforcement for float parameters:

    <?php
    FUNCTION(multiply, REQ(float, $a); REQ(float, $b))
    {
        return $a * $b;
    }
    ENDFUNCTION

The result when executed with valid parameters:

    php> multiply(2.5, 7.3);
    18.25

The result when executed with invalid parameters:

    php> multiply("2.5", 7.3);
    PHP Fatal error:  Uncaught exception 'InvalidArgumentException' with
                      message 'Got string for argument 1 but expected float' in
                      demo:2

### Missing Exceptions ###

Normally, functions like `json_decode` and `preg_match` fail silently, and in
the case of `json_decode`, it is not possible to discern a legitimate return
value from an error without explicitly checking `json_last_error` each time.
The `exceptions.h` header file wraps many functions that normally fail without
exceptions to throw errors on exceptional conditions.

When `json_decode` fails, `null` is returned, but `null` may also be returned
when it succeeds if the encoded string is simply "null". Here is failure in
standard PHP:

    php> json_decode('noll');
    null;

This is what happens when the invalid value is decoded with using the macro
provided by PHP Happiness:

    php> json_decode('noll');
    PHP Fatal error:  Uncaught exception 'DomainException' with message
                      'json_last_error() error 4' in demo(2) : eval()'d code:1

Installation
------------

PHP Happiness requires a C preprocessor. It has only been tested with the GCC C
preprocessor, but it may work with others. Aside from that, everything else is
vanilla PHP and simply need only be copied where it can be accessed by
applications that depend on it.

PHP Happiness is PSR-0 compliant, but the `CPPStreamWrapper.php` file is
generally best explicitly imported with a `require_once` call to register the
stream wrappers for the `cpp://` and `php://` schemes. Once the stream wrapper
has been registered, code dependent on the PHP Happiness macros can be included
with a call like `include("phph://example.php")`. Files using the `phph` scheme
will automatically have all headers in the `PHPHappiness/headers` folder
immediately available along with any other header files found in the PHP
includes folders and `./headers` relative to the calling script. If the `cpp`
scheme is used, headers must be explicitly loaded using the `#include` C
preprocessor directive. The C preprocessor will search all the directories
defined in the include path, `./headers` relative to the calling script and the
bundled PHP Happiness headers folder for header files.

There is also a helper script included with PHP Happiness named `ppp` which
stands for PHP Happiness Pre-processor. Run `ppp -h` for full usage
information, but the general syntax is simple `ppp $FILENAME` where `$FILENAME`
is the path to a PHP script dependent on PHP Happiness:

    phphappiness% chmod +x ppp
    phphappiness% ./ppp examples/argtypes.php 
    The password for 'jameseric' has been changed to 'hunter2'!
    passwd("1001", "bobbytables", "lulzsec") failed as expected.
    4.2

FAQ
---

**Q:** Why would you do such a thing?

**A:** Because I can! What started out as a perverse thought-experiment with
[dririan](https://github.com/dririan) has been made a reality.
