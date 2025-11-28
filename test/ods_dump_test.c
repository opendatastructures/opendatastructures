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
        @file           ods_dump_tests.c

        @brief


        ------------------------------------------------------------------------
*/
#ifndef ODS_TEST_RESOURCE_DIR
#error "Must provide -D ODS_TEST_RESOURCE_DIR=value while compiling this file."
#endif

#include "../src/ods_dump.c"
#include "../include/testrun.h"

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST CASES                                                      #CASES
 *
 *      ------------------------------------------------------------------------
 */

int test_ods_dump_binary_as_hex(void) {

    char *path = ODS_TEST_RESOURCE_DIR "/dump_hex";
    char *buffer = "ABCD";
    char *expect = " 41 42 43 44";
    char *read = NULL;

    FILE *fp = fopen(path, "w");

    uint64_t filesize = 0;
    size_t count = 0;

    testrun(fp != NULL, "File opened");

    testrun(!ods_dump_binary_as_hex(NULL, NULL, 0), "NULL");
    testrun(!ods_dump_binary_as_hex(fp, (uint8_t *)buffer, 0), "NULL");
    testrun(!ods_dump_binary_as_hex(fp, 0, strlen(buffer)), "NULL");
    testrun(
        !ods_dump_binary_as_hex(0, (uint8_t *)buffer, strlen(buffer)), "NULL");

    testrun(
        ods_dump_binary_as_hex(fp, (uint8_t *)buffer, strlen(buffer)), "dump");
    testrun(fclose(fp) == 0, "File closed");

    fp = fopen(path, "r");
    testrun(fp != NULL, "File reopened");
    testrun(fseek(fp, 0L, SEEK_END) == 0, "seek to EOF");
    filesize = ftell(fp);
    testrun(filesize > 0, "filesize < 1");

    read = calloc(filesize + 1, sizeof(char));

    testrun(fseek(fp, 0L, SEEK_SET) == 0, "seek pointer to SOF");

    count = fread(read, sizeof(char), filesize, fp);
    testrun(count > 0, "Failure reading data from file");

    testrun(fclose(fp) == 0, "File closed");

    testrun(strncmp(read, expect, strlen(expect)) == 0);
    free(read);

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_dump_socket_addrinfo() {

    struct addrinfo data = {0};

    testrun(!ods_dump_socket_addrinfo(NULL, NULL));
    testrun(!ods_dump_socket_addrinfo(stdout, NULL));
    testrun(!ods_dump_socket_addrinfo(NULL, &data));

    // empty
    testrun(ods_dump_socket_addrinfo(stdout, &data));

    // set some data
    data.ai_flags = 1;
    data.ai_family = 2;
    data.ai_socktype = 3;
    data.ai_protocol = 4;
    data.ai_addrlen = 5;
    data.ai_canonname = "canon";
    data.ai_next = &data;

    testrun(ods_dump_socket_addrinfo(stdout, &data));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_dump_socket_sockaddr() {

    struct sockaddr_in v4 = {0};
    struct sockaddr_in6 v6 = {0};

    struct sockaddr *data = (struct sockaddr *)&v4;

    testrun(!ods_dump_socket_sockaddr(NULL, NULL));
    testrun(!ods_dump_socket_sockaddr(stdout, NULL));
    testrun(!ods_dump_socket_sockaddr(NULL, data));

    // empty
    testrun(!ods_dump_socket_sockaddr(stdout, data));
    data->sa_family = AF_INET;
    testrun(ods_dump_socket_sockaddr(stdout, data));

    data = (struct sockaddr *)&v4;
    v4.sin_family = AF_INET;
    v4.sin_port = htons(1234);
    v4.sin_addr.s_addr = 1;

    testrun(ods_dump_socket_sockaddr(stdout, data));

    data = (struct sockaddr *)&v6;
    v6.sin6_family = AF_INET6;
    v6.sin6_port = htons(1234);
    v6.sin6_flowinfo = 1;
    v6.sin6_scope_id = 2;
    v6.sin6_addr.s6_addr[1] = 3;

    testrun(ods_dump_socket_sockaddr(stdout, data));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_dump_socket_sockaddr_storage() {

    struct sockaddr_in v4 = {0};
    struct sockaddr_in6 v6 = {0};

    struct sockaddr_storage *data = (struct sockaddr_storage *)&v4;

    testrun(!ods_dump_socket_sockaddr_storage(NULL, NULL));
    testrun(!ods_dump_socket_sockaddr_storage(stdout, NULL));
    testrun(!ods_dump_socket_sockaddr_storage(NULL, data));

    // empty
    testrun(!ods_dump_socket_sockaddr_storage(stdout, data));

    data->ss_family = AF_INET;
    testrun(ods_dump_socket_sockaddr_storage(stdout, data));

    data = (struct sockaddr_storage *)&v4;
    v4.sin_family = AF_INET;
    v4.sin_port = htons(1234);
    v4.sin_addr.s_addr = 1;

    testrun(ods_dump_socket_sockaddr_storage(stdout, data));

    data = (struct sockaddr_storage *)&v6;
    v6.sin6_family = AF_INET6;
    v6.sin6_port = htons(1234);
    v6.sin6_flowinfo = 1;
    v6.sin6_scope_id = 2;
    v6.sin6_addr.s6_addr[1] = 3;

    testrun(ods_dump_socket_sockaddr_storage(stdout, data));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_dump_socket_sockaddr_in() {

    struct sockaddr_in data = {0};

    testrun(!ods_dump_socket_sockaddr_in(NULL, NULL));
    testrun(!ods_dump_socket_sockaddr_in(stdout, NULL));
    testrun(!ods_dump_socket_sockaddr_in(NULL, &data));

    // empty
    testrun(ods_dump_socket_sockaddr_in(stdout, &data));

    data.sin_family = AF_INET;
    data.sin_port = htons(1234);
    data.sin_addr.s_addr = 1;

    testrun(ods_dump_socket_sockaddr_in(stdout, &data));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_dump_socket_sockaddr_in6() {

    struct sockaddr_in6 data = {0};

    testrun(!ods_dump_socket_sockaddr_in6(NULL, NULL));
    testrun(!ods_dump_socket_sockaddr_in6(stdout, NULL));
    testrun(!ods_dump_socket_sockaddr_in6(NULL, &data));

    // empty
    testrun(ods_dump_socket_sockaddr_in6(stdout, &data));

    data.sin6_family = AF_INET6;
    data.sin6_port = htons(1234);
    data.sin6_flowinfo = 1;
    data.sin6_scope_id = 2;
    data.sin6_addr.s6_addr[1] = 3;

    testrun(ods_dump_socket_sockaddr_in6(stdout, &data));

    return testrun_log_success();
}

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST CLUSTER                                                    #CLUSTER
 *
 *      ------------------------------------------------------------------------
 */

int all_tests() {

    testrun_init();
    testrun_test(test_ods_dump_binary_as_hex);
    testrun_test(test_ods_dump_socket_addrinfo);
    testrun_test(test_ods_dump_socket_sockaddr);
    testrun_test(test_ods_dump_socket_sockaddr_storage);
    testrun_test(test_ods_dump_socket_sockaddr_in);
    testrun_test(test_ods_dump_socket_sockaddr_in6);

    return testrun_counter;
}

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST EXECUTION                                                  #EXEC
 *
 *      ------------------------------------------------------------------------
 */

testrun_run(all_tests);
