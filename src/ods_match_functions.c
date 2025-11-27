/***
    ----------------------------------------------------------------------------

    Copyright 2025 Markus Töpfer

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
        @file           ods_match_functions.c

        @brief          Implementation of some default match functions.


        ------------------------------------------------------------------------
*/
#include "../include/ods_match_functions.h"

#include <string.h>
#include <strings.h>

bool ods_match_strict(const void *key, const void *string) {

    if (!key || !string) return false;

    size_t len = strlen(string);

    if (strlen(key) != len) return false;

    if (0 == memcmp(key, string, len)) return true;

    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_match_c_string_strict(const void *key, const void *string) {

    if (key == string) return true;

    if (!key || !string) return false;

    if (0 == strcmp(key, string)) return true;

    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_match_c_string_case_ignore_strict(const void *key, const void *string) {

    if (key == string) return true;

    if (!key || !string) return false;

    if (0 == strcasecmp(key, string)) return true;

    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_match_intptr(const void *ptr1, const void *ptr2) {

    return (ptr1 == ptr2);
}

/*---------------------------------------------------------------------------*/

bool ods_match_uint64(const void *ptr1, const void *ptr2) {

    if (!ptr1 || !ptr2) return false;

    return ((*(uint64_t *)ptr1) == (*(uint64_t *)ptr2));
}
