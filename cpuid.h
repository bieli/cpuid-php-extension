#ifndef HAVE_CPUID_H
#define HAVE_CPUID_H 1

#include <stdio.h>
#include <stdlib.h>
// for gethostid funciton: long gethostid(void);
//#include <unistd.h>

/*
#ifdef _MSC_VER
#   include <intrin.h>
#endif
*/

/* Handy macro for accessing the content of the extension globals */
#ifdef ZTS
#define PHP_CPUID_G(v) TSRMG(memorylog_cpuid_id, zend_cpuid_globals *, v)
#else
#define PHP_CPUID_G(v) (memorylog_globals.v)
#endif

extern zend_module_entry cpuid_module_entry;
#define phpext_cpuid_ptr &cpuid_module_entry

#ifdef PHP_WIN32
# define PHP_CPUID_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_CPUID_API __attribute__ ((visibility("default")))
#else
# define PHP_CPUID_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

typedef unsigned long       DWORD;

#define EXTENDED_OFFSET           0x80000000

/* Vendor-strings. */
#define CPUID_VENDOR_OLDAMD       "AMDisbetter!" //early engineering samples of AMD K5 processor
#define CPUID_VENDOR_AMD          "AuthenticAMD"
#define CPUID_VENDOR_INTEL        "GenuineIntel"
#define CPUID_VENDOR_VIA          "CentaurHauls"
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86"
#define CPUID_VENDOR_CYRIX        "CyrixInstead"
#define CPUID_VENDOR_CENTAUR      "CentaurHauls"
#define CPUID_VENDOR_NEXGEN       "NexGenDriven"
#define CPUID_VENDOR_UMC          "UMC UMC UMC "
#define CPUID_VENDOR_SIS          "SiS SiS SiS "
#define CPUID_VENDOR_NSC          "Geode by NSC"
#define CPUID_VENDOR_RISE         "RiseRiseRise"



enum {
    CPUID_FEAT_ECX_SSE3         = 1 << 0,
    CPUID_FEAT_ECX_PCLMUL       = 1 << 1,
    CPUID_FEAT_ECX_DTES64       = 1 << 2,
    CPUID_FEAT_ECX_MONITOR      = 1 << 3,
    CPUID_FEAT_ECX_DS_CPL       = 1 << 4,
    CPUID_FEAT_ECX_VMX          = 1 << 5,
    CPUID_FEAT_ECX_SMX          = 1 << 6,
    CPUID_FEAT_ECX_EST          = 1 << 7,
    CPUID_FEAT_ECX_TM2          = 1 << 8,
    CPUID_FEAT_ECX_SSSE3        = 1 << 9,
    CPUID_FEAT_ECX_CID          = 1 << 10,
    CPUID_FEAT_ECX_FMA          = 1 << 12,
    CPUID_FEAT_ECX_CX16         = 1 << 13,
    CPUID_FEAT_ECX_ETPRD        = 1 << 14,
    CPUID_FEAT_ECX_PDCM         = 1 << 15,
    CPUID_FEAT_ECX_DCA          = 1 << 18,
    CPUID_FEAT_ECX_SSE4_1       = 1 << 19,
    CPUID_FEAT_ECX_SSE4_2       = 1 << 20,
    CPUID_FEAT_ECX_x2APIC       = 1 << 21,
    CPUID_FEAT_ECX_MOVBE        = 1 << 22,
    CPUID_FEAT_ECX_POPCNT       = 1 << 23,
    CPUID_FEAT_ECX_AES          = 1 << 25,
    CPUID_FEAT_ECX_XSAVE        = 1 << 26,
    CPUID_FEAT_ECX_OSXSAVE      = 1 << 27,
    CPUID_FEAT_ECX_AVX          = 1 << 28,

