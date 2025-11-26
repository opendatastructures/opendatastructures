#!/usr/bin/env bash

ODS_ROOT=$(pwd)
ODS_LIBS=${ODS_ROOT}/build/lib
LD_LIBRARY_PATH=$ODS_LIBS

# Switch on debug build

# DEBUG=1
DEBUG=

# Enable to show all commands triggered in make files in full length
# ODS_QUIET=
# export ODS_QUIET=

# Compiler to use

CC=gcc
# CC=clang

# Switches for tests

ODS_VALGRIND=valgrind
ODS_TEST_SPARSE_OUT=

export ODS_ROOT
export ODS_LIBS
export LD_LIBRARY_PATH
export DEBUG
export CC

export ODS_TEST_SPARSE_OUT
export ODS_VALGRIND

# clang requires the sdk-path for compilation
if [[ "$OSTYPE" == "darwin"* ]]; then
    export SDKROOT="`xcrun --show-sdk-path`"
fi

