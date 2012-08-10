PHP_ARG_ENABLE(cpuid_extension, whether to enable cpuid extension,
[ --enable-cpuid-extension   Enable cpuid extension])
 
if test "$PHP_CPUID_EXTENSION" = "yes"; then
  AC_DEFINE(HAVE_CPUID_EXTENSION, 1, [Whether you have cpu extension])
  PHP_NEW_EXTENSION(cpuid_extension, cpuid_extension.c, $ext_shared)
fi

