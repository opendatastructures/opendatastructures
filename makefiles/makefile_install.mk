# -*- Makefile -*-
#       ------------------------------------------------------------------------
#
#   Copyright 2025 German Space Operations Center (GSOC) DLR e.V.
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

include ./makefiles/makefile_version.mk 
include ./makefiles/makefile_const.mk

ODS_LIB_INSTALL_DIR 	:= /usr/local

ODS_LIB_SOURCE_ROOT		:= $(ODS_LIBDIR)
ODS_PKG_CONFIG_FILE     := $(ODS_LIBNAME).pc
ODS_PKG_CONFIG_PATH     := $(ODS_LIB_INSTALL_DIR)/lib/pkgconfig
ODS_PKG_CONFIG 			:= $(ODS_PKG_CONFIG_PATH)/$(ODS_PKG_CONFIG_FILE)

.phony: install deinstall

install: install_lib_header install_pkg_config install_lib_sources

install_lib_header : install_pkg_config
	$(ODS_QUIET) sudo $(ODS_MKDIR) $(ODS_LIB_INSTALL_DIR)/include/opendatastructures
	$(ODS_QUIET) sudo $(ODS_COPY) $(ODS_BUILDDIR)/include/*.h $(ODS_LIB_INSTALL_DIR)/include/opendatastructures/.

install_lib_sources : 
	$(ODS_QUIET) sudo $(ODS_MKDIR) $(ODS_LIB_INSTALL_DIR)/lib/opendatastructures
	$(ODS_QUIET) sudo $(ODS_COPY) $(ODS_LIBDIR)/* $(ODS_LIB_INSTALL_DIR)/lib/opendatastructures/.

deinstall : 
	$(ODS_QUIET) sudo $(ODS_RMDIR) $(ODS_LIB_INSTALL_DIR)/include/opendatastructures
	$(ODS_QUIET) sudo $(ODS_RMDIR) $(ODS_LIB_INSTALL_DIR)/lib/opendatastructures
	$(ODS_QUIET) sudo $(ODS_RM) $(ODS_PKG_CONFIG)

install_pkg_config :
	$(ODS_QUIET) for item in $(ODS_LIBNAME); do \
		sudo touch $(ODS_PKG_CONFIG) ;\
		sudo chmod a+w  $(ODS_PKG_CONFIG) ;\
		sudo echo $(ODS_PKG_CONFIG_FILE) >  $(ODS_PKG_CONFIG) ;\
		sudo echo "prefix=$(ODS_LIB_INSTALL_DIR)" >>  $(ODS_PKG_CONFIG) ;\
		sudo echo "exec_prefix=$(ODS_LIB_INSTALL_DIR)" >>  $(ODS_PKG_CONFIG);\
		sudo echo "includedir=$(ODS_LIB_INSTALL_DIR)/include" >>  $(ODS_PKG_CONFIG);\
		sudo echo "libdir=$(ODS_LIB_INSTALL_DIR)/lib" >>  $(ODS_PKG_CONFIG) ;\
		sudo echo "" >>  $(ODS_PKG_CONFIG) ;\
		sudo echo "Name:$(ODS_LIB_NAME)" >> $(ODS_PKG_CONFIG) ;\
		sudo echo "Description: The $$item Library." >> $(ODS_PKG_CONFIG) ;\
		sudo echo "Version:$(ODS_VERSION_MAJOR).$(ODS_VERSION_MINOR).$(ODS_VERSION_PATCH)" >> $(ODS_PKG_CONFIG);\
		sudo echo "Cflags: -I$(ODS_LIB_INSTALL_DIR)/include/opendatastructures/$(ODS_LIBNAME)" >>$(ODS_PKG_CONFIG) ;\
		sudo echo "Libs: -L$(ODS_LIB_INSTALL_DIR)/lib/opendatastructures/ -l$(ODS_LIBNAME)" >>$(ODS_PKG_CONFIG) ;\
	done