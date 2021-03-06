#!/usr/bin/env bash
# Travis CI command script for compiling and installing cpuid_extension for PHP

set -e

echo "=================================================================="
echo "MANUAL INSTALL OF CPUID MODULE"
echo "Travis PHP version: ${TRAVIS_PHP_VERSION}"
echo "=================================================================="

sudo apt-get install gcc-multilib

git clone http://github.com/bieli/cpuid-php-extension.git
cd cpuid-php-extension

phpize
#TODO: need BUGFIX for -m64 architecture
CFLAGS="-m32" ./configure
make
#make test

#sudo make install
#echo "extension=cpuid_extension.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini

###PHP_LIB_PATH=`grep -r cpuid_extension.so  ~/.phpenv/versions/$(phpenv version-name)/lib/php/extensions/ | grep -oP "\/.[^\.]*.so"`
#PHP_LIB_PATH=~/.phpenv/versions/$(phpenv version-name)/lib/php/extensions/no-debug-zts-20100525/cpuid_extension.so

#echo "+==================================================================+"
#echo "PHP_LIB_PATH: '$PHP_LIB_PATH'"
#ls $PHP_LIB_PATH -la
#echo "+==================================================================+"

#sudo mkdir -p /lib/php/extensions/no-debug-zts-20100525
#sudo chmod a+wrx /lib/php/extensions/no-debug-zts-20100525
#sudo cp $PHP_LIB_PATH /lib/php/extensions/no-debug-zts-20100525/cpuid_extension.so
#sudo chmod a+wrx /lib/php/extensions/no-debug-zts-20100525/cpuid_extension.so

#echo "+==================================================================+"
#ls /lib/php/extensions/no-debug-zts-20100525/cpuid_extension.so -la
#echo "+==================================================================+"


#echo "extension=$PHP_LIB_PATH" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
