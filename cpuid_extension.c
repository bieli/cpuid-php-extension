/*
 * CPUID - extension for PHP language allow to showing short CPU's info. (on installed server)
 *
 * @author Marcin Bielak <marcin.bieli@gmail.com>
 */

//TODO: ONLY Intel processors are detected now - add support for AMD

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
t_cpu_info cpu_info;

/* Declare the extension's callback for use by the Zend engine */
PHP_MINIT_FUNCTION(cpuid_init);
PHP_MINFO_FUNCTION(cpuid_info);

/* Declare the PHP functions provided by this extension */
PHP_FUNCTION(cpuid_array);
PHP_FUNCTION(cpuid_gethostid);
PHP_FUNCTION(cpuid_cpu_detected);

// list of custom PHP functions provided by this extension
// set {NULL, NULL, NULL} as the last record to mark the end of list
static function_entry cpuid_functions[] = {
    PHP_FE(cpuid_array, NULL)
    PHP_FE(cpuid_gethostid, NULL)
    PHP_FE(cpuid_cpu_detected, NULL)
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
 * implementation of a custom cpuid_functions
 */
PHP_MINIT_FUNCTION(cpuid_init)
{
    REGISTER_LONG_CONSTANT("CPUID_INTEL_DETECT_MAGIC_CODE", INTEL_DETECT_MAGIC_CODE, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("CPUID_AMD_DETECT_MAGIC_CODE", AMD_DETECT_MAGIC_CODE, CONST_CS|CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("CPUID_INTEL_CPU_DETECTED", CPUID_INTEL_CPU_DETECTED, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("CPUID_AMD_CPU_DETECTED", CPUID_AMD_CPU_DETECTED, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("CPUID_UNKNOWN_CPU_DETECTED", CPUID_UNKNOWN_CPU_DETECTED, CONST_CS|CONST_PERSISTENT);

    cpu_info = get_cpu_info();

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
    array_init(return_value);

    ret = sprintf(buff, "%ld", cpu_info.stepping);

    add_assoc_string(return_value, "stepping", buff, 1);

    ret = sprintf(buff, "%ld", cpu_info.model);

    add_assoc_string(return_value, "model", buff, 1);

    ret = sprintf(buff, "%ld", cpu_info.family);

    add_assoc_string(return_value, "family", buff, 1);

    ret = sprintf(buff, "%ld", cpu_info.type);

    add_assoc_string(return_value, "processor_type", buff, 1);

    ret = sprintf(buff, "%ld", cpu_info.extended_model);

    add_assoc_string(return_value, "extended_model", buff, 1);

    ret = sprintf(buff, "%ld", cpu_info.extended_family);

    add_assoc_string(return_value, "extended_family", buff, 1);
}

PHP_FUNCTION(cpuid_gethostid)
{
    RETURN_LONG(gethostid());
}

PHP_FUNCTION(cpuid_cpu_detected)
{
    RETURN_LONG(cpu_info.cpu_detected);
}
