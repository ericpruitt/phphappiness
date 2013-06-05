#ifndef ARGTYPES_H
#define ARGTYPES_H

#define float double
#define real double

#define REQ(type, varname) \
    varname = func_get_arg($_++); \
    if(($__ = gettype(varname)) !== #type) { \
        if ($__ !== #type and \
         !((#type === "float" or #type === "real" or #type === "double") and \
          ($__ === "integer" or $__ === "double"))) { \
            $message = "Got $__ for argument $_ but expected ".#type; \
            throw new InvalidArgumentException($message); \
        } \
    }

#define FUNCTION(name, argasserts) \
    function name() \
    { \
        $_ = 0; \
        argasserts; \
        do

#define ENDFUNCTION while(0); }

#endif
