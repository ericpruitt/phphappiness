/* Wraps common functions so exceptions are raised when something goes wrong.
 */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define THROW(type, message) (eval("throw new ".#type."(\"".message."\");"))

#define THROWER(function, args, test, e) (((($_ = function args) or true) and \
    (($__ = test) ? THROW(e, #test . " error $__") : \
    false)) ?: $_)

//                               JSON Functions

#if PHP_VERSION_ID < 50303
#define JSON_ERROR_UTF8 5
#endif

# define JSON_THROWER(fname, ...) ( \
($_ = fname(__VA_ARGS__)) !== null ? $_ : \
(($__ = json_last_error()) ? ( \
    ($__ == JSON_ERROR_DEPTH ? THROW(OverflowException, \
        "The maximum stack depth has been exceeded") : \
\
    ($__ == JSON_ERROR_STATE_MISMATCH ? THROW(UnexpectedValueException, \
        "Invalid or malformed JSON") : \
\
    ($__ == JSON_ERROR_CTRL_CHAR ? THROW(UnexpectedValueException, \
        "Control character error, possibly incorrectly encoded") : \
\
    ($__ == JSON_ERROR_SYNTAX ? THROW(UnexpectedValueException, \
        "Syntax error") : \
\
    ($__ == JSON_ERROR_UTF8 ? THROW(UnexpectedValueException, \
        "Malformed UTF-8 characters, possibly incorrectly encoded") : \
\
    THROW(Exception, \
        "Unknown JSON error"))))))) : $_ \
))

#define json_encode(...) JSON_THROWER(json_encode, __VA_ARGS__)
#define json_decode(...) JSON_THROWER(json_decode, __VA_ARGS__)

//                               PCRE Functions

#define preg_match(...) \
    THROWER(preg_match, (__VA_ARGS__), preg_last_error(), RuntimeException)

#define preg_match_all(...) \
    THROWER(preg_match_all, (__VA_ARGS__), preg_last_error(), RuntimeException)

#define preg_match_replace(...) \
    THROWER(preg_match_all, (__VA_ARGS__), preg_last_error(), RuntimeException)

//                              Socket Functions

// Generic macro for socket functions to test whether or not an error occurred.
#define SOCKET_THROWER(fname, ...) ($_ = @fname(__VA_ARGS__) ?: \
    (array($__ = socket_last_error(), $__ = socket_strerror($__), \
    socket_clear_error(), THROW(Exception, $__))))

#define socket_accept(...) SOCKET_THROWER(socket_accept, __VA_ARGS__)
#define socket_bind(...) SOCKET_THROWER(socket_bind, __VA_ARGS__)
#define socket_connect(...) SOCKET_THROWER(socket_connect, __VA_ARGS__)
#define socket_create_listen(...) SOCKET_THROWER(socket_create_listen, __VA_ARGS__)
#define socket_create_pair(...) SOCKET_THROWER(socket_create_pair, __VA_ARGS__)
#define socket_create(...) SOCKET_THROWER(socket_create, __VA_ARGS__)
#define socket_listen(...) SOCKET_THROWER(socket_listen, __VA_ARGS__)
#define socket_read(...) SOCKET_THROWER(socket_read, __VA_ARGS__)
#define socket_recv(...) SOCKET_THROWER(socket_recv, __VA_ARGS__)
#define socket_recvfrom(...) SOCKET_THROWER(socket_recvfrom, __VA_ARGS__)
#define socket_select(...) SOCKET_THROWER(socket_select, __VA_ARGS__)
#define socket_send(...) SOCKET_THROWER(socket_send, __VA_ARGS__)
#define socket_sendto(...) SOCKET_THROWER(socket_sendto, __VA_ARGS__)
#define socket_set_option(...) SOCKET_THROWER(socket_set_option, __VA_ARGS__)
#define socket_write(...) SOCKET_THROWER(socket_write, __VA_ARGS__)

#endif
