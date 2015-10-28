
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "zigbee/zigbeeLib.h"

int i;

int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        //printf("result %d\n", result );
        return result;
}


/*int twoCharHex(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}*/


int subHextoInt(unsigned char * chaine, int start, int longueur, int octet)
{
    int resultat = 0;
    int temp = 0;
    int mult =1;
    i =0;

    for(int j = 0;j<= (longueur/octet -1);j++){
        
                i = start+ (octet-1) + (j)*octet;
                temp = 0; 
                mult =1;
                for(   int i =0;i>=start + j*octet; i--){
                    
                        temp += (hex_to_int(chaine[i]) * mult); 
                        //printf("chaine[%d] = %c\n", i, chaine[i]);
                        mult = mult <<4  ;
                        
                }
                //printf("temp = %x\n", temp);
                resultat += temp;
    }
    
    
    return resultat;
    
}




uint8_t checksum2 (struct TrameXbee * trame,unsigned char *chaine, unsigned char *chaineFinale) {
    
      
    uint32_t soustracteur = 0;
    int i;
    uint8_t bitDeStart  = trame->header.firstByte;
    assert(bitDeStart);
    fprintf(stderr,"bitDeStart  -> %02x\n",bitDeStart);
    uint16_t dataLength  = trame->header.taille;
    fprintf(stderr,"dataLenght  -> %04x\n",dataLength);
    uint8_t ID  = trame->header.frameID;
    fprintf("Frame ID  -> %02x\n",ID);
    
    soustracteur += ID;
    for(i = 0; i < dataLength ; i++){
        soustracteur += trame->trameData[i];
    }

    uint8_t check = 0xFF - (uint8_t)(soustracteur & 0xFF);

    fprintf(stderr,"Le checksum : %02x\n",check);



    return check;
      
}

// EXEMPLE UTILISATION CHECKSUM
// int main(int argc, char* argv[])
// {
    
//     unsigned char* chaine = (unsigned char*) argv[1];
//     int i = 0;
    
//     while(chaine[i] != '\0'){
        
//         i++;
        
        
        
//     }
    
//     unsigned char test[i+2+1]; 
    
    
//     int  check = checksum(chaine,test);
     
     
     
//     printf ("checksum : %x\n", check );
//     printf ("chaine : %s\n", test );
//     return 0;
    
    
// }



    

