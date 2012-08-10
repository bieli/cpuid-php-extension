cpuid-php-extension
===================

CPUID - extension for PHP language allow to showing short CPU's info. (on installed server)


What is this ?
-------------
 It is ANSI C source code for extending http://php.net language as server side module.
 This source code need to be "compiled" on destination machine or crosscompiled and manually installed on destination machine.

What functions are promoted in PHP ?
-------------
 * array *cpuid_array()* **IMPELENTED**
   * return array with CPU specific numerical information
 * array *cpuid_array_desc()* **NOT IMPELENTED**
   * return array with detected CPU information as string
 * long *cuid_gethostid()* **NOT IMPELENTED**
   * port of system call gethostid()

How to compile source code ?
-------------

 You need below packages:
  * php5
 * php5-dev
 * php5-cli
 * gcc
 * build-essentials
 * make
 * git

First clone repository:

``$ git clone git://github.com/bieli/cpuid-php-extension.git``

Next compile extension:

``
$ phpize
$ ./configure OR
$ make
$ sudo make install
``

Next create PHP INI configuration file dedicated for this extension:

``
$ cat > /etc/php5/cli/conf.d/cpuid_extension.ini
extension=cpuid_extension.so
``

Press: 'Enter' and 'Ctrl + Z'

Create PHP test script with new PHP function from this extension:

``
$ cat > cpuid_test.php
<?php

var_dump(cpuid_array());
``

Press: 'Enter' and 'Ctrl + Z'

Run test PHP script:

``
$ php cpuid_test.php
``

This is output from PHP test script:

``
array(6) {
  ["stepping"]=>
  int(0)
  ["model"]=>
  int(8)
  ["family"]=>
  int(15)
  ["processor_type"]=>
  int(0)
  ["extended_model"]=>
  int(0)
  ["extended_family"]=>
  int(1)
}
``
