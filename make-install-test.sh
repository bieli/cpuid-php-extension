#!/bin/sh

make clean && make && sudo make install && php cpuid_test.php

