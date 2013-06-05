Macro Documentation
===================

This document contains all of the defined macros defined in the various
headers, their functions, and usage examples.

argtypes.h
----------

This header provides macros for strict PHP argument type enforcement. Due to
the implementation of this macro, function definitions are tad different. To
declare a function with strictly typed arguments, one must use the `FUNCTION`
macro, and each of the function arguments is defined with the `REQ` macro which
expects the variable type and variable name as parameters. The end of the
function then be terminated with the `ENDFUNCTION` macro. Here's a simple
function that requires strings for concatenation:

    FUNCTION(concatenate, REQ(string, $leftstring); REQ(string, $rightstring))
    {
        return $leftstring . $rightstring;
    }
    ENDFUNCTION

Note that the function arguments must be separated with semicolons instead of
commas. Calls to the function remain the same, and any attempts to call the
function with invalid types will result in an `InvalidArgumentException` being
thrown:

    php> echo concatenate('Left', 'Right');
    LeftRight
    php> echo concatenate(100, 200);
    PHP Fatal error:  Uncaught exception 'InvalidArgumentException' with me...
    Stack trace:
    #0 documentation.php(10): concatenate(100, 200)
    #1 /home/jameseric/programming/phphappiness/ppp(40): require_once('docu...
    #2 {main}

When specifying type restrictions for numerics, integers will be accepted for
functions that specify "float", "double", or "real" as the argument type.
However, the reverse is not true: if "integer" is specified as the argument
type, floating point numbers will be rejected by the function. Take the
following function for example:

    FUNCTION(updateStatistics, REQ(int, $userid); REQ(double, $average))
    {
        // ...
    }
    ENDFUNCTION

Calling the function like `updateStatistics(100, 7.2)` would work, and so would
calling the function like `updateStatistics(100, 9)`. Although `9` is an
integer, it will still be accepted in place of a float. When calling the
function like `updateStatistics(100.0, 7.2)`, an `InvalidArgumentException`
exception will be raised because `100.0` is floating point type.

contexts.h
----------

Contexts are wrappers around closures to isolate the effects of code within.
The are presently two main context types.

### BEGINCONTEXT and ENDCONTEXT ###

The `BEGINCONTEXT` and `ENDCONTEXT` macros wrap a block of code in a closure
definition and execute it, but they also make all currently scoped variables
accessible to the closure without having to explicitly specify a "use" clause.
In block below, a variable is defined outside a context block, updated inside
the context and its value displayed inside the context block and outside the
context block:

    <?php
    $var = 1000;
    BEGINCONTEXT
    {
        $var = 2000;
        echo "Inside context: \$var = $var\n";
    }
    ENDCONTEXT
    echo "Outside context: \$var = $var\n";

Executing this code generates the following output:

    Inside context: $var = 2000
    Outside context: $var = 1000

### LOGLEVELCONTEXT and ENDLOGLEVELCONTEXT ###

The `LOGLEVELCONTEXT` macro is used to define an error_reporting level for a
block of code and attempts ensure the error_reporting level is reset back to
its original value regardless of whether or not the code within throws an
exception. It can be used to temporarily increase or decrease PHP's verbosity.
The example below temporarily silences warnings caused by dividing by zero:

    LOGLEVELCONTEXT(~E_ALL)
    {
        echo 1 / 0, "\n";
    }
    ENDLOGLEVELCONTEXT

There is also the convenience macro `SILENCE` and its companion `ENDSILENCE`
which are simply shorthand for setting the error reporting level to `~E_ALL`.
The example below and the example above are equivalent:

    SILENCE
    {
        echo 1 / 0, "\n";
    }
    ENDSILENCE

exceptions.h
------------

The exceptions header wraps various functions so that exceptions are thrown
when an error occurs. Here is a list of the functions that have been wrapped to
throw exceptions:

### JSON Functions ###

    json_decode  json_encode

### PCRE Functions ###

    preg_match  preg_match_all  preg_match_replace

### Socket Functions ###

    socket_accept         socket_create_pair  socket_recv      socket_sendto
    socket_bind           socket_create       socket_recvfrom  socket_set_option
    socket_connect        socket_listen       socket_select    socket_write
    socket_create_listen  socket_read         socket_send
