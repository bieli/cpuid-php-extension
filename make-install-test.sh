#!/bin/sh

PHP=`whereis php | awk '{ print $2;}'`
make clean && make && sudo make install && php cpuid_test.php
TEST_PHP_EXECUTABLE=$PHP php run-tests.php tests
