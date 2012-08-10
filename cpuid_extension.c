/*
 * CPUID - extension for PHP language allow to showing short CPU's info. (on installed server)
 *
 * @author Marcin Bielak <marcin.bieli@gmail.com>
 */

//TODO: ONLY Intel processors are detected now - add support for AMD
//TODO: debug & test detect_cpu();

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "ext/standard/info.h"
#include "cpuid.h"

#define PHP_CPUID_VERSION "1.0"
#define PHP_CPUID_EXTNAME "cpuid"
#define PHP_CPUID_AUTHOR "Marcin Bielak <marcin.bieli@gmail.com>"


/* Declare the content of this extension globals */
/* (This actually defines a typedef on a structure) */
int ret;
char buff[16];
DWORD cpuid_info[5];

/* Declare the extension's callback for use by the Zend engine */
PHP_MINIT_FUNCTION(cpuid_init);
PHP_MINFO_FUNCTION(cpuid_info);

/* Declare the PHP functions provided by this extension */
PHP_FUNCTION(cpuid_array);
PHP_FUNCTION(cpuid_gethostid);

// list of custom PHP functions provided by this extension
// set {NULL, NULL, NULL} as the last record to mark the end of list
static function_entry cpuid_functions[] = {
    PHP_FE(cpuid_array, NULL)
    PHP_FE(cpuid_gethostid, NULL)
    {NULL, NULL, NULL}
};

// the following code creates an entry for the module and registers it with Zend.
zend_module_entry cpuid_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_CPUID_EXTNAME,
    cpuid_functions,
    PHP_MINIT(cpuid_init), // name of the MINIT function or NULL if not applicable
    NULL, // name of the MSHUTDOWN function or NULL if not applicable
    NULL, // name of the RINIT function or NULL if not applicable
    NULL, // name of the RSHUTDOWN function or NULL if not applicable
    PHP_MINFO(cpuid_info), // name of the MINFO function or NULL if not applicable
#if ZEND_MODULE_API_NO >= 20010901
    PHP_CPUID_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(cpuid)


/*
 *  implementation of a custom cpuid_functions
 */

PHP_MINIT_FUNCTION(cpuid_init)
{
    unsigned eax, ebx, ecx, edx;

//TODO: processor info and feature bits
//eax = 1;
    eax = EXTENDED_OFFSET;

    native_cpuid(&eax, &ebx, &ecx, &edx);

    cpuid_info[0] = eax & 0xF;
    cpuid_info[1] = (eax >> 4) & 0xF;
    cpuid_info[2] = (eax >> 8) & 0xF;
    cpuid_info[3] = (eax >> 12) & 0x3;
    cpuid_info[4] = (eax >> 16) & 0xF;
    cpuid_info[5] = (eax >> 20) & 0xFF;

    return SUCCESS;
}

PHP_MINFO_FUNCTION(cpuid_info)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "CPUID Extension", "enabled");
    php_info_print_table_row(2, "Version", PHP_CPUID_VERSION);
    php_info_print_table_row(2, "Author", PHP_CPUID_AUTHOR);
    php_info_print_table_end();
}

PHP_FUNCTION(cpuid_array)
{
/*
//DEBUG PHP messages
    php_printf("stepping %d\n", cpuid_info[0]);
    php_printf("model %d\n", cpuid_info[1]);
    php_printf("family %d\n", cpuid_info[2]);
    php_printf("processor type %d\n", cpuid_info[3]);
    php_printf("extended model %d\n", cpuid_info[4]);
    php_printf("extended family %d\n", cpuid_info[5]);
*/

    array_init(return_value);

    ret = sprintf(buff, "%ld", cpuid_info[0]);

    add_assoc_string(return_value, "stepping", buff, 1);

    ret = sprintf(buff, "%ld", cpuid_info[1]);

    add_assoc_string(return_value, "model", buff, 1);

    ret = sprintf(buff, "%ld", cpuid_info[2]);

    add_assoc_string(return_value, "family", buff, 1);

    ret = sprintf(buff, "%ld", cpuid_info[3]);

    add_assoc_string(return_value, "processor_type", buff, 1);

    ret = sprintf(buff, "%ld", cpuid_info[4]);

    add_assoc_string(return_value, "extended_model", buff, 1);

    ret = sprintf(buff, "%ld", cpuid_info[5]);

    add_assoc_string(return_value, "extended_family", buff, 1);
}

PHP_FUNCTION(cpuid_gethostid)
{
    RETURN_LONG(gethostid());
}
