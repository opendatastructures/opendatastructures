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
        @file           ods_base64.h
        @brief          Definition of base64 Encoding of RFC4648.

        ------------------------------------------------------------------------
*/
#ifndef ods_base64_h
#define ods_base64_h

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 *      ------------------------------------------------------------------------
 *
 *                             ENCODING
 *
 *      ------------------------------------------------------------------------
 *
 */

/**
        Encode a source buffer of length to a destination buffer.

        MODE 1  - allocate destination
        If *destination == NULL the buffer will be allocated and the
        length of the allocated data will be written to dest_length

        MODE 2  - fill destination
        If *destination != NULL the buffer will be filled with the
        encoded string, if the dest_length is big enough.

        @param source           source buffer to be encoded
        @param src_length       length of the soruce buffer
        @param destination      pointer to destination buffer
        @param dest_length      pointer to length of the destination buffer

        @returns true if the source was encoded and written to destination.
*/
bool ods_base64_encode(const uint8_t *source,
                      size_t src_length,
                      uint8_t **destination,
                      size_t *dest_length);

/*----------------------------------------------------------------------------*/

/**
        URL encode a source buffer of length to a destination buffer.
        For @mode and @param @see ods_base64_encode
*/
bool ods_base64_url_encode(const uint8_t *buffer,
                          size_t length,
                          uint8_t **result,
                          size_t *result_length);

/*
 *      ------------------------------------------------------------------------
 *
 *                             DECODING
 *
 *      ------------------------------------------------------------------------
 *
 */

/**
        Decode a source buffer of length to a destination buffer.
        For @mode and @param @see ods_base64_encode
*/
bool ods_base64_decode(const uint8_t *buffer,
                      size_t length,
                      uint8_t **result,
                      size_t *result_length);

/*----------------------------------------------------------------------------*/

/**
        URL decode a source buffer of length to a destination buffer.
        For @mode and @param @see ods_base64_encode
*/
bool ods_base64_url_decode(const uint8_t *buffer,
                          size_t length,
                          uint8_t **result,
                          size_t *result_length);

#endif /* ods_base64_h */
