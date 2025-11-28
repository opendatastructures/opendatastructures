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
        @file           ods_endian_test.c

        @brief          Unit tests of


        ------------------------------------------------------------------------
*/
#include "../src/ods_endian.c"
#include "../include/testrun.h"

#include "../include/ods_dump.h"

/*
 *      ------------------------------------------------------------------------
 *
 *      TEST CASES                                                      #CASES
 *
 *      ------------------------------------------------------------------------
 */

int test_ods_endian_write_uint16_be() {

    size_t size = 100;
    uint8_t buffer[size];
    memset(buffer, 0, size);
    uint8_t *next = NULL;

    testrun(!ods_endian_write_uint16_be(NULL, 0, NULL, 0));
    testrun(!ods_endian_write_uint16_be(buffer, 0, NULL, 0));
    testrun(!ods_endian_write_uint16_be(NULL, size, NULL, 0));

    // buffer to small
    testrun(!ods_endian_write_uint16_be(buffer, 1, NULL, 0));

    // buffer min
    testrun(ods_endian_write_uint16_be(buffer, 2, NULL, 0));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);

    testrun(ods_endian_write_uint16_be(buffer, size, NULL, 1));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 1);

    testrun(ods_endian_write_uint16_be(buffer, size, NULL, 0x01FE));
    testrun(buffer[0] == 1);
    testrun(buffer[1] == 0xFE);
    testrun(buffer[2] == 0);

    testrun(ods_endian_write_uint16_be(buffer, size, NULL, 0xFACE));
    testrun(buffer[0] == 0xFA);
    testrun(buffer[1] == 0xCE);
    testrun(buffer[2] == 0);

    // write max
    testrun(ods_endian_write_uint16_be(buffer, size, &next, 0xFFFF));
    testrun(buffer[0] == 0xFF);
    testrun(buffer[1] == 0xFF);
    testrun(next == buffer + 2);

    // override
    testrun(ods_endian_write_uint16_be(buffer, size, &next, 0x1234));
    testrun(buffer[0] == 0x12);
    testrun(buffer[1] == 0x34);
    testrun(next == buffer + 2);

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_endian_write_uint32_be() {

    size_t size = 100;
    uint8_t buffer[size];
    memset(buffer, 0, size);
    uint8_t *next = NULL;

    testrun(!ods_endian_write_uint32_be(NULL, 0, NULL, 0));
    testrun(!ods_endian_write_uint32_be(buffer, 0, NULL, 0));
    testrun(!ods_endian_write_uint32_be(NULL, size, NULL, 0));

    // buffer to small
    testrun(!ods_endian_write_uint32_be(buffer, 3, NULL, 0));

    // buffer min
    testrun(ods_endian_write_uint32_be(buffer, 4, NULL, 0));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 1));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0x01);
    testrun(buffer[4] == 0);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 0x01FE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 1);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 0x01FEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 1);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 0x01FEFEFE));
    testrun(buffer[0] == 1);
    testrun(buffer[1] == 0xFE);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0);

    // MAX
    testrun(ods_endian_write_uint32_be(buffer, size, &next, 0xFFFFFFFF));
    testrun(buffer[0] == 0xff);
    testrun(buffer[1] == 0xff);
    testrun(buffer[2] == 0xff);
    testrun(buffer[3] == 0xff);
    testrun(buffer[4] == 0);
    testrun(next == buffer + 4);

    // OVERRIDE
    testrun(ods_endian_write_uint32_be(buffer, size, &next, 0xface1234));
    testrun(buffer[0] == 0xfa);
    testrun(buffer[1] == 0xce);
    testrun(buffer[2] == 0x12);
    testrun(buffer[3] == 0x34);
    testrun(buffer[4] == 0);
    testrun(next == buffer + 4);
    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_endian_write_uint64_be() {

    size_t size = 100;
    uint8_t buffer[size];
    memset(buffer, 0, size);
    uint8_t *next = NULL;

    testrun(!ods_endian_write_uint64_be(NULL, 0, NULL, 0));
    testrun(!ods_endian_write_uint64_be(buffer, 0, NULL, 0));
    testrun(!ods_endian_write_uint64_be(NULL, size, NULL, 0));

    // buffer to small
    testrun(!ods_endian_write_uint64_be(buffer, 7, NULL, 0));

    // buffer min
    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 0);
    testrun(buffer[6] == 0);
    testrun(buffer[7] == 0);
    testrun(buffer[8] == 0);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 1));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 0);
    testrun(buffer[6] == 0);
    testrun(buffer[7] == 1);
    testrun(buffer[8] == 0);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 0);
    testrun(buffer[6] == 1);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 1);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 1);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 1);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 1);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 1);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 1);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFEFEFEFE));
    testrun(buffer[0] == 1);
    testrun(buffer[1] == 0xFE);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0xFEFEFEFEFEFEFEFE));
    testrun(buffer[0] == 0xFE);
    testrun(buffer[1] == 0xFE);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_endian_read_uint64_be() {

    size_t size = 100;
    uint8_t buffer[size];
    memset(buffer, 0, size);
    uint8_t *next = NULL;

    uint64_t number = 0;

    testrun(!ods_endian_read_uint64_be(NULL, 0, NULL));
    testrun(!ods_endian_read_uint64_be(buffer, 0, &number));
    testrun(!ods_endian_read_uint64_be(NULL, size, &number));
    testrun(!ods_endian_read_uint64_be(buffer, size, NULL));

    // buffer to small
    testrun(!ods_endian_read_uint64_be(buffer, 7, &number));

    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 0);
    testrun(buffer[6] == 0);
    testrun(buffer[7] == 0);
    testrun(buffer[8] == 0);

    // buffer min
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0 == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 1));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 0);
    testrun(buffer[6] == 0);
    testrun(buffer[7] == 1);
    testrun(buffer[8] == 0);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(1 == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 0);
    testrun(buffer[6] == 1);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 1);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FEFE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(buffer[5] == 1);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FEFE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, NULL, 0x01FEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 1);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FEFEFE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 1);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FEFEFEFE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 1);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FEFEFEFEFE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFEFEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 1);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FEFEFEFEFEFE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01FEFEFEFEFEFEFE));
    testrun(buffer[0] == 1);
    testrun(buffer[1] == 0xFE);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01FEFEFEFEFEFEFE == number);

    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0xFEFEFEFEFEFEFEFE));
    testrun(buffer[0] == 0xFE);
    testrun(buffer[1] == 0xFE);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(buffer[4] == 0xFE);
    testrun(buffer[5] == 0xFE);
    testrun(buffer[6] == 0xFE);
    testrun(buffer[7] == 0xFE);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0xFEFEFEFEFEFEFEFE == number);

    // check max
    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0xFFFFFFFFFFFFFFFF));
    testrun(buffer[0] == 0xFF);
    testrun(buffer[1] == 0xFF);
    testrun(buffer[2] == 0xFF);
    testrun(buffer[3] == 0xFF);
    testrun(buffer[4] == 0xFF);
    testrun(buffer[5] == 0xFF);
    testrun(buffer[6] == 0xFF);
    testrun(buffer[7] == 0xFF);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0xFFFFFFFFFFFFFFFF == number);

    // check override
    testrun(ods_endian_write_uint64_be(buffer, 8, &next, 0x01));
    testrun(buffer[0] == 0x00);
    testrun(buffer[1] == 0x00);
    testrun(buffer[2] == 0x00);
    testrun(buffer[3] == 0x00);
    testrun(buffer[4] == 0x00);
    testrun(buffer[5] == 0x00);
    testrun(buffer[6] == 0x00);
    testrun(buffer[7] == 0x01);
    testrun(buffer[8] == 0);
    testrun(next == buffer + 8);
    testrun(ods_endian_read_uint64_be(buffer, 8, &number));
    testrun(0x01 == number);

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_endian_read_uint16_be() {

    size_t size = 100;
    uint8_t buffer[size];
    memset(buffer, 0, size);

    uint16_t number = 0;

    testrun(!ods_endian_read_uint16_be(NULL, 0, NULL));
    testrun(!ods_endian_read_uint16_be(buffer, 0, &number));
    testrun(!ods_endian_read_uint16_be(NULL, size, &number));
    testrun(!ods_endian_read_uint16_be(buffer, size, NULL));

    // buffer to small
    testrun(!ods_endian_read_uint16_be(buffer, 1, &number));

    // buffer min
    testrun(ods_endian_write_uint16_be(buffer, 2, NULL, 0));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(ods_endian_read_uint16_be(buffer, 2, &number));
    testrun(number == 0);

    testrun(ods_endian_write_uint16_be(buffer, size, NULL, 1));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 1);
    testrun(ods_endian_read_uint16_be(buffer, 2, &number));
    testrun(number == 1);

    testrun(ods_endian_write_uint16_be(buffer, size, NULL, 0x01FE));
    testrun(buffer[0] == 1);
    testrun(buffer[1] == 0xFE);
    testrun(ods_endian_read_uint16_be(buffer, 2, &number));
    testrun(number == 0x01FE);

    testrun(ods_endian_write_uint16_be(buffer, size, NULL, 0xFACE));
    testrun(buffer[0] == 0xFA);
    testrun(buffer[1] == 0xCE);
    testrun(ods_endian_read_uint16_be(buffer, 2, &number));
    testrun(number == 0xFACE);

    // max
    testrun(ods_endian_write_uint16_be(buffer, size, NULL, 0xFFFF));
    testrun(buffer[0] == 0xFF);
    testrun(buffer[1] == 0xFF);
    testrun(ods_endian_read_uint16_be(buffer, 2, &number));
    testrun(number == 0xFFFF);

    return testrun_log_success();
}

