/* Wraps common functions so exceptions are raised when something goes wrong.
 */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define THROW(type, message) (eval("throw new ".#type."(\"".message."\");"))

#define json_encode(v) (((($_ = json_encode(v)) or true) and \
    (($__ = json_last_error()) ? THROW(DomainException, "JSON Error #$__") : \
    false)) ?: $_)

#define json_decode(v) (((($_ = json_decode(v)) or true) and \
    (($__ = json_last_error()) ? THROW(DomainException, "JSON Error #$__") : \
    false)) ?: $_)

#endif
