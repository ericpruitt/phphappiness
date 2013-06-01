<?php
#include <argtypes.h>

FUNCTION(passwd, REQ(integer, $id); REQ(string, $username); REQ(string, $pass))
{
    echo "The password for '$username' has been changed to '$pass'!\n";
}
ENDFUNCTION

passwd(1000, "jameseric", "hunter2");
passwd("1001", "bobbytables", "lulzsec");
