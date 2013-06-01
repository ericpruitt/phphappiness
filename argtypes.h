/* This header provides macros for strict PHP argument type enforcement. Due to
 * the implementation of this macro, function definitions are tad different. To
 * declare a function with strictly typed arguments, you must use the FUNCTION
 * macro, and each of the function arguments is defined with the REQ macro
 * which expects the variable type and variable name. The end of the function
 * must also be terminated with the ENDFUNCTION macro. Here's a simple function
 * that requires strings for concatenation:
 *
 *  FUNCTION(concatenate, REQ(string, $leftstring); REQ(string, $rightstring))
 *  {
 *      return $leftstring . $rightstring;
 *  }
 *  ENDFUNCTION
 *
 * Note that the function arguments must be separated with semicolons instead
 * of commas. Calls to the function remain the same, and any attempts to call
 * the function with invalid types will result in an InvalidArgumentException
 * being thrown.
 */
#ifndef ARGTYPES_H
#define ARGTYPES_H

#define REQ(type, varname) \
    varname = func_get_arg($_++); \
    if(gettype(varname) !== #type) \
        throw new InvalidArgumentException("Argument $_ is not ".#type.".");

#define FUNCTION(name, argasserts) \
    function name() \
    { \
        $_ = 0; \
        argasserts; \
        do

#define ENDFUNCTION while(0); }

#endif
