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
        @file           ods_hash_functions.h

        @brief          Default Hash functions. 


        ------------------------------------------------------------------------
*/
#ifndef ods_hash_functions_h
#define ods_hash_functions_h

#include <inttypes.h>

/**
        Simple hash function for c strings (null-terminated!).
        @param c_string zero-terminated array of bytes
        @return values in the range of 0 ... 255
 */
uint64_t ods_hash_simple_c_string(const void *c_string);

/*---------------------------------------------------------------------------*/

/**
        Pearson hashing for c strings.
        See Pearson, Peter K. (June 1990),
               "Fast Hashing of Variable-Length Text Strings",
               Communications of the ACM, 33 (6)

        @param c_string zero-terminated array of bytes
        @return values in the range of 0 ... 255

 */
uint64_t ods_hash_pearson_c_string(const void *c_string);

/*---------------------------------------------------------------------------*/

/**
        Returns the content of the intptr.
*/
uint64_t ods_hash_intptr(const void *intptr);

/*---------------------------------------------------------------------------*/

/**
        Returns the content of the uint64_t pointer.
*/
uint64_t ods_hash_uint64(const void *uint64);

/*---------------------------------------------------------------------------*/

/**
        Returns the content of int64.
*/
uint64_t ods_hash_int64(const void *int64);

#endif /* ods_hash_functions_h */
