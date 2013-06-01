/* Wraps common functions so exceptions are raised when something goes wrong.
 */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define THROW(type, message) (eval("throw new ".#type."(\"".message."\");"))

#define THROWER(function, args, test, e) (((($_ = function args) or true) and \
    (($__ = test) ? THROW(e, #test . " error $__") : \
    false)) ?: $_)

#define json_encode(v) \
    THROWER(json_encode, (__VA_ARGS__), json_last_error(), DomainException)

#define json_decode(...) \
    THROWER(json_decode, (__VA_ARGS__), json_last_error(), DomainException)

#define preg_match(...) \
    THROWER(preg_match, (__VA_ARGS__), preg_last_error(), RuntimeException)

#define preg_match_all(...) \
    THROWER(preg_match_all, (__VA_ARGS__), preg_last_error(), RuntimeException)

#define preg_match_replace(...) \
    THROWER(preg_match_all, (__VA_ARGS__), preg_last_error(), RuntimeException)

#endif
