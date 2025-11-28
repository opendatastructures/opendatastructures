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

ODS_EDITION            := 1

#-----------------------------------------------------------------------------
ODS_VERSION_BUILD_ID_FILE := $(ODS_ROOT)/.ods_build_id.txt

ODS_VERSION_MAJOR      := 0
ODS_VERSION_MINOR      := 0
ODS_VERSION_PATCH      := 1
ODS_VERSION            := $(ODS_VERSION_MAJOR).$(ODS_VERSION_MINOR).$(ODS_VERSION_PATCH)
ODS_VERSION_HEX        := $(shell printf "%02i%02i%02i\n" $(ODS_VERSION_MAJOR) $(ODS_VERSION_MINOR) $(ODS_VERSION_PATCH))
ODS_VERSION_BUILD_ID   := $(shell [ ! -e $(ODS_VERSION_BUILD_ID_FILE) ] && echo 0 > $(ODS_VERSION_BUILD_ID_FILE); cat $(ODS_VERSION_BUILD_ID_FILE))
ODS_VERSION_BUILD_DATE := $(shell date '+%Y.%m.%d_%H:%M:%S')
ODS_VERSION_COMPILER   := $(shell echo $(CC) && cc -dumpversion)
ODS_VERSION_COMMIT_ID  := $(shell git log --format="%H" -n 1)



#-----------------------------------------------------------------------------
