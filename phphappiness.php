<?php
namespace PHPHappiness;

class CPPStreamWrapper
{
    protected $_process;
    protected $_openened_path;

    public function stream_open($path, $mode, $options, &$opened_path)
    {
        if (!preg_match('/^rb?$/', $mode)) {
            throw InvalidArgumentException('Access mode must be read-only.');
        }

        // Strip the scheme off the path
        $parsedpath = parse_url($path);
        $path = $parsedpath['host'];

        // When STREAM_USE_PATH is set, all files in the include path should be
        // searched. To avoid duplicating the search logic already implemented
        // in PHP, use fopen to resolve the path.
        if ($options & STREAM_USE_PATH and !is_file($path)) {
            $handle = fopen($path, "r", true);
            if (!$handle) {
                throw new Exception("Could open path '$path'.");
            }

            $metadata = stream_get_meta_data($handle);
            fclose($handle);
            $path = $metadata['uri'];
        }

        // With phph files, assume all discovered headers should be included by
        // the pre-processor automatically.
        $autoinclude = $parsedpath['scheme'] === 'phph';

        $this->_process = preprocess_file($path, $autoinclude);
        $this->opened_path = $opened_path = $path;

        return true;
    }

    public function stream_read($count)
    {
        return fread($this->_process->stdout, $count);
    }

    public function stream_tell()
    {
        return ftell($this->_process->stdout);
    }

    public function stream_eof()
    {
        return feof($this->_process->stdout);
    }

    public function stream_seek($offset, $whence = SEEK_SET)
    {
        return fseek($this->_process->stdout, $offset, $whence);
    }

    public function stream_stat()
    {
        return stat($this->_openened_path);
    }
}

function preprocess_file($phph_filename, $autoinclude, $cpp = 'cpp')
{
    if (is_link(__FILE__)) {
        $include_path = dirname(readlink(__FILE__));
    } else {
        $include_path = dirname(__FILE__);
    }

    $include_paths = explode(PATH_SEPARATOR, get_include_path());
    $cppargs = array($cpp);

    $skipped_lines = 3;
    foreach ($include_paths as $path) {
        if (!is_dir($path)) {
            continue;

        } else if ($autoinclude) {
            if (!($files = scandir($path))) {
                throw new Exception("Could not open include path '$path'.");
            }

            // Include all .h files found in directory.
            foreach ($files as $filename) {
                if (substr($filename, -2) == '.h') {
                    $cppargs[] = '-include';
                    $cppargs[] = "$path/$filename";
                    $skipped_lines += 2;
                }
            }

        } else {
            $cppargs[] = '-I';
            $cppargs[] = $path;

        }
    }

    $cppargs[] = $phph_filename;

    $descriptors = array(
        1 => array('pipe', 'w'),
        2 => array('pipe', 'w'),
    );

    $command = implode(' ', array_map('escapeshellarg', $cppargs));
    $pipes = null;

    $process = proc_open($command, $descriptors, $pipes);
    if (!$process) {
        throw new RuntimeException("Could not execute `$command`.");
    }

    $stderr = trim(stream_get_contents($pipes[2]));
    fclose($pipes[2]);

    if ($stderr) {
        fclose($pipes[1]);
        proc_close($process);
        throw new Exception($stderr);
    }

    // Skip lines in the output that contain pre-processor cruft. Using the
    // "-P" flag on cpp will get rid of these, but it also compresses
    // whitespace which throws off line numbers in error messages. When
    // autoinclude is not set, #defines present in the body of the code may
    // still cause line-number inaccuracies.
    while ($skipped_lines--) {
        fgets($pipes[1]);
    }

    return (object) array('stdout' => $pipes[1], 'resource' => $process);
}

stream_wrapper_register('cpp', 'PHPHappiness\CPPStreamWrapper');
stream_wrapper_register('phph', 'PHPHappiness\CPPStreamWrapper');