/*----------------------------------------------------------------------------*/

int test_ods_endian_read_uint32_be() {

    size_t size = 100;
    uint8_t buffer[size];
    memset(buffer, 0, size);

    uint32_t number = 0;

    testrun(!ods_endian_read_uint32_be(NULL, 0, NULL));
    testrun(!ods_endian_read_uint32_be(buffer, 0, &number));
    testrun(!ods_endian_read_uint32_be(NULL, size, &number));
    testrun(!ods_endian_read_uint32_be(buffer, size, NULL));

    // buffer to small
    testrun(!ods_endian_read_uint32_be(buffer, 3, &number));

    // buffer min
    testrun(ods_endian_write_uint32_be(buffer, 4, NULL, 0));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0);
    testrun(buffer[4] == 0);
    testrun(ods_endian_read_uint32_be(buffer, 4, &number));
    testrun(number == 0);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 1));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 0);
    testrun(buffer[3] == 0x01);
    testrun(ods_endian_read_uint32_be(buffer, 4, &number));
    testrun(number == 1);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 0x01FE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 0);
    testrun(buffer[2] == 1);
    testrun(buffer[3] == 0xFE);
    testrun(ods_endian_read_uint32_be(buffer, 4, &number));
    testrun(number == 0x01FE);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 0x01FEFE));
    testrun(buffer[0] == 0);
    testrun(buffer[1] == 1);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(ods_endian_read_uint32_be(buffer, 4, &number));
    testrun(number == 0x01FEFE);

    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 0x01FEFEFE));
    testrun(buffer[0] == 1);
    testrun(buffer[1] == 0xFE);
    testrun(buffer[2] == 0xFE);
    testrun(buffer[3] == 0xFE);
    testrun(ods_endian_read_uint32_be(buffer, 4, &number));
    testrun(number == 0x01FEFEFE);

    // MAX
    testrun(ods_endian_write_uint32_be(buffer, size, NULL, 0xFFFFFFFF));
    testrun(buffer[0] == 0xff);
    testrun(buffer[1] == 0xff);
    testrun(buffer[2] == 0xff);
    testrun(buffer[3] == 0xff);
    testrun(ods_endian_read_uint32_be(buffer, 4, &number));
    testrun(number == 0xFFFFFFFF);

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

    testrun_test(test_ods_endian_write_uint16_be);
    testrun_test(test_ods_endian_write_uint32_be);
    testrun_test(test_ods_endian_write_uint64_be);

    testrun_test(test_ods_endian_read_uint16_be);
    testrun_test(test_ods_endian_read_uint32_be);
    testrun_test(test_ods_endian_read_uint64_be);

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
