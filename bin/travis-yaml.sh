#!/usr/bin/env bash
# Install the yaml pecl module from source
# Thanks to bd808 for the implementation: https://github.com/bd808

set -e

# pecl is present for this version of php
if pecl &>/dev/null ; then
    printf "\n" | pecl install yaml-devel

# Travis doesn't always have pecl installed for alpha/beta php versions
else
    echo "=================================================================="
    echo "MANUAL INSTALL OF PECL MODULE"
    echo "Travis doesn't have a working pecl binary for ${TRAVIS_PHP_VERSION}"
    echo "=================================================================="

    # Download and unpack latest tarball
    curl -o yaml.tgz http://pecl.php.net/get/yaml
    tar xzf yaml.tgz
    cd yaml-*

    # Standard pecl module build dance
    phpize
    ./configure --with-yaml
    make

    # Install our new module
    sudo make install
    echo "extension=cpuid_extension.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini
fi
