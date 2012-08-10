cpuid-php-extension
===================

CPUID - extension for PHP language allow to showing short CPU's info. (on installed server)


What is this ?
-------------
 It is ANSI C source code for extending http://php.net language as server side module.
 This source code need to be "compiled" on destination machine or crosscompiled and manually installed on destination machine.

What functions are implemented in CPUID PHP extension ?
-------------
 * long *cpuid_cpu_detected()* **IMPELENTED**
   * return values for one of declarated constant:
     * *CPUID_INTEL_CPU_DETECTED* - when detected Intel proccessor
     * *CPUID_AMD_CPU_DETECTED* - when detected AMD proccessor
     * *CPUID_UNKNOWN_CPU_DETECTED* - when detected unknown proccessor
 * array *cpuid_array()* **IMPELENTED**
   * return array with CPU specific numerical information
 * long *cpuid_gethostid()* **IMPELENTED**
   * return value of call gethostid()
 * long *cpuid_cores_count()* **IMPELENTED**
   * return number of cores installed on machine
 * array *cpuid_array_desc()* **NOT IMPELENTED**
   * return array with detected CPU information as string
 * array *cpuid_check_future(long)* **NOT IMPELENTED**
   * inputed constant for exisiting future in proccessor

        > /**
        >  * Reference:
        >  * http://datasheets.chipdb.org/Intel/x86/CPUID/24161821.pdf
        >  * http://www.flounder.com/cpuid_explorer2.htm
        >  */
        > enum CpuidFeatures
        > {
        >   FPU   = 1<< 0, // Floating-Point Unit on-chip
        >   VME   = 1<< 1, // Virtual Mode Extension
        >   DE    = 1<< 2, // Debugging Extension
          PSE   = 1<< 3, // Page Size Extension
          TSC   = 1<< 4, // Time Stamp Counter
          MSR   = 1<< 5, // Model Specific Registers
          PAE   = 1<< 6, // Physical Address Extension
          MCE   = 1<< 7, // Machine Check Exception
          CX8   = 1<< 8, // CMPXCHG8 Instruction
          APIC  = 1<< 9, // On-chip APIC hardware
          SEP   = 1<<11, // Fast System Call
          MTRR  = 1<<12, // Memory type Range Registers
          PGE   = 1<<13, // Page Global Enable
          MCA   = 1<<14, // Machine Check Architecture
          CMOV  = 1<<15, // Conditional MOVe Instruction
          PAT   = 1<<16, // Page Attribute Table
          PSE36 = 1<<17, // 36bit Page Size Extension
          PSN   = 1<<18, // Processor Serial Number
          CLFSH = 1<<19, // CFLUSH Instruction
          DS    = 1<<21, // Debug Store
          ACPI  = 1<<22, // Thermal Monitor & Software Controlled Clock
          MMX   = 1<<23, // MultiMedia eXtension
          FXSR  = 1<<24, // Fast Floating Point Save & Restore
          SSE   = 1<<25, // Streaming SIMD Extension 1
          SSE2  = 1<<26, // Streaming SIMD Extension 2
          SS    = 1<<27, // Self Snoop
          HTT   = 1<<28, // Hyper Threading Technology
          TM    = 1<<29, // Thermal Monitor
          PBE   = 1<<31, // Pend Break Enabled
        };

        /**
         * Reference:
         * http://datasheets.chipdb.org/Intel/x86/CPUID/24161821.pdf
         * http://www.flounder.com/cpuid_explorer2.htm
         */
        enum CpuidExtendedFeatures
        {
          SSE3  = 1<< 0, // Streaming SIMD Extension 3
          MW    = 1<< 3, // Mwait instruction
          CPL   = 1<< 4, // CPL-qualified Debug Store
          VMX   = 1<< 5, // VMX
          EST   = 1<< 7, // Enhanced Speed Test
          TM2   = 1<< 8, // Thermal Monitor 2
          L1    = 1<<10, // L1 Context ID
          CAE   = 1<<13, // CompareAndExchange 16B
        };

   * return boolean true when future exists or false where not exists or null when inputed unknown value

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
