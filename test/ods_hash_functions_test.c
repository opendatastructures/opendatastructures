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
        @file           ods_hash_functions_test.c

        @brief


        ------------------------------------------------------------------------
*/
#include "ods_hash_functions.c"
#include "../include/testrun.h"

#include "stdbool.h"
#include "assert.h"

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST HELPER                                                     #HELPER
 *
 *      ------------------------------------------------------------------------
 */

#define VARIANCE(v, e, x) ((v) + ((x) - (e)) * ((x) - (e)))

bool utils_fill_buffer_random_string(uint8_t **buffer,
                                     size_t length,
                                     const char *alphabet_in) {

    static const char *alphabet_default = "1234567890AbCdEfGhJkMnPqRsTwXz";

    const char *alphabet = alphabet_in;
    if (!alphabet) alphabet = alphabet_default;

    size_t alphabet_max_index = strlen(alphabet);

    if (0 == alphabet_max_index) goto error;

    --alphabet_max_index;

    size_t index = 0;
    uint8_t *pointer = NULL;
    int64_t number = 0;

    if (!length) goto error;

    pointer = *buffer;

    if (!pointer) {
        pointer = calloc(length, sizeof(uint8_t));
        *buffer = pointer;
    }

    for (index = 0; index + 1 < length; index++) {
        number = random();
        pointer[index] = alphabet[(number * alphabet_max_index) / RAND_MAX];
    }

    pointer[length - 1] = 0;

    return true;

error:
    return false;
}

/*---------------------------------------------------------------------------*/

void create_random_c_strings(char **keys, size_t num_keys) {

    for (size_t i = 0; i < num_keys; ++i) {

        utils_fill_buffer_random_string((uint8_t **)&keys[i], 5 + i % 250, 0);
    }
}

char *keys[1 << 20] = {};

/*---------------------------------------------------------------------------*/

void helper_hash_function_c_string(uint64_t (*f)(const void *),
                                   double expected_avg) {

    assert(0 == f(0));

    uint64_t hash_value = 0;
    double average = 0;
    double variance = 0;

    const size_t num_keys = sizeof(keys) / sizeof(keys[0]);

    for (size_t i = 0; i < num_keys; ++i) {

        hash_value = f(keys[i]);
        average += hash_value;
        variance = VARIANCE(variance, expected_avg, hash_value);
    }

    average /= num_keys;
    variance /= num_keys;

    fprintf(stderr,
            "AVERAGE EXPECTED: %f    REAL:  %f    VARIANCE %f\n",
            expected_avg,
            average,
            variance);
}

/*----------------------------------------------------------------------------*/

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST CASES                                                      #CASES
 *
 *      ------------------------------------------------------------------------
 */

int test_ods_hash_simple_c_string() {

    helper_hash_function_c_string(ods_hash_simple_c_string, UINT8_MAX / 2);

    return testrun_log_success();
}

/*---------------------------------------------------------------------------*/

int test_ods_hash_pearson_c_string() {

    helper_hash_function_c_string(ods_hash_pearson_c_string, UINT8_MAX / 2);

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_hash_intptr() {

    for (intptr_t i = 0; i < 0xffff; i++) {

        testrun((uint64_t)i == ods_hash_intptr((void *)i));
    }

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_hash_uint64() {

    uint64_t i = 0;

    for (i = 0; i < 0xffff; i++) {

        testrun((uint64_t)i == ods_hash_uint64(&i));
    }

    // check max
    i = 0xFFFFFFFFFFFFFFFF;
    testrun(i == ods_hash_uint64(&i));

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_hash_int64() {

    int64_t i = 0;

    for (i = -0xffff; i < 0xffff; i++) {

        testrun((uint64_t)i == ods_hash_int64(&i));
    }

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
    testrun_test(test_ods_hash_simple_c_string);
    testrun_test(test_ods_hash_pearson_c_string);
    testrun_test(test_ods_hash_intptr);
    testrun_test(test_ods_hash_uint64);
    testrun_test(test_ods_hash_int64);

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
