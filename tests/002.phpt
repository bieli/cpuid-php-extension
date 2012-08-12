--TEST--
CPUID PHP extension cpuid_processors_count() method tests
--SKIPIF--
<?php if (!extension_loaded("cpuid_extension")) print "skip"; ?>
--FILE--
<?php

var_dump(0 < count(cpuid_processors_count()));

?>
--EXPECT--
bool(true)
