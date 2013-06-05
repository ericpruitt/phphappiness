<?php
require_once('attotest.php');

class ContextTests extends AttoTest
{
    public function test_contextVariableAccess()
    {
        $a = 1000;
        $b = 2000;
        $c = 3000;
        $d = &$c;

        BEGINCONTEXT
        {
            assertEqual($a, 1000);
            assertEqual($b, 2000);
            assertEqual($c, 3000);
            assertEqual($c, $d);
            $a = -$a;
            $b = -$b;
            $c = -$c;
            $d = 999;
        }
        ENDCONTEXT

        assertEqual($a, 1000);
        assertEqual($b, 2000);
        assertEqual($c, 3000);

        $c = -50;
        assertEqual($c, $d);
    }

    public function test_logLevelChanges()
    {
        $original = error_reporting();

        try {
            error_reporting(E_ALL);
            LOGLEVELCONTEXT(~E_ALL)
            {
                assertEqual(error_reporting(), ~E_ALL);
                throw new Exception("XXX");
            }
            ENDLOGLEVELCONTEXT

        } catch (Exception $e) {
            assertTrue(error_reporting(), E_ALL);
            try {
                error_reporting(E_ALL);
                SILENCE
                {
                    assertEqual(error_reporting(), ~E_ALL);
                    throw new Exception("XXX");
                }
                ENDSILENCE
            } catch (Exception $e) {
                assertTrue(error_reporting(), E_ALL);
            }
        }

        error_reporting($original);
    }
}

$contextstests = new ContextTests();
$contextstests->runTests();
