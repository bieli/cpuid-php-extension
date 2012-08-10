cpuid-php-extension
===================

CPUID - extension for PHP language allow to showing short CPU's info. (on installed server)


What is this ?
-------------
 It is ANSI C source code for extending http://php.net language as server side module.
 This source code need to be "compiled" on destination machine or crosscompiled and manually installed on destination machine.

What functions are promoted in PHP ?
-------------
 * long *cpuid_cpu_detected()* **IMPELENTED**
   * return values for one of declarated constant:
     * *CPUID_INTEL_CPU_DETECTED* - when detected Intel proccessor
     * *CPUID_AMD_CPU_DETECTED* - when detected AMD proccessor
     * *CPUID_UNKNOWN_CPU_DETECTED* - when detected unknown proccessor
 * array *cpuid_array()* **IMPELENTED**
   * return array with CPU specific numerical information
 * array *cpuid_array_desc()* **NOT IMPELENTED**
   * return array with detected CPU information as string
 * long *cpuid_gethostid()* **IMPELENTED**
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

    $ git clone git://github.com/bieli/cpuid-php-extension.git

Next compile extension:

    $ phpize
    $ ./configure OR
    $ make
    $ sudo make install

Next create PHP INI configuration file dedicated for this extension:

    $ cat > /etc/php5/cli/conf.d/cpuid_extension.ini
    extension=cpuid_extension.so

Press: 'Enter' and 'Ctrl + Z'

Create PHP test script with new PHP function from this extension:

    $ cat > cpuid_test.php
    <?php

    var_dump(
        cpuid_array(),
        cpuid_gethostid(),
        cpuid_cpu_detected(),
        cpuid_cpu_detected() === CPUID_INTEL_CPU_DETECTED,
        cpuid_cpu_detected() === CPUID_AMD_CPU_DETECTED,
        cpuid_cpu_detected() === CPUID_UNKNOWN_CPU_DETECTED
    );

Press: 'Enter' and 'Ctrl + Z'

Run test PHP script:

    $ php cpuid_test.php

This is example output from PHP test script:

    array(6) {
      ["stepping"]=>
      string(1) "9"
      ["model"]=>
      string(1) "2"
      ["family"]=>
      string(2) "15"
      ["processor_type"]=>
      string(1) "0"
      ["extended_model"]=>
      string(1) "0"
      ["extended_family"]=>
      string(1) "0"
    }
    int(8323329)
    int(1)
    bool(true)
    bool(false)
    bool(false)
