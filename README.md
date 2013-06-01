PHP Happiness
=============
PHP Happiness sets out to correct many of the evils of PHP using the C / C++
preprocessor language. To use PHP Happiness, simply add C-style include
directives to your PHP code and run any standard macro processor on the files.

Here's an example of a function using the strict-argument type macros:

    FUNCTION(concatenate, REQ(string, $leftstring); REQ(string, $rightstring))
    {
        return $leftstring . $rightstring;
    }
    ENDFUNCTION

And here are a couple of examples using `cpp` on Linux to pre-process the code
before piping it into the PHP interpreter.

    phphappiness% cpp -P -I. examples/argtypes.php | php
    The password for 'jameseric' has been changed to 'hunter2'!
    PHP Fatal error:  Uncaught exception 'InvalidArgumentException' with message 'Argument 1 is not integer.' in -:2
    Stack trace:
    #0 -(8): passwd('1001', 'bobbytables', 'lulzsec')
    #1 {main}
      thrown in - on line 2

    phphappiness% cpp -P -I. examples/phphappiness.php | php
    var_dump(array_fill(0, 1, 'zazoo'));
    array(1) {
      [0]=>
      string(5) "zazoo"
    }

    var_dumpp(array_fill(0, 0, 'simba'));
    array(0) {
    }

To see what various macros are available, please review the header files for
full documentation.

License
-------

Unless you need an explicit license, consider this code public domain.
Otherwise, refer to the LICENSE file for the full text of the BSD License.

FAQ
---

**Q:** Why would you do such a thing?

**A:** Because I can! What started out as a perverse thought-experiment with
[dririan](https://github.com/dririan) has been made a reality.
