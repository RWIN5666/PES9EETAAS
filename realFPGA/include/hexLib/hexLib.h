#ifndef HEXLIB_H
#define HEXLIB_H

#include <stdint.h>

typedef unsigned char u8;

u8 a(char **b);
void s2u(char *s, u8 *o);
int charToByteArray(unsigned int * bytearray,char *hexstring);
void convertZeroPadedHexIntoByte(char *dataset,uint8_t *bytearray);


#endif
