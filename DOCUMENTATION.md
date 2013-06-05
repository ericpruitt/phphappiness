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
