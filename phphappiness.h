/* Fixes for issues described on http://phpsadness.com/.
 *
 * Most of the macros in this file are simple function replacements, so
 * although the behaviour of a function may change, the calls need not be
 * modified.
 */
#ifndef PHPHAPPINESS_H
#define PHPHAPPINESS_H

// Issue 48 (http://phpsadness.com/sad/48):
// Function naming is inconsistent with "to" and "2". Now you can use either.

#define stream_copy_2_stream stream_copy_to_stream
#define str2lower strtolower
#define str2time strtotime
#define str2upper strtoupper
#define unix2jd unixtojd

#define bintohex bin2hex
#define degtorad deg2rad
#define radtoreg rad2deg
#define hextobin hex2bin
#define iptolong ip2long
#define longtoip long2ip
#define nltobr nl2br

// Issue 43 (http://phpsadness.com/sad/43):
// The array_fill() function doesn't allow length 0

#define array_fill(s, n, v) (!n ? array() : array_fill(s, n, v))

#endif
