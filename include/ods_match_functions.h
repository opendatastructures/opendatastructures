/***
    ----------------------------------------------------------------------------

    Copyright 2025 German Space Operations Center (GSOC) DLR e.V.

    Redistribution and use in source and binary forms, with or without 
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice, 
       this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software 
       without specific prior written permission.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” 
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
    OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
    OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    ----------------------------------------------------------------------------
*//**
        @file           ods_match_functions.h
        
        @brief          Definition of some default matching functions.


        ------------------------------------------------------------------------
*/
#ifndef ods_match_functions_h
#define ods_match_functions_h

#include <inttypes.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------*/

/**
        BYTE MATCH of key and string
        up to \0 termination of string.
*/
bool ods_match_strict(const void *key, const void *string);

/*---------------------------------------------------------------------------*/

/**
        MATCH a \0 terminated string,
        against another \0 terminated string.
        Case sensitive match.
*/
bool ods_match_c_string_strict(const void *key, const void *string);

/*---------------------------------------------------------------------------*/

/**
        MATCH a \0 terminated string,
        against another \0 terminated string.
        Case insensitive match.
*/
bool ods_match_c_string_case_ignore_strict(const void *key, const void *string);

/*---------------------------------------------------------------------------*/

/**
        Intptr match
*/
bool ods_match_intptr(const void *ptr1, const void *ptr2);

/*---------------------------------------------------------------------------*/

/**
        Uint64_t match
*/
bool ods_match_uint64(const void *ptr1, const void *ptr2);

#endif /* ods_match_functions_h */
