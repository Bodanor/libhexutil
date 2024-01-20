#ifndef __HEX_UTIL_H__
#define __HEX_UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


typedef struct rawbyte_t {
    uint8_t *raw_bytes_array;
    uint64_t array_size;
}RawByte;


RawByte *convert_hex_array_from_string(const char *string_bytes);
void print_rawbytes(RawByte *rawbyte);

#endif