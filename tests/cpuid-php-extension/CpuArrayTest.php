<?php

class CpuArrayTest extends PHPUnit_Framework_TestCase
{
    public function setUp()
    {
        parent::setUp();
        $this->assertTrue(extension_loaded('cpuid'));
        $this->assertTrue(function_exists('cpuid_array'));
    }

    public function testValidElementsCountInCpuArray()
    {
        $arr = cpuid_array();

        $elementsCount = count($arr);

        $this->assertEquals(6, count($arr));
    }

    public function testExistsElementsInCpuArray()
    {
        $arr = cpuid_array();

        $this->assertTrue(isset($arr['stepping']));
        $this->assertTrue(isset($arr['model']));
        $this->assertTrue(isset($arr['family']));
        $this->assertTrue(isset($arr['processor_type']));
        $this->assertTrue(isset($arr['extended_model']));
        $this->assertTrue(isset($arr['extended_family']));
    }

    public function testValidElementsInCpuArray()
    {
        $arr = cpuid_array();

        $this->assertTrue(is_numeric($arr['stepping']));
        $this->assertTrue(is_numeric($arr['model']));
        $this->assertTrue(is_numeric($arr['family']));
        $this->assertTrue(is_numeric($arr['processor_type']));
        $this->assertTrue(is_numeric($arr['extended_model']));
        $this->assertTrue(is_numeric($arr['extended_family']));
    }
}
