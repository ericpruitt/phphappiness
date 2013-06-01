/* Wraps common functions so exceptions are raised when something goes wrong.
 */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define json_encode(v) (((($_ = json_encode(v)) or true) and \
    (json_last_error() ? \
    eval("throw new DomainException('JSON error #".json_last_error()."');") : \
    $_) and false) ?: $_)

#define json_decode(v) (((($_ = json_decode(v)) or true) and \
    (json_last_error() ? \
    eval("throw new DomainException('JSON error #".json_last_error()."');") : \
    $_) and false) ?: $_)

#endif
