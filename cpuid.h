/*
 * CPUID - extension for PHP language allow to showing short CPU's info. (on installed server)
 *
 * @author Marcin Bielak <marcin.bieli@gmail.com>
 */

#ifndef HAVE_CPUID_H
#define HAVE_CPUID_H 1

#include <stdio.h>
#include <stdlib.h>

#if defined(__GNUC__)
    #include <stdint.h>
#elif defined(_WIN32)
    # error ONLY POSIX systems (*BSD, Linux, *NIX) are supported.
#endif

#define PHP_CPUID_VERSION "1.0"
#define PHP_CPUID_EXTNAME "cpuid"
#define PHP_CPUID_AUTHOR "Marcin Bielak <marcin.bieli@gmail.com>"

#define INTEL_DETECT_MAGIC_CODE 0x756e6547
#define AMD_DETECT_MAGIC_CODE 0x68747541

#define CPUID_INTEL_CPU_DETECTED 1
#define CPUID_AMD_CPU_DETECTED 2
#define CPUID_UNKNOWN_CPU_DETECTED 0

#define _cpuid_(op, a, b, c, d) __asm__("pushl %%ebx      \n\t" "cpuid            \n\t" "movl %%ebx, %1   \n\t" "popl %%ebx       \n\t" : "=a"(a), "=r"(b), "=c"(c), "=d"(d) : "a"(op) : "cc");

/* Declare the content of this extension globals */
/* (This actually defines a typedef on a structure) */

typedef unsigned long       DWORD;

typedef struct {
    unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
    long int model, family, type, brand, stepping, reserved, extended_model, extended_family;
    uint8_t cpu_detected;
} t_cpu_info;


int ret;
char buff[16];
t_cpu_info cpu_info;


uint8_t cpu_detect(void) {
    uint8_t ret;
    unsigned long ebx, unused;

    _cpuid_(0, unused, ebx, unused, unused);

    switch(ebx) {
        case INTEL_DETECT_MAGIC_CODE:
            ret = CPUID_INTEL_CPU_DETECTED;
            break;
        case AMD_DETECT_MAGIC_CODE:
            ret = CPUID_AMD_CPU_DETECTED;
            break;
        default:
            ret = CPUID_UNKNOWN_CPU_DETECTED;
            break;
    }

    return ret;
}

t_cpu_info get_cpu_info() {
    t_cpu_info cpu_info;

    unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
    int model, family, type, brand, stepping, reserved, extended_family = -1;

    memset(&cpu_info, 0, sizeof(cpu_info));

    cpu_info.cpu_detected = cpu_detect();

    switch(cpu_info.cpu_detected) {
        case CPUID_INTEL_CPU_DETECTED:
            _cpuid_(1, eax, ebx, unused, unused);

            cpu_info.model = (eax >> 4) & 0xF;
            cpu_info.family = (eax >> 8) & 0xF;
            cpu_info.type = (eax >> 12) & 0x3;
            cpu_info.extended_model = (eax >> 16) & 0xF;
            cpu_info.extended_family = (eax >> 20) & 0xFF;
            cpu_info.brand = ebx & 0xFF;
            cpu_info.stepping = eax & 0xF;
            cpu_info.reserved = eax >> 14;
            cpu_info.signature = eax;
            break;
        case CPUID_AMD_CPU_DETECTED:
            _cpuid_(1, eax, unused, unused, unused);

            cpu_info.model = (eax >> 4) & 0xf;
            cpu_info.family = (eax >> 8) & 0xf;
            cpu_info.stepping = eax & 0xf;
            cpu_info.reserved = eax >> 12;
            break;
        default:
            break;
    }

    return cpu_info;
}

#endif
