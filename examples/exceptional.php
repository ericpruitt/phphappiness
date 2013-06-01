<?php
#include <exceptions.h>

echo "var_dump(json_decode('\"Succeed\"'));\n";
var_dump(json_decode('"Succeed"'));

echo "preg_match('/(?:\D+|<\d+>)*[!?]/', 'foobar foobar foobar');\n";
preg_match('/(?:\D+|<\d+>)*[!?]/', 'foobar foobar foobar');

echo "\njson_decode('\"Fail');\n";
json_decode('"Fail');
