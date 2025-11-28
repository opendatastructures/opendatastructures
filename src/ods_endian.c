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
        @file           ods_endian.c

        @brief          Implementation of some endian write and read functions.


        ------------------------------------------------------------------------
*/
#include "../include/ods_endian.h"

bool ods_endian_write_uint16_be(uint8_t *buffer,
                               size_t buffer_size,
                               uint8_t **next,
                               uint16_t number) {

    if (!buffer || buffer_size < 2) goto error;

    buffer[1] = number;
    buffer[0] = number >> 8;

    if (next) *next = buffer + 2;

    return true;
error:
    return false;
}

/*----------------------------------------------------------------------------*/

bool ods_endian_write_uint32_be(uint8_t *buffer,
                               size_t buffer_size,
                               uint8_t **next,
                               uint32_t number) {

    if (!buffer || buffer_size < 4) goto error;

    buffer[3] = number;
    buffer[2] = number >> 8;
    buffer[1] = number >> 16;
    buffer[0] = number >> 24;

    if (next) *next = buffer + 4;

    return true;
error:
    return false;
}

/*----------------------------------------------------------------------------*/

bool ods_endian_write_uint64_be(uint8_t *buffer,
                               size_t buffer_size,
                               uint8_t **next,
                               uint64_t number) {

    if (!buffer || buffer_size < 8) goto error;

    buffer[7] = number;
    buffer[6] = number >> 8;
    buffer[5] = number >> 16;
    buffer[4] = number >> 24;
    buffer[3] = number >> 32;
    buffer[2] = number >> 40;
    buffer[1] = number >> 48;
    buffer[0] = number >> 56;

    if (next) *next = buffer + 8;

    return true;
error:
    return false;
}

/*----------------------------------------------------------------------------*/

bool ods_endian_read_uint16_be(const uint8_t *buffer,
                              size_t buffer_size,
                              uint16_t *number) {

    if (!buffer || !number || buffer_size < 2) goto error;

    *number = ((uint16_t)buffer[1] << 0) | ((uint16_t)buffer[0] << 8);

    return true;
error:
    if (number) *number = 0;
    return false;
}

/*----------------------------------------------------------------------------*/

bool ods_endian_read_uint32_be(const uint8_t *buffer,
                              size_t buffer_size,
                              uint32_t *number) {

    if (!buffer || !number || buffer_size < 4) goto error;

    *number = ((uint32_t)buffer[3] << 0) | ((uint32_t)buffer[2] << 8) |
              ((uint32_t)buffer[1] << 16) | ((uint32_t)buffer[0] << 24);

    return true;
error:
    if (number) *number = 0;
    return false;
}

/*----------------------------------------------------------------------------*/

bool ods_endian_read_uint64_be(const uint8_t *buffer,
                              size_t buffer_size,
                              uint64_t *number) {

    if (!buffer || !number || buffer_size < 8) goto error;

    *number = ((uint64_t)buffer[7] << 0) | ((uint64_t)buffer[6] << 8) |
              ((uint64_t)buffer[5] << 16) | ((uint64_t)buffer[4] << 24) |
              ((uint64_t)buffer[3] << 32) | ((uint64_t)buffer[2] << 40) |
              ((uint64_t)buffer[1] << 48) | ((uint64_t)buffer[0] << 56);

    return true;
error:
    if (number) *number = 0;
    return false;
}

/*----------------------------------------------------------------------------*/
