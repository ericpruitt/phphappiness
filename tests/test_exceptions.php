<?php
require_once('attotest.php');

class ExceptionTests extends AttoTest
{

    public function test_socketExceptionsAreThrown()
    {
        try {
            socket_create(-999, -999, -999);
        } catch (Exception $e) {
            // Nothing to do here, this is what we want.
            return;
        }

        throw new Exception("Exception not thrown for bogus socket_create call.");
    }

    public function test_PCREExceptionsAreThrown()
    {
        try {
            preg_match('/(?:\D+|<\d+>)*[!?]/', 'foobar foobar foobar');
        } catch (Exception $e) {
            try {
                preg_match_all('/(?:\D+|<\d+>)*[!?]/', 'foobar foobar foobar');
            } catch (Exception $e) {
                try {
                    $er = error_reporting();
                    error_reporting(~E_ALL);
                    preg_replace('(?:\D+|<\d+>)*[!?]/', 'x', 'x');
                    error_reporting($er);
                } catch (Exception $e) {
                    error_reporting($er);
                    return;
                }
            }
        }

        throw new Exception("PCRE Exception not thrown.");
    }

    public function test_JSONExceptionsAreThrown()
    {
        try {
            $j = json_decode('noll') != json_decode('null');
        } catch (Exception $e) {
            try {
                $j = json_encode(array('o', "invalid UTF data:\xc3\x28", 'y'));
            } catch (Exception $e) {
                return;
            }
        }

        throw new Exception('Exception not thrown while decoding data.');
    }
}

$exceptiontests = new ExceptionTests();
$exceptiontests->runTests();
