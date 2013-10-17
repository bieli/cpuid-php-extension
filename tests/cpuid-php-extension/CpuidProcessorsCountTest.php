<?php

class CpuidProcessorsCountTest extends PHPUnit_Framework_TestCase
{
    public function setUp()
    {
        parent::setUp();
        $this->assertTrue(extension_loaded('cpuid'));
        $this->assertTrue(function_exists('cpuid_processors_count'));
    }

    public function testValidElementsCountInCpuidProcessorsCount()
    {
        $testValue = cpuid_processors_count();

        $this->assertTrue(0 < $testValue);
    }
}
