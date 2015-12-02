#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include "hexLib/hexLib.h"
#include <stdint.h>

u8 a(char **b){ u8 r; if(**b>071) r= **b-0x37; else r = **b-060; (*b)++; return r; }
void s2u(char *s, u8 *o)
{
   for(;*s;o++) *o = (a(&s) << 4)|a(&s);
}




int charToByteArray(unsigned int * bytearray,char *hexstring){
    int i;
	
    uint8_t str_len = strlen(hexstring);

	memset(bytearray, 0x00, (int)sizeof(bytearray));

    for (i = 0; i < ((str_len / 2)-1); i++) {
        sscanf(hexstring + 2*i, "%02x", &bytearray[i]);
    }

    return 1;
}



void convertZeroPadedHexIntoByte(char *dataset,uint8_t *bytearray){
	int i = strlen(dataset),j=0,counter=0;
	char c[2];
	unsigned int bytes[2];

	for(j=0;j<i;j++){
		if(0 == j%2){

			c[0] = dataset[j];
			c[1] = dataset[j+1];

			sscanf(c, "%02x", &bytes[0]);

			bytearray[counter] = bytes[0];

			counter++;
		}
	}

}

