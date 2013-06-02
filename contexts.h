/* Contexts are wrappers around closures to isolate the effects of code within.
 * The are presently two context types: a vanilla context that does nothing
 * more than wrap a block of code in a closure definition and execute it and a
 * log-level context. The LOGLEVELCONTEXT is used to define an error_reporting
 * level for a block of code and attempts ensure the error_reporting level is
 * reset back to its original value regardless of whether or not the code
 * within throws an exception.
 */
#ifndef CONTEXTS_H
#define CONTEXTS_H

#define BEGINCONTEXT $_ = function()
#define ENDCONTEXT ; $_();

#define LOGLEVELCONTEXT(loglevel) $_ = error_reporting(); \
    error_reporting(loglevel); $__ = function ()

#define ENDLOGLEVELCONTEXT \
    ; try { \
        $__(); \
        error_reporting($_); \
    } catch (Exception $e) { \
        error_reporting($_); \
        throw $e; \
    }

#define SILENCE LOGLEVELCONTEXT(~E_ALL)
#define ENDSILENCE ENDLOGLEVELCONTEXT

#endif
