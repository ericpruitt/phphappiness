/* Contexts are wrappers around closures to isolate the effects of code within.
 * The are presently two main context types. The vanilla BEGINCONTEXT /
 * ENDCONTEXT macros wrap a block of code in a closure definition and execute
 * it, but they also makes all currently scoped variables accessible to the
 * closure without having to explicitly specify a "use" clause.  The
 * LOGLEVELCONTEXT macro is used to define an error_reporting level for a block
 * of code and attempts ensure the error_reporting level is reset back to its
 * original value regardless of whether or not the code within throws an
 * exception.
 */
#ifndef CONTEXTS_H
#define CONTEXTS_H

#define BEGINCONTEXT \
    $_ = get_defined_vars(); \
    $_ = function () use ($_) { \
        foreach ($_ as $_ => $__) { \
            $$_ = $__; \
        } \
        do

#define ENDCONTEXT while(0); }; $_();

#define LOGLEVELCONTEXT(loglevel) $__ = error_reporting(); \
    error_reporting(loglevel); BEGINCONTEXT

#define ENDLOGLEVELCONTEXT \
    while(0); }; try { \
        $_(); \
        error_reporting($__); \
    } catch (Exception $e) { \
        error_reporting($__); \
        throw $e; \
    }

#define SILENCE LOGLEVELCONTEXT(~E_ALL)
#define ENDSILENCE ENDLOGLEVELCONTEXT

#endif
