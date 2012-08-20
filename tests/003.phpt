--TEST--
CPUID PHP extension cpuid_gethostid() method tests
--SKIPIF--
<?php if (!extension_loaded("cpuid")) print "skip"; ?>
--FILE--
<?php

var_dump(0 < count(cpuid_gethostid()));

?>
--EXPECT--
bool(true)
