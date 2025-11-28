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

#-----------------------------------------------------------------------------

$(ODS_BUILDDIR): target_prepare

#-----------------------------------------------------------------------------

target_prepare:
# check if ODS_ROOT environment variable is set
ifndef ODS_ROOT
	$(error ODS_ROOT is not defined. Aborting.)
endif
#
# check if build directory already exists
ifneq ($(wildcard $(ODS_BUILDDIR)/.*),)
	@echo "[PREPARE] build dir FOUND"
else
	@echo "[PREPARE] build dir NOT found, creating ..."
	$(ODS_QUIET)$(ODS_MKDIR) $(ODS_BUILDDIR) $(ODS_NUL_STDERR)
	$(ODS_QUIET)test -d $(ODS_BUILDDIR) || exit 1
	$(ODS_QUIET)$(ODS_MKDIR) $(ODS_OBJDIR) $(ODS_NUL_STDERR)
	$(ODS_QUIET)$(ODS_MKDIR) $(ODS_LIBDIR) $(ODS_NUL_STDERR)
	$(ODS_QUIET)$(ODS_MKDIR) $(ODS_TESTDIR) $(ODS_NUL_STDERR)
endif

#-----------------------------------------------------------------------------

target_clean:
	@echo "[CLEAN    ] clean up ..."
	$(ODS_QUIET)$(ODS_RMDIR) $(ODS_BUILDDIR)
ifeq ($(CC), clang)
	$(ODS_QUIET)$(ODS_RM) $(ODS_COMPILE_COMMANDS)
endif
	@echo "[CLEAN    ] done"

#-----------------------------------------------------------------------------

target_build: $(ODS_TARGET) 

#-----------------------------------------------------------------------------

target_test: $(ODS_TEST_RESOURCE_TARGET) $(ODS_TEST_TARGET) 

#-----------------------------------------------------------------------------

$(ODS_OBJ) : $(ODS_SRC)
	@echo "[CC       ] $@"
	$(ODS_QUIET) $(CC) $(BUILD_DEFINITIONS) $(TEST_DEFINITIONS)\
	$(CFLAGS) $(ODS_FLAGS) -MMD \
	-c $(patsubst %.o,%.c,$(patsubst $(ODS_OBJDIR)/%,$(ODS_ROOT)/src/%,$@)) \
	-o $@
	
#-----------------------------------------------------------------------------

$(ODS_OBJ_TEST) : $(ODS_TEST_SOURCES)
	@echo "[CC       ] $@"
	$(ODS_QUIET) $(CC) $(BUILD_DEFINITIONS) $(TEST_DEFINITIONS) \
	$(CFLAGS) $(ODS_FLAGS) -MMD \
	-c  $(patsubst %.o,%.c,$(patsubst $(ODS_OBJDIR)/%,$(ODS_ROOT)/test/%,$@)) \
	-o $@

#-----------------------------------------------------------------------------

$(ODS_STATIC):  $(ODS_OBJ)
	$(ODS_QUIET)ar rcs $(ODS_STATIC) $(ODS_OBJ)
	$(ODS_QUIET)ranlib $(ODS_STATIC)
	@echo "[STATIC   ] $(notdir $(ODS_STATIC)) created"

#-----------------------------------------------------------------------------

$(ODS_TESTDIR)/%_test.run : $(ODS_OBJDIR)/%_test.o $(ODS_OBJ_IF_TEST) $(ODS_OBJ)
	$(ODS_QUIET)$(eval NO_SELF_DEPENDENCY := $(filter-out $(<:%_test.o=%.o) , $(ODS_OBJ)))
	$(ODS_QUIET)$(eval NO_SELF_DEPENDENCY := $(filter-out $(ODS_OBJ_EXEC) , $(NO_SELF_DEPENDENCY)))
	$(ODS_QUIET)$(CC) -o $@  $< $(NO_SELF_DEPENDENCY) $(LFLAGS) $(ODS_LIBS)
	@echo "[TEST EXEC] $(notdir $@ ) created"

#-----------------------------------------------------------------------------

# ... will create the directory for the resources and copy resources
$(ODS_TEST_RESOURCE_TARGET): $(ODS_TEST_RESOURCE)
	 $(ODS_QUIET) $(shell cp -r $(ODS_TEST_RESOURCE) $(ODS_TEST_RESOURCE_DIR)/)

#-----------------------------------------------------------------------------

$(ODS_LIBDIR)/$(ODS_SHARED_REAL): $(ODS_OBJ)
ifeq ($(ODS_UNAME), Linux)
	$(ODS_QUIET)$(CC) -shared -o $@ $(ODS_OBJ) $(LFLAGS) \
		-Wl,-soname,$(ODS_SHARED_SONAME) \
		-Wl,--defsym -Wl,__ODS_LD_VERSION=0x$(ODS_VERSION_HEX) \
		-Wl,--defsym -Wl,__ODS_LD_EDITION=0x$(ODS_EDITION) \
		$(ODS_LIBS)
else ifeq ($(ODS_UNAME), Darwin)
	$(ODS_QUIET)$(CC) -shared -o $@ $(ODS_OBJ) $(LFLAGS) \
		-compatibility_version $(ODS_VERSION) \
		-current_version $(ODS_VERSION) \
		$(ODS_LIBS)
else
	@echo "[SHARED    ] OS $(ODS_UNAME) unsupported yet."
endif
ifeq ($(ODS_BUILD_MODE), STRIP)
	$(ODS_QUIET)$(ODS_STRIP) $@
endif
	@echo "[SHARED   ] $(notdir $@) created"

#-----------------------------------------------------------------------------

$(ODS_LIBDIR)/$(ODS_SHARED_LINKER_NAME): $(ODS_LIBDIR)/$(ODS_SHARED_REAL)
	$(ODS_QUIET)$(shell \
		cd $(ODS_LIBDIR) ; \
		$(ODS_SYMLINK) $(ODS_SHARED_REAL) $(ODS_SHARED_LINKER_NAME); )
	@echo "[LINK     ] $(notdir $@) created"

#-----------------------------------------------------------------------------

$(ODS_LIBDIR)/$(ODS_SHARED_SONAME): $(ODS_LIBDIR)/$(ODS_SHARED_REAL)
	$(ODS_QUIET)$(shell \
		cd $(ODS_LIBDIR) ; \
		$(ODS_SYMLINK) $(ODS_SHARED_REAL) $(ODS_SHARED_SONAME);)
	@echo "[LINK     ] $(notdir $@) created"

#-----------------------------------------------------------------------------