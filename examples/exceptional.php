<?php
#include <exceptions.h>

echo "var_dump(json_decode('\"Succeed\"'));\n";
var_dump(json_decode('"Succeed"'));

echo "\njson_decode('\"Fail');\n";
json_decode('"Fail');
