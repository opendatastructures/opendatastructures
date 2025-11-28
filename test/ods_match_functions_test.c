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
        @file           ods_match_functions_test.c

        @brief          Unit tests of ods_match_functions


        ------------------------------------------------------------------------
*/
#include "../src/ods_match_functions.c"
#include "../include/testrun.h"

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST CASES                                                      #CASES
 *
 *      ------------------------------------------------------------------------
 */

int test_ods_match_strict() {

    char buffer1[10] = {0};
    char buffer2[10] = {0};

    strcat(buffer1, "test");
    strcat(buffer2, "test");
    testrun(!ods_match_strict(NULL, NULL));
    testrun(!ods_match_strict(buffer1, NULL));
    testrun(!ods_match_strict(NULL, buffer2));

    testrun(ods_match_strict(buffer1, buffer2));

    buffer1[0] = 'T';
    testrun(!ods_match_strict(buffer1, buffer2));
    buffer2[0] = 'T';
    testrun(ods_match_strict(buffer1, buffer2));

    buffer2[4] = 's';
    testrun(!ods_match_strict(buffer1, buffer2));
    buffer1[4] = 's';
    testrun(ods_match_strict(buffer1, buffer2));

    buffer1[5] = '1';
    testrun(!ods_match_strict(buffer1, buffer2));

    buffer2[5] = '1';
    testrun(ods_match_strict(buffer1, buffer2));

    buffer2[5] = 0xFF;
    testrun(!ods_match_strict(buffer1, buffer2));
    buffer1[5] = 0xFF;
    testrun(ods_match_strict(buffer1, buffer2));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_match_c_string_strict() {

    char buffer1[10] = {0};
    char buffer2[10] = {0};

    strcat(buffer1, "test");
    strcat(buffer2, "test");
    testrun(ods_match_c_string_strict(NULL, NULL));
    testrun(!ods_match_c_string_strict(buffer1, NULL));
    testrun(!ods_match_c_string_strict(NULL, buffer2));

    testrun(ods_match_c_string_strict(buffer1, buffer2));

    buffer1[0] = 'T';
    testrun(!ods_match_c_string_strict(buffer1, buffer2));
    buffer2[0] = 'T';
    testrun(ods_match_c_string_strict(buffer1, buffer2));

    buffer2[4] = 's';
    testrun(!ods_match_c_string_strict(buffer1, buffer2));
    buffer1[4] = 's';
    testrun(ods_match_c_string_strict(buffer1, buffer2));

    buffer1[5] = '1';
    testrun(!ods_match_c_string_strict(buffer1, buffer2));

    buffer2[5] = '1';
    testrun(ods_match_c_string_strict(buffer1, buffer2));

    buffer2[5] = 0xFF;
    testrun(!ods_match_c_string_strict(buffer1, buffer2));
    buffer1[5] = 0xFF;
    testrun(ods_match_c_string_strict(buffer1, buffer2));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_match_c_string_case_ignore_strict() {

    char buffer1[10] = {0};
    char buffer2[10] = {0};

    strcat(buffer1, "test");
    strcat(buffer2, "test");
    testrun(ods_match_c_string_case_ignore_strict(NULL, NULL));
    testrun(!ods_match_c_string_case_ignore_strict(buffer1, NULL));
    testrun(!ods_match_c_string_case_ignore_strict(NULL, buffer2));

    testrun(ods_match_c_string_case_ignore_strict(buffer1, buffer2));

    buffer1[0] = 'T';
    testrun(ods_match_c_string_case_ignore_strict(buffer1, buffer2));
    buffer2[0] = 'T';
    testrun(ods_match_c_string_case_ignore_strict(buffer1, buffer2));

    buffer2[4] = 's';
    testrun(!ods_match_c_string_case_ignore_strict(buffer1, buffer2));
    buffer1[4] = 'S';
    testrun(ods_match_c_string_case_ignore_strict(buffer1, buffer2));

    buffer1[5] = '1';
    testrun(!ods_match_c_string_case_ignore_strict(buffer1, buffer2));

    buffer2[5] = '1';
    testrun(ods_match_c_string_case_ignore_strict(buffer1, buffer2));

    buffer2[5] = 0xFF;
    testrun(!ods_match_c_string_case_ignore_strict(buffer1, buffer2));
    buffer1[5] = 0xFF;
    testrun(ods_match_c_string_case_ignore_strict(buffer1, buffer2));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_match_intptr() {

    intptr_t ptr1 = 123;
    intptr_t ptr2 = 123;

    testrun(ods_match_intptr(NULL, NULL));
    testrun(!ods_match_intptr((void *)ptr1, NULL));
    testrun(!ods_match_intptr(NULL, (void *)ptr2));

    testrun(ods_match_intptr((void *)ptr1, (void *)ptr2));

    ptr1 = 1;
    testrun(!ods_match_intptr((void *)ptr1, (void *)ptr2));
    ptr2 = 1;
    testrun(ods_match_intptr((void *)ptr1, (void *)ptr2));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_match_uint64() {

    uint64_t ptr1 = 123;
    uint64_t ptr2 = 123;

    testrun(!ods_match_uint64(NULL, NULL));
    testrun(!ods_match_uint64(&ptr1, NULL));
    testrun(!ods_match_uint64(NULL, &ptr2));

    testrun(ods_match_uint64(&ptr1, &ptr2));

    ptr1 = 1;
    testrun(!ods_match_uint64(&ptr1, &ptr2));
    ptr2 = 1;
    testrun(ods_match_uint64(&ptr1, &ptr2));

    // check max
    ptr1 = 0xFFFFFFFFFFFFFFFF;
    testrun(!ods_match_uint64(&ptr1, &ptr2));
    ptr2 = 0xFFFFFFFFFFFFFFFF;
    testrun(ods_match_uint64(&ptr1, &ptr2));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST CLUSTER                                                    #CLUSTER
 *
 *      ------------------------------------------------------------------------
 */

int all_tests() {

    testrun_init();

    testrun_test(test_ods_match_c_string_strict);
    testrun_test(test_ods_match_c_string_case_ignore_strict);
    testrun_test(test_ods_match_intptr);
    testrun_test(test_ods_match_uint64);

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