    CPUID_FEAT_EDX_FPU          = 1 << 0,
    CPUID_FEAT_EDX_VME          = 1 << 1,
    CPUID_FEAT_EDX_DE           = 1 << 2,
    CPUID_FEAT_EDX_PSE          = 1 << 3,
    CPUID_FEAT_EDX_TSC          = 1 << 4,
    CPUID_FEAT_EDX_MSR          = 1 << 5,
    CPUID_FEAT_EDX_PAE          = 1 << 6,
    CPUID_FEAT_EDX_MCE          = 1 << 7,
    CPUID_FEAT_EDX_CX8          = 1 << 8,
    CPUID_FEAT_EDX_APIC         = 1 << 9,
    CPUID_FEAT_EDX_SEP          = 1 << 11,
    CPUID_FEAT_EDX_MTRR         = 1 << 12,
    CPUID_FEAT_EDX_PGE          = 1 << 13,
    CPUID_FEAT_EDX_MCA          = 1 << 14,
    CPUID_FEAT_EDX_CMOV         = 1 << 15,
    CPUID_FEAT_EDX_PAT          = 1 << 16,
    CPUID_FEAT_EDX_PSE36        = 1 << 17,
    CPUID_FEAT_EDX_PSN          = 1 << 18,
    CPUID_FEAT_EDX_CLF          = 1 << 19,
    CPUID_FEAT_EDX_DTES         = 1 << 21,
    CPUID_FEAT_EDX_ACPI         = 1 << 22,
    CPUID_FEAT_EDX_MMX          = 1 << 23,
    CPUID_FEAT_EDX_FXSR         = 1 << 24,
    CPUID_FEAT_EDX_SSE          = 1 << 25,
    CPUID_FEAT_EDX_SSE2         = 1 << 26,
    CPUID_FEAT_EDX_SS           = 1 << 27,
    CPUID_FEAT_EDX_HTT          = 1 << 28,
    CPUID_FEAT_EDX_TM1          = 1 << 29,
    CPUID_FEAT_EDX_IA64         = 1 << 30,
    CPUID_FEAT_EDX_PBE          = 1 << 31
};

enum cpuid_requests {
  CPUID_GETVENDORSTRING,
  CPUID_GETFEATURES,
  CPUID_GETTLB,
  CPUID_GETSERIAL,

  CPUID_INTELEXTENDED = EXTENDED_OFFSET,
  CPUID_INTELFEATURES,
  CPUID_INTELBRANDSTRING,
  CPUID_INTELBRANDSTRINGMORE,
  CPUID_INTELBRANDSTRINGEND,
};

/** issue a single request to CPUID. Fits 'intel features', for instance
 *  note that even if only "eax" and "edx" are of interest, other registers
 *  will be modified by the operation, so we need to tell the compiler about it.
 */
static inline void cpuid(int code, DWORD *a, DWORD *d) {
  asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}

/** issue a complete request, storing general registers output as a string
 */
static inline int cpuid_string(int code, DWORD where[4]) {
  asm volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
               "=c"(*(where+2)),"=d"(*(where+3)):"a"(code));
  return (int)where[0];
}

inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
                                unsigned int *ecx, unsigned int *edx)
{
        // ecx is often an input as well as an output.
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}




















