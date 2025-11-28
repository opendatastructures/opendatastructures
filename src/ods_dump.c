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
        @file           ods_dump.c

        @brief


        ------------------------------------------------------------------------
*/
#include "../include/ods_dump.h"

/*---------------------------------------------------------------------------*/

bool ods_dump_binary_as_hex(FILE *stream, uint8_t *binary, uint64_t length) {

    uint64_t i = 0;

    if ((!binary) || (!length)) goto error;

    if (!stream) goto error;

    for (i = 0; i < length; i++) {
        fprintf(stream, " %02x", binary[i]);
    }

    return true;

error:
    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_dump_socket_addrinfo(FILE *stream, struct addrinfo *info) {

    if (!stream || !info) goto error;

    if (!fprintf(stream,
                 "flags          %i\n"
                 "family         %i\n"
                 "type           %i\n"
                 "protocol       %i\n"
                 "sock_addr_len  %i\n"
                 "canonname      %s\n"
                 "next           %p\n",
                 info->ai_flags,
                 info->ai_family,
                 info->ai_socktype,
                 info->ai_protocol,
                 info->ai_addrlen,
                 info->ai_canonname,
                 info->ai_next))
        goto error;

    if (info->ai_addr) return ods_dump_socket_sockaddr(stream, info->ai_addr);

    if (fprintf(stream, "ai_addr          (null)\n")) return true;

error:
    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_dump_socket_sockaddr(FILE *stream, struct sockaddr *addr) {

    if (!stream || !addr) goto error;

    if (addr->sa_family == AF_INET) {

        return ods_dump_socket_sockaddr_in(stream, (struct sockaddr_in *)addr);

    } else if (addr->sa_family == AF_INET6) {

        return ods_dump_socket_sockaddr_in6(stream, (struct sockaddr_in6 *)addr);
    }

error:
    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_dump_socket_sockaddr_storage(FILE *stream,
                                     struct sockaddr_storage *addr) {

    if (!stream || !addr) goto error;

    if (addr->ss_family == AF_INET) {

        return ods_dump_socket_sockaddr_in(stream, (struct sockaddr_in *)addr);

    } else if (addr->ss_family == AF_INET6) {

        return ods_dump_socket_sockaddr_in6(stream, (struct sockaddr_in6 *)addr);
    }

error:
    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_dump_socket_sockaddr_in(FILE *stream, struct sockaddr_in *addr) {

    if (!stream || !addr) goto error;

    char dest[INET6_ADDRSTRLEN] = {0};

    if (0 == inet_ntop(AF_INET, &addr->sin_addr, dest, INET6_ADDRSTRLEN))
        goto error;

    if (!fprintf(stream,
                 "sin_family     %i\n"
                 "sin_port       %hu\n"
                 "IP             %s\n",
                 addr->sin_family,
                 ntohs(addr->sin_port),
                 dest))
        goto error;

    return true;
error:
    return false;
}

/*---------------------------------------------------------------------------*/

bool ods_dump_socket_sockaddr_in6(FILE *stream, struct sockaddr_in6 *addr) {

    if (!stream || !addr) goto error;

    char dest[INET6_ADDRSTRLEN] = {0};

    if (0 == inet_ntop(AF_INET6, &addr->sin6_addr, dest, INET6_ADDRSTRLEN))
        goto error;

    if (!fprintf(stream,
                 "sin6_family    %i\n"
                 "sin6_port      %u\n"
                 "sin6_flowinfo  %u\n"
                 "sin6_scope_id  %u\n"
                 "IP             %s\n",
                 addr->sin6_family,
                 ntohs(addr->sin6_port),
                 addr->sin6_flowinfo,
                 addr->sin6_scope_id,
                 dest))
        goto error;

    return true;
error:
    return false;
}
