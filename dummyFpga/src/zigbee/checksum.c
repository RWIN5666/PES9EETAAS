
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "zigbee/zigbeeLib.h"

int i;


uint8_t checksum (struct TrameXbee * trame) {
    
      
    uint32_t soustracteur = 0;
    int i;
    uint8_t bitDeStart  = trame->header.firstByte;
    assert(bitDeStart);
    fprintf(stderr,"bitDeStart  -> %02x\n",bitDeStart);
    uint16_t dataLength  = trame->header.taille;
    fprintf(stderr,"dataLenght  -> %04x\n",dataLength);
    uint8_t ID  = trame->header.frameID;
    fprintf(stderr,"Frame ID  -> %02x\n",ID);
    
    soustracteur += ID;
    for(i = 0; i < dataLength-1 ; i++){
        soustracteur += trame->trameData[i];
    }

    // d'apres le cours
    uint8_t check = 0xFF - (uint8_t)(soustracteur & 0xFF);

    fprintf(stderr,"Le checksum : %02x\n",check);



    return check;
      
}


    

