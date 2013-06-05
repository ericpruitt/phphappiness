<?php
require_once('attotest.php');

class ArgtypesTests extends AttoTest
{
    public function test_numberArgumentValidation_failure()
    {
        try {
            // Should fail because 7.0 is a double.
            requireNumbers(7.0, 0.0, 0.0, 0.0);
        } catch (InvalidArgumentException $e) {
            return true;
        }

        throw new Exception('InvalidArgumentException not thrown.');
    }

    public function test_numberArgumentValidation_success()
    {
        requireNumbers(7, 0, 0, 0);

        // double, float, and real should all accept integer and floating-point
        // values.
        requireNumbers(0, 7, 0, 0);
        requireNumbers(0, 7.0, 0, 0);

        requireNumbers(0, 0, 7, 0);
        requireNumbers(0, 0, 7.0, 0);

        requireNumbers(0, 0, 0, 7);
        requireNumbers(0, 0, 0, 7.0);
    }

    public function test_generalArgumentValidation_failure()
    {
        try {
            requireStrings(1, 1);
        } catch (InvalidArgumentException $e) {
            try {
                requireStrings("1", 1);
            } catch (InvalidArgumentException $e) {
                try {
                    requireStrings(1, "1");
                } catch (InvalidArgumentException $e) {
                    return true;
                }
            }
        }

        throw new Exception('InvalidArgumentException not thrown.');
    }

    public function test_generalArgumentValidation_success()
    {
        requireStrings('This is a string,', 'and so is this.');
        requireStrings('This is a string,', 'and so is this.');
    }
}

FUNCTION(requireStrings, REQ(string, $a); REQ(string, $b))
{
    assertEqual(gettype($a), 'string');
    assertEqual(gettype($b), 'string');
}
ENDFUNCTION

FUNCTION(requireNumbers, REQ(integer, $a); REQ(float, $b); REQ(double, $c); REQ(real, $d))
{
    assertEqual(gettype($a), 'integer');
    assertTrue(gettype($b) == 'integer' or gettype($b) == 'double');
    assertTrue(gettype($c) == 'integer' or gettype($c) == 'double');
    assertTrue(gettype($d) == 'integer' or gettype($d) == 'double');
}
ENDFUNCTION

$argtypetests = new ArgtypesTests();
$argtypetests->runTests();
