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
