#!/usr/bin/env bash

set -e

echo "=================================================================="
echo "MANUAL INSTALL OF CPUID MODULE"
echo "Travis PHP version: ${TRAVIS_PHP_VERSION}"
echo "=================================================================="

git clone http://github.com/bieli/cpuid-php-extension.git
cd cpuid-php-extension

phpize
./configure
make

sudo make install
echo "extension=cpuid_extension.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
