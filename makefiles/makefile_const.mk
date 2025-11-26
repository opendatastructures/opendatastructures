# -*- Makefile -*-
#       ------------------------------------------------------------------------
#
#    Copyright 2025 Markus Töpfer
#
#   Redistribution and use in source and binary forms, with or without 
#   modification, are permitted provided that the following conditions are met:
#
#   1. Redistributions of source code must retain the above copyright notice, 
#      this list of conditions and the following disclaimer.
#
#   2. Redistributions in binary form must reproduce the above copyright notice, 
#      this list of conditions and the following disclaimer in the documentation 
#      and/or other materials provided with the distribution.
#
#   3. Neither the name of the copyright holder nor the names of its contributors 
#      may be used to endorse or promote products derived from this software 
#      without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” 
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
#   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
#   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
#   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
#   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
#   OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
#   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
#   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
#   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#       ------------------------------------------------------------------------

-include ./makefiles/makefile_version.mk 

ODS_LIBNAME             := libopendatastructures
ODS_LIBS                := 

# directories
ODS_SOURCEDIR       := $(ODS_ROOT)/src
ODS_BUILDDIR        := $(ODS_ROOT)/build
ODS_BUILDDIR        := $(abspath $(ODS_BUILDDIR))
ODS_OBJDIR          := $(ODS_BUILDDIR)/obj
ODS_LIBDIR          := $(ODS_BUILDDIR)/lib
ODS_TESTDIR         := $(ODS_BUILDDIR)/test

ODS_UNAME               := $(shell uname)

# generic source files
ODS_HDR             := $(wildcard include/*.h)
ODS_SRC             := $(wildcard src/*.c)
ODS_OBJ_FILE        := $(patsubst %.c,%.o,$(ODS_SRC))
ODS_OBJ             := $(addprefix $(ODS_OBJDIR)/,$(patsubst %,%,$(notdir $(ODS_OBJ_FILE))))
ODS_TEST_SOURCES    := $(wildcard test/*_test.c)
ODS_OBJ_TEST_FILE   := $(patsubst %.c,%.o,$(ODS_TEST_SOURCES))
ODS_OBJ_TEST        := $(addprefix $(ODS_OBJDIR)/,$(patsubst %,%,$(notdir $(ODS_OBJ_TEST_FILE))))

ODS_STATIC           = $(ODS_LIBDIR)/$(ODS_LIBNAME)$(ODS_EDITION).a

ODS_SHARED_LINKER_NAME = $(ODS_LIBNAME)$(ODS_EDITION).so
ODS_SHARED_SONAME      = $(ODS_SHARED_LINKER_NAME).$(ODS_VERSION_MAJOR)
ODS_SHARED_REAL        = $(ODS_SHARED_LINKER_NAME).$(ODS_VERSION)
ODS_SHARED             = $(ODS_LIBDIR)/$(ODS_SHARED_REAL) $(ODS_LIBDIR)/$(ODS_SHARED_LINKER_NAME) $(ODS_LIBDIR)/$(ODS_SHARED_SONAME)

ODS_TEST_RESOURCE        = $(wildcard resources/test/*)
ODS_TEST_RESOURCE_TARGET = $(addprefix $(ODS_TEST_RESOURCE_DIR)/,$(notdir $(ODS_TEST_RESOURCE)))

# shell commands
ODS_MKDIR           := mkdir -p
ODS_RM              := rm -f
ODS_RMDIR           := rm -rf
ODS_SYMLINK         := ln -s
ODS_COPY            := cp -r

# redirection (suppressing printouts from command line tools))
ODS_NUL             := /dev/null
ODS_NUL_STDERR      := 2>$(ODS_NUL) || true
ODS_NUL_STDOUT      := 1>$(ODS_NUL) || true
ODS_DEV_NULL        := $(ODS_NUL_STDOUT) $(ODS_NUL_STDERR)

# make commands quiet
ODS_QUIET           ?= @
#ODS_QUIET            =

# prevent make from displaying 'Entering/Leaving directory ...'
ODS_QUIET_MAKE      ?= --no-print-directory

# include paths
ODS_INC                 := -Iinclude -I$(ODS_BUILDDIR) -I$(ODS_BUILDDIR)/include

#.............................................................................
# distinguish libs and executables
#
# IMPORTANT:
# this _MUST_ be defined as a recursively expanded variable!!
ODS_TARGET           = $(ODS_STATIC) $(ODS_SHARED)
ODS_TEST_TARGET      = $(addprefix $(ODS_TESTDIR)/,$(patsubst %.c,%.run, $(notdir $(ODS_TEST_SOURCES))))
#.............................................................................
# test sources directory
ODS_TEST_RESOURCE_DIR := $(ODS_BUILDDIR)/test/$(ODS_DIRNAME)/resources/

#.............................................................................

BUILD_DEFINITIONS = -D ODS_ROOT='"$(ODS_ROOT)"' \
                    -D ODS_VERSION='"$(ODS_VERSION)"' \
                    -D ODS_VERSION_BUILD_ID='"$(ODS_VERSION_BUILD_ID)"' \
                    -D ODS_VERSION_COMMIT_ID='"$(ODS_VERSION_COMMIT_ID)"' \
                    -D ODS_VERSION_BUILD_DATE='"$(ODS_VERSION_BUILD_DATE)"' \
                    -D ODS_VERSION_COMPILER='"$(ODS_VERSION_COMPILER)"' \
                    -D ODS_PLUGINS_INSTALLDIR='"$(ODS_PLUGINS_INSTALLDIR)"' \

#.............................................................................

TEST_DEFINITIONS =  -D ODS_TEST_RESOURCE_DIR='"$(ODS_TEST_RESOURCE_DIR)"'

#.............................................................................

# CLANG specifics
CFLAGS              += -fstrict-aliasing -Wno-trigraphs -O0

#.............................................................................
#
# these _must_ not be prefixed ...
# -Wno-missing-braces is disabled with GCC by default, but clang still uses it
#

CFLAGS             += -Werror -Wall -Wextra -fPIC $(ODS_INC)
CFLAGS             += -std=c11 -D _DEFAULT_SOURCE -D _POSIX_C_SOURCE=200809
CFLAGS             += -D _XOPEN_SOURCE=500
CFLAGS             += -DDEBUG -g
# To make clang accept C11 '{0}' initialisation ...
CFLAGS             +=  -Wno-missing-braces

ifeq ($(ODS_UNAME), Darwin)
    CFLAGS         +=  -D _DARWIN_C_SOURCE=__DARWIN_C_FULL
endif

# when clang is used write some compile_command.json per file
ifeq ($(CC), clang)
    CFLAGS         +=  -MJ $@.json
endif

# Debug flags - switch on on command line like
# DEBUG=1 make test -j 4

ifdef DEBUG

CFLAGS             += -DDEBUG
CFLAGS             += -g

endif

LFLAGS              = -rdynamic