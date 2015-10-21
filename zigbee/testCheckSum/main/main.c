/***********  comXbee.c ***********/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include <stdint.h>

#include "zigbee/zigbeeLib.h"
#include "zigbee/checksum.h"


#define MAX_LEN 128



void print_image(FILE *fptr);
// static int serial_init(const char *devname, speed_t baudrate);




int main(int argc, char**argv){


	 char *filename = "main/image2.txt";
	 FILE *fptr = NULL;
	 
	 if((fptr = fopen(filename,"r")) == NULL)
	  {
		fprintf(stderr,"error opening %s\n",filename);
		return 1;
	    }
	 
	 print_image(fptr);
	 
	 fclose(fptr);

	printf("Lancement du programme de test CheckSum\n");


	// Trame Test envoie donnée : 7E 00 11 10 01 00 00 00 00 00 00 FF FF FF FE 00 00 01 02 03 ED
	struct TrameXbee * trameTest = computeTrame(0x0011, "\x10\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFE\x00\x00\x01\x02\x03");


	uint8_t* chaine = (uint8_t*) argv[1];
    int i = 0;    
     while(chaine[i] != '\0'){        
         i++;      
     }
    
     uint8_t test[i+2+1];    
     int  check = checksum(chaine,test);   
     printf ("checksum : %x\n", check );
     printf ("chaine : %s\n", test );
     return 0;

}


void print_image(FILE *fptr)
{
    	char read_string[MAX_LEN];
    	while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}




