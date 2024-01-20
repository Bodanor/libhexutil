#include "hex_util.h"


static int offset_from_ascii_table(uint8_t c);

static int offset_from_ascii_table(uint8_t c)
{
    if (c >= 0x30 && c <= 0x39)
        return c - 0x30;
    else if (c >= 0x41 && c <= 0x46)
        return (c+10) - 0x41;
    else if (c >= 0x61 && c <= 0x66)
        return (c+10) - 0x61;
    else
        return -1;
}

static RawByte *alloc_rawbyte(const char *string_bytes);

static RawByte *alloc_rawbyte(const char *string_bytes)
{
    RawByte *bytes_array;
    size_t string_size;

    bytes_array = NULL;

    /*
     * One byte is 2 characters in the provided string (uint8_t size)
     * Also, if the provided string is of size 1, we round up to the smallest 
     * Integral value not less the length of the string
     */

    string_size = ceil((((float)strlen(string_bytes)) / 2));

    if (string_size != 0) {
        bytes_array = (RawByte*)malloc(sizeof(RawByte));
        if (bytes_array == NULL)
            return NULL;
        bytes_array->array_size = string_size;
        bytes_array->raw_bytes_array = (uint8_t*)malloc(sizeof(uint8_t) *string_size);
        if (bytes_array->raw_bytes_array == NULL)
            return NULL;
        
        return bytes_array;
    }
    return NULL;


}
RawByte *convert_hex_array_from_string(const char *string_bytes)
{
    RawByte *bytes_array;
    size_t i;
    size_t string_length;

    /* Check if string is null and assign the length to string_bytes */
    if (string_bytes == NULL || (string_length = strlen(string_bytes)) == 0)
        return NULL;


    #ifdef LIBHEXUTILDEBUG
        /* Get the length of the string, if odd, warn through stderror */
        if ((string_length) % 2  == 1){
            fprintf(stderr, "LIBCRYPTOUTIL (convert_hex_array_from_string) : Input length is odd !\n");
        }
    #endif

    /* Allocate enough bytes for the input */
    bytes_array = alloc_rawbyte(string_bytes);
    if (bytes_array == NULL)
        return NULL;
    
    for (i = 0; i < string_length / 2; i++)
        bytes_array->raw_bytes_array[i] = (offset_from_ascii_table(string_bytes[2 * i]) << 4) | offset_from_ascii_table(string_bytes[(2*i) + 1]);

    /* If is odd, we have one more character to process */
    if ((string_length % 2) != 0) {
        bytes_array->raw_bytes_array[string_length / 2] = offset_from_ascii_table(string_bytes[string_length - 1]);
    }
    return bytes_array;

}

void print_rawbytes(RawByte *rawbyte)
{
    uint64_t i;

    if (rawbyte != NULL || rawbyte->raw_bytes_array != NULL)
        for (i = 0; i < rawbyte->array_size; i++)
            putchar(rawbyte->raw_bytes_array[i]);
}