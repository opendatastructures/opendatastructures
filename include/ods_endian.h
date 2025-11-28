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
        @file           ods_endian.h

        @brief          Definition of some endian write and read functions.

                        This implementation is independent of the endianess
                        used at the platform and POSIX compliant.
                        It is intent to be used for network protocols, to write
                        in big endian network byte order.

                        @NOTE There are most probably more efficient plattform
                        specific implementations.

        ------------------------------------------------------------------------
*/
#ifndef ods_endian_h
#define ods_endian_h

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 *      ------------------------------------------------------------------------
 *
 *      WRITE from whatever HOST endianess is used, to BIG ENDIAN
 *
 *      ... example usage (write and move ptr in some buffer of buffer_size)
 *
 *      if (!ods_endian_write_ ... (
 *              ptr,
 *              buffer_size - (ptr - buffer_start),
 *              &ptr,
 *              number))
 *              goto error;
 *
 *      ------------------------------------------------------------------------
 */

/**
        Write a uint16_t number to buffer in network byte order.

        @param buffer   start of the buffer to write to
        @param length   of the buffer to write to (MUST be at least 2)
        @param next     (optional) pointer to byte after write
        @param number   number to write in network byte order.
*/
bool ods_endian_write_uint16_be(uint8_t *buffer,
                               size_t length,
                               uint8_t **next,
                               uint16_t number);

/*----------------------------------------------------------------------------*/

/**
        Write a uint32_t number to buffer in network byte order.

        @param buffer   start of the buffer to write to
        @param length   of the buffer to write to (MUST be at least 4)
        @param next     (optional) pointer to byte after write
        @param number   number to write in network byte order.
*/
bool ods_endian_write_uint32_be(uint8_t *buffer,
                               size_t length,
                               uint8_t **next,
                               uint32_t number);

/*----------------------------------------------------------------------------*/

/**
        Write a uint64_t number to buffer in network byte order.

        @param buffer   start of the buffer to write to
        @param length   of the buffer to write to (MUST be at least 8)
        @param next     (optional) pointer to byte after write
        @param number   number to write in network byte order.
*/
bool ods_endian_write_uint64_be(uint8_t *buffer,
                               size_t length,
                               uint8_t **next,
                               uint64_t number);

/*
 *      ------------------------------------------------------------------------
 *
 *      READ to whatever HOST endianess is used, from BIG ENDIAN
 *
 *      ------------------------------------------------------------------------
 */

/**
        Read a uint16_t number from a buffer in network byte order.

        @param buffer   start of the buffer to read from
        @param length   of the buffer to read from (MUST be at least 2)
        @param number   pointer to number
*/
bool ods_endian_read_uint16_be(const uint8_t *buffer,
                              size_t length,
                              uint16_t *number);

/*----------------------------------------------------------------------------*/

/**
        Read a uint32_t number from a buffer in network byte order.

        @param buffer   start of the buffer to read from
        @param length   of the buffer to read from (MUST be at least 4)
        @param number   pointer to number
*/
bool ods_endian_read_uint32_be(const uint8_t *buffer,
                              size_t length,
                              uint32_t *number);

/*----------------------------------------------------------------------------*/

/**
        Read a uint64_t number from a buffer in network byte order.

        @param buffer   start of the buffer to read from
        @param length   of the buffer to read from (MUST be at least 8)
        @param number   pointer to number
*/
bool ods_endian_read_uint64_be(const uint8_t *buffer,
                              size_t length,
                              uint64_t *number);

#endif /* ods_endian_h */
