#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h>
#include "zigbee/zigbeeLib.h"

int hex_to_int(char c);
int subHextoInt(unsigned char * chaine, int start, int longueur, int octet);


uint8_t checksum2 (struct TrameXbee * trame);

#endif
