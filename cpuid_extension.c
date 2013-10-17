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

#ifdef HAVE_CPUID_EXTENSION

#include "ext/standard/info.h"
#include "cpuid.h"

/* Declare the extension's callback for use by the Zend engine */
PHP_MINIT_FUNCTION(cpuid_init);
PHP_MINFO_FUNCTION(cpuid_info);

/* Declare the PHP functions provided by this extension */
PHP_FUNCTION(cpuid_array);
PHP_FUNCTION(cpuid_gethostid);
PHP_FUNCTION(cpuid_cpu_detected);
PHP_FUNCTION(cpuid_processors_count);

// list of custom PHP functions provided by this extension
// set {NULL, NULL, NULL} as the last record to mark the end of list
/* {{{ cpuid_functions[]
 */
static zend_function_entry cpuid_functions[] = {
    PHP_FE(cpuid_array, NULL)
    PHP_FE(cpuid_gethostid, NULL)
    PHP_FE(cpuid_cpu_detected, NULL)
    PHP_FE(cpuid_processors_count, NULL)
    {NULL, NULL, NULL}
};
/* }}} */

// the following code creates an entry for the module and registers it with Zend.
/* {{{ cpuid_module_entry
 */
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
/* }}} */


#ifdef COMPILE_DL_CPUID_EXTENSION
ZEND_GET_MODULE(cpuid)
#endif


/*
 * implementation of a custom cpuid_functions
 */

/* {{{ PHP_MINIT_FUNCTION
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
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cpuid_info)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "CPUID Extension", "enabled");
    php_info_print_table_row(2, "Version", PHP_CPUID_VERSION);
    php_info_print_table_row(2, "Author", PHP_CPUID_AUTHOR);
    php_info_print_table_end();
}
/* }}} */

/* {{{ proto array cpuid_array()
   Return hash array with CPU specific numerical information */
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
/* }}} */

/* {{{ proto int cpuid_gethostid()
   Returns value from system call gethostid()  */
PHP_FUNCTION(cpuid_gethostid)
{
    RETURN_LONG(gethostid());
}
/* }}} */

/* {{{ proto int cpuid_cpu_detected()
   Return return values for one of declarated constant:
    - CPUID_INTEL_CPU_DETECTED - when detected Intel proccessor
    - CPUID_AMD_CPU_DETECTED - when detected AMD proccessor
    - CPUID_UNKNOWN_CPU_DETECTED - when detected unknown proccessor */
PHP_FUNCTION(cpuid_cpu_detected)
{
    RETURN_LONG(cpu_info.cpu_detected);
}
/* }}} */

/* {{{ proto int cpuid_cpu_detected()
   Return the number of processors which are currently online (i.e., available) in OS */
PHP_FUNCTION(cpuid_processors_count)
{
//TODO: implementing for other OS - http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
//TODO: check oteher info from OS - http://www.gnu.org/software/libc/manual/html_node/Processor-Resources.html
    RETURN_LONG(sysconf( _SC_NPROCESSORS_ONLN ));
}
/* }}} */

#endif  /* HAVE_CPUID_EXTENSION */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
