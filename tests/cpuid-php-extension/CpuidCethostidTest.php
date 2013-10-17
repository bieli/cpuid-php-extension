<?php

class CpuidCethostidTest extends PHPUnit_Framework_TestCase
{
    public function setUp()
    {
        parent::setUp();
        $this->assertTrue(extension_loaded('cpuid'));
        $this->assertTrue(function_exists('cpuid_gethostid'));
    }

    public function testValidElementsCountInCpuidCethostid()
    {
        $testValue = cpuid_gethostid();

        $this->assertTrue(0 < $testValue);
    }
}