/*
// Required Declarations
int do_intel(void);
int do_amd(void);
void printregs(int eax, int ebx, int ecx, int edx);

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

// Simply call this function detect_cpu();
int detect_cpu(void) { // or main() if your trying to port this as an independant application
    unsigned long ebx, unused;
    cpuid(0, unused, ebx, unused, unused);
    switch(ebx) {
        case 0x756e6547: // Intel Magic Code
        do_intel();
        break;
        case 0x68747541: // AMD Magic Code
        do_amd();
        break;
        default:
        php_printf("Unknown x86 CPU Detected\n");
        break;
    }
    return 0;
}

// Intel Specific brand list
char *Intel[] = {
    "Brand ID Not Supported.",
    "Intel(R) Celeron(R) processor",
    "Intel(R) Pentium(R) III processor",
    "Intel(R) Pentium(R) III Xeon(R) processor",
    "Intel(R) Pentium(R) III processor",
    "Reserved",
    "Mobile Intel(R) Pentium(R) III processor-M",
    "Mobile Intel(R) Celeron(R) processor",
    "Intel(R) Pentium(R) 4 processor",
    "Intel(R) Pentium(R) 4 processor",
    "Intel(R) Celeron(R) processor",
    "Intel(R) Xeon(R) Processor",
    "Intel(R) Xeon(R) processor MP",
    "Reserved",
    "Mobile Intel(R) Pentium(R) 4 processor-M",
    "Mobile Intel(R) Pentium(R) Celeron(R) processor",
    "Reserved",
    "Mobile Genuine Intel(R) processor",
    "Intel(R) Celeron(R) M processor",
    "Mobile Intel(R) Celeron(R) processor",
    "Intel(R) Celeron(R) processor",
    "Mobile Geniune Intel(R) processor",
    "Intel(R) Pentium(R) M processor",
    "Mobile Intel(R) Celeron(R) processor"
};

// This table is for those brand strings that have two values depending on the processor signature. It should have the same number of entries as the above table.
char *Intel_Other[] = {
    "Reserved",
    "Reserved",
    "Reserved",
    "Intel(R) Celeron(R) processor",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Intel(R) Xeon(R) processor MP",
    "Reserved",
    "Reserved",
    "Intel(R) Xeon(R) processor",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// Intel-specific information
int do_intel(void) {
    php_printf("Intel Specific Features:\n");
    unsigned long eax, ebx, ecx, edx, max_eax, signature, unused;
    int model, family, type, brand, stepping, reserved;
    int extended_family = -1;
    cpuid(1, eax, ebx, unused, unused);
    model = (eax >> 4) & 0xf;
    family = (eax >> 8) & 0xf;
    type = (eax >> 12) & 0x3;
    brand = ebx & 0xff;
    stepping = eax & 0xf;
    reserved = eax >> 14;
    signature = eax;
    php_printf("Type %d - ", type);
    switch(type) {
        case 0:
        php_printf("Original OEM");
        break;
        case 1:
        php_printf("Overdrive");
        break;
        case 2:
        php_printf("Dual-capable");
        break;
        case 3:
        php_printf("Reserved");
        break;
    }
    php_printf("\n");
    php_printf("Family %d - ", family);
    switch(family) {
        case 3:
        php_printf("i386");
        break;
        case 4:
        php_printf("i486");
        break;
        case 5:
        php_printf("Pentium");
        break;
        case 6:
        php_printf("Pentium Pro");
        break;
        case 15:
        php_printf("Pentium 4");
    }
    php_printf("\n");
    if(family == 15) {
        extended_family = (eax >> 20) & 0xff;
        php_printf("Extended family %d\n", extended_family);
    }
    php_printf("Model %d - ", model);
    switch(family) {
        case 3:
        break;
        case 4:
        switch(model) {
            case 0:
            case 1:
            php_printf("DX");
            break;
            case 2:
            php_printf("SX");
            break;
            case 3:
            php_printf("487/DX2");
            break;
            case 4:
            php_printf("SL");
            break;
            case 5:
            php_printf("SX2");
            break;
            case 7:
            php_printf("Write-back enhanced DX2");
            break;
            case 8:
            php_printf("DX4");
            break;
        }
        break;
        case 5:
        switch(model) {
            case 1:
            php_printf("60/66");
            break;
            case 2:
            php_printf("75-200");
            break;
            case 3:
            php_printf("for 486 system");
            break;
            case 4:
            php_printf("MMX");
            break;
        }
        break;
        case 6:
        switch(model) {
            case 1:
            php_printf("Pentium Pro");
            break;
            case 3:
            php_printf("Pentium II Model 3");
            break;
            case 5:
            php_printf("Pentium II Model 5/Xeon/Celeron");
            break;
            case 6:
            php_printf("Celeron");
            break;
            case 7:
            php_printf("Pentium III/Pentium III Xeon - external L2 cache");
            break;
            case 8:
            php_printf("Pentium III/Pentium III Xeon - internal L2 cache");
            break;
        }
        break;
        case 15:
        break;
    }
    php_printf("\n");
    cpuid(0x80000000, max_eax, unused, unused, unused);
//    Quok said: If the max extended eax value is high enough to support the processor brand string
//    (values 0x80000002 to 0x80000004), then we'll use that information to return the brand information.
//    Otherwise, we'll refer back to the brand tables above for backwards compatibility with older processors.
//    According to the Sept. 2006 Intel Arch Software Developer's Guide, if extended eax values are supported,
//    then all 3 values for the processor brand string are supported, but we'll test just to make sure and be safe.
    if(max_eax >= 0x80000004) {
        php_printf("Brand: ");
        if(max_eax >= 0x80000002) {
            cpuid(0x80000002, eax, ebx, ecx, edx);
            printregs(eax, ebx, ecx, edx);
        }
        if(max_eax >= 0x80000003) {
            cpuid(0x80000003, eax, ebx, ecx, edx);
            printregs(eax, ebx, ecx, edx);
        }
        if(max_eax >= 0x80000004) {
            cpuid(0x80000004, eax, ebx, ecx, edx);
            printregs(eax, ebx, ecx, edx);
        }
        php_printf("\n");
    } else if(brand > 0) {
        php_printf("Brand %d - ", brand);
        if(brand < 0x18) {
            if(signature == 0x000006B1 || signature == 0x00000F13) {
                php_printf("%s\n", Intel_Other[brand]);
            } else {
                php_printf("%s\n", Intel[brand]);
            }
        } else {
            php_printf("Reserved\n");
        }
    }
    php_printf("Stepping: %d Reserved: %d\n", stepping, reserved);
    return 0;
}

// Print Registers
void printregs(int eax, int ebx, int ecx, int edx) {
    int j;
    char string[17];
    string[16] = '\0';
    for(j = 0; j < 4; j++) {
        string[j] = eax >> (8 * j);
        string[j + 4] = ebx >> (8 * j);
        string[j + 8] = ecx >> (8 * j);
        string[j + 12] = edx >> (8 * j);
    }
    php_printf("%s", string);
}

// AMD-specific information
int do_amd(void) {
    php_printf("AMD Specific Features:\n");
    unsigned long extended, eax, ebx, ecx, edx, unused;
    int family, model, stepping, reserved;
    cpuid(1, eax, unused, unused, unused);
    model = (eax >> 4) & 0xf;
    family = (eax >> 8) & 0xf;
    stepping = eax & 0xf;
    reserved = eax >> 12;
    php_printf("Family: %d Model: %d [", family, model);
    switch(family) {
        case 4:
        php_printf("486 Model %d", model);
        break;
        case 5:
        switch(model) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 6:
            case 7:
            php_printf("K6 Model %d", model);
            break;
            case 8:
            php_printf("K6-2 Model 8");
            break;
            case 9:
            php_printf("K6-III Model 9");
            break;
            default:
            php_printf("K5/K6 Model %d", model);
            break;
        }
        break;
        case 6:
        switch(model) {
            case 1:
            case 2:
            case 4:
            php_printf("Athlon Model %d", model);
            break;
            case 3:
            php_printf("Duron Model 3");
            break;
            case 6:
            php_printf("Athlon MP/Mobile Athlon Model 6");
            break;
            case 7:
            php_printf("Mobile Duron Model 7");
            break;
            default:
            php_printf("Duron/Athlon Model %d", model);
            break;
        }
        break;
    }
    php_printf("]\n");
    cpuid(0x80000000, extended, unused, unused, unused);
    if(extended == 0) {
        return 0;
    }
    if(extended >= 0x80000002) {
        unsigned int j;
        php_printf("Detected Processor Name: ");
        for(j = 0x80000002; j <= 0x80000004; j++) {
            cpuid(j, eax, ebx, ecx, edx);
            printregs(eax, ebx, ecx, edx);
        }
        php_printf("\n");
    }
    if(extended >= 0x80000007) {
        cpuid(0x80000007, unused, unused, unused, edx);
        if(edx & 1) {
            php_printf("Temperature Sensing Diode Detected!\n");
        }
    }
    php_printf("Stepping: %d Reserved: %d\n", stepping, reserved);
    return 0;
}
*/

#endif
