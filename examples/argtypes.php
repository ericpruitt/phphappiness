<?php
#include <argtypes.h>

FUNCTION(passwd, REQ(integer, $id); REQ(string, $username); REQ(string, $pass))
{
    echo "The password for '$username' has been changed to '$pass'!\n";
}
ENDFUNCTION

passwd(1000, "jameseric", "hunter2");

try {
    passwd("1001", "bobbytables", "lulzsec");
} catch (InvalidArgumentException $e) {
    echo 'passwd("1001", "bobbytables", "lulzsec") failed as expected.', "\n";
}

FUNCTION(multiply, REQ(float, $a); REQ(float, $b))
{
    return $a * $b;
}
ENDFUNCTION

echo multiply(2.1, 2), "\n";
