<?php
error_reporting(E_ALL);

$files = scandir('tests');
foreach ($files as $file) {
    if (stripos($file, 'test_') === 0) {
        require_once("phph://tests/$file");
    }
}
