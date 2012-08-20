--TEST--
CPUID PHP extension cpuid_array() method tests
--SKIPIF--
<?php if (!extension_loaded("cpuid")) print "skip"; ?>
--FILE--
<?php

$arr = cpuid_array();

var_dump(count($arr));

var_dump(isset($arr['stepping']));
var_dump(isset($arr['model']));
var_dump(isset($arr['family']));
var_dump(isset($arr['processor_type']));
var_dump(isset($arr['extended_model']));
var_dump(isset($arr['extended_family']));

var_dump(is_numeric($arr['stepping']));
var_dump(is_numeric($arr['model']));
var_dump(is_numeric($arr['family']));
var_dump(is_numeric($arr['processor_type']));
var_dump(is_numeric($arr['extended_model']));
var_dump(is_numeric($arr['extended_family']));

?>
--EXPECT--
int(6)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
