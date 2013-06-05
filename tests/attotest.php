<?php

class AttoTest
{
    protected function setUp()
    {
        // Should be provided by descendant classes
    }

    function runTests()
    {
        $initial_reporting = error_reporting();

        foreach (get_class_methods($this) as $method) {
            if (stripos($method, 'test_') === 0) {
                $this->setUp();
                print("Running $method...");
                flush();
                try {
                    $this->$method();
                    print(" OK\n");
                } catch (Exception $exc) {
                    print("\n$exc\n");
                }
            }
        }

        error_reporting($initial_reporting);
    }
}

function assertEqual($a, $b, $strict = false)
{
    if (($strict and !($a === $b)) or !($a == $b)) {
        throw new Exception('Values not equal!');
    }
}

function assertFalse($falsehood)
{
    if ($falsehood) {
        throw new Exception('Value not false!');
    }
}

function assertTrue($truth)
{
    if (!$truth) {
        throw new Exception('Value not true!');
    }
}
