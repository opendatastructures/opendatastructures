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
        @file           ods_dump.h
        @brief          Definition of dumps.


        ------------------------------------------------------------------------
*/
#ifndef ods_dump_h
#define ods_dump_h

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

/*----------------------------------------------------------------------------*/

/**
        Dump binary as hex to stream.
        @return true on success, false on error
 */
bool ods_dump_binary_as_hex(FILE *stream, uint8_t *binary, uint64_t length);

/*----------------------------------------------------------------------------*/

/**
        Dump the content of the addrinfo to stream.
*/
bool ods_dump_socket_addrinfo(FILE *stream, struct addrinfo *info);

/*---------------------------------------------------------------------------*/

/**
        Dump the content of the sockaddr to stream.
*/
bool ods_dump_socket_sockaddr(FILE *stream, struct sockaddr *addr);

/*---------------------------------------------------------------------------*/

/**
        Dump the content of the sockaddr_storage to stream.
*/
bool ods_dump_socket_sockaddr_storage(FILE *stream,
                                     struct sockaddr_storage *addr);

/*---------------------------------------------------------------------------*/

/**
        Dump the content of the sockaddr_in to stream.
*/
bool ods_dump_socket_sockaddr_in(FILE *stream, struct sockaddr_in *addr);

/*---------------------------------------------------------------------------*/

/**
        Dump the content of the sockaddr_in6 to stream.
*/
bool ods_dump_socket_sockaddr_in6(FILE *stream, struct sockaddr_in6 *addr);

#endif /* ods_dump_h */
