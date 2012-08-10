<?php

var_dump(
    cpuid_array(),
    cpuid_gethostid(),
    cpuid_cpu_detected(),
    cpuid_cpu_detected() === CPUID_INTEL_CPU_DETECTED,
    cpuid_cpu_detected() === CPUID_AMD_CPU_DETECTED,
    cpuid_cpu_detected() === CPUID_UNKNOWN_CPU_DETECTED,
    cpuid_cores_count()
);
