/***********  comXbee.c ***********/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include <assert.h>
#include "zigbee/zigbeeLib.h"
#include "zigbee/checksum.h"
#include "serial0/serial0.h"


#define MAX_LEN 128



void print_image(FILE *fptr);
// static int serial_init(const char *devname, speed_t baudrate);



// TABLE DE MODULES FPGA
struct moduleFPGA tableauFPGA[10];


int main(void){

	// POUR AFFICHER UN TRUC SYMPA AU LANCEMENT DU PROGRAMME
	 // char *filename = "main/image2.txt";
	 // FILE *fptr = NULL;
	 
	 // if((fptr = fopen(filename,"r")) == NULL)
	 //  {
		// fprintf(stderr,"error opening %s\n",filename);
		// return 1;
	 //  }
	 
	 // print_image(fptr);
	 
	 // fclose(fptr);

	 // fprintf(stderr,"\n");

	printf("Lancement du programme de test XBEE\n");
	printf("Nous allons attendre une trame!\nAllez, c'est parti !\n");
	/*Initialisation UART XBEE */
	
	int xbee1 = serial_init("/dev/ttyUSB1",9600);
	int * xbee1Pointer = &xbee1;



	// Fonction pour creer une trame : computeTrame(uint16_t taille, uint8_t type, uint8_t * trameData)
	// On envoie cette trame pour le test : 7E 00 04 08 01 4D 59 50
	// TODO : calculer la taille de la chaine envoyee
	// struct TrameXbee * trameTest = computeTrame(0x0004, "\x08\x01\x4D\x59");
	// on va envoyer la trame créée avec sendTrame(int xbeeToUse, struct TrameXbee * trameToSend){
	// sendTrame(xbee1Pointer, trameTest);


	// ON VEUT RECUPERER LA TRAME RETOUR
	printf("test\n");
	struct TrameXbee * trameRetour = getTrame(xbee1Pointer);

	// j'essaie d'afficher la trame trouvee
	//afficherTrame(trameRetour);

	assert(trameRetour);

	// FIN DU PROGRAMME
	close(xbee1);

}


void print_image(FILE *fptr)
{
    	char read_string[MAX_LEN];
    	while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}



