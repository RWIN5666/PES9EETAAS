/***********  main.c **********************

VOICI LE PROGRAMME MAIN QUI VA GERER LA COM
ZIGBEE AINSI QUE LES ECHANGES AVEC LA PAGE
WEB PAR WEBSOCKET

*******************************************/
// include standard
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include <assert.h>
#include <pthread.h>

// include persos
#include "zigbee/zigbeeLib.h"
#include "zigbee/checksum.h"
#include "serial0/serial0.h"
#include "dessinterminal/drawterminal.h"



// prototypes Threads & fonctions persos
void *thread_WebServer(void *arg);
void *thread_XBee(void *arg);





// TABLE DE MODULES FPGA
// On se dit qu'on en aura que 10 au maximum pour le moment...
struct moduleFPGA tableauFPGA[10];







// MAIN
int main(void){

	//POUR AFFICHER UN TRUC SYMPA AU LANCEMENT DU PROGRAMME
	char *filename = "main/image2.txt";
	FILE *fptr = NULL;
	if((fptr = fopen(filename,"r")) == NULL)
	  {
		fprintf(stderr,"error opening %s\n",filename);
		return 1;
	  }
	print_image(fptr);
	fclose(fptr);
	fprintf(stderr,"\n");
	printf("Lancement du programme 42main\n");
	



	// CREATIONS DES DEUX THREADS PRINCIPAUX
	// ET LEUR LANCEMENT
	pthread_t threadWebServer;
	pthread_t threadXBee;
    printf("Avant la création des threads.\n");
    if (pthread_create(&threadWebServer, NULL, thread_WebServer, NULL)) {
	    perror("pthread_create");
	    return EXIT_FAILURE;
    }
	if (pthread_create(&threadXBee, NULL, thread_XBee, NULL)) {
	    perror("pthread_create");
	    return EXIT_FAILURE;
    }
    if (pthread_join(threadWebServer, NULL)) {
	    perror("pthread_join");
	    return EXIT_FAILURE;
    }
    if (pthread_join(threadXBee, NULL)) {
	    perror("pthread_join");
	    return EXIT_FAILURE;
    }

    printf("Fin Du Programme. Merci d'avoir participe au test!\n");
	return EXIT_SUCCESS;

}



void *thread_WebServer(void *arg)
{
    printf("Nous sommes dans ce thread car vous avez demarre le WebServer.\n");

    /* Pour enlever le warning */
    (void) arg;
    pthread_exit(NULL);
}

void *thread_XBee(void *arg)
{
    printf("Nous sommes dans ce thread car vous etes prets a recevoir la connexion d'un FPGA.\n");
    /* Pour enlever le warning */
    (void) arg;

    // POUR TESTER LA CREATION D'UNE TRAME
    printf("Test calcul checksum :\n");
    struct TrameXbee * trameTest = computeTrame(0x0011,0x10,"\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFE\x00\x00\x01\x02\x03");

	// printf("Nous allons attendre une trame!\nAllez, c'est parti !\n");
	// /*Initialisation UART XBEE */
	// int xbee1 = serial_init("/dev/ttyUSB1",9600);
	// int * xbee1Pointer = &xbee1;
	// // Fonction pour creer une trame : computeTrame(uint16_t taille, uint8_t type, uint8_t * trameData)
	// // On envoie cette trame pour le test : 7E 00 04 08 01 4D 59 50
	// // TODO : calculer la taille de la chaine envoyee
	// // struct TrameXbee * trameTest = computeTrame(0x0004, "\x08\x01\x4D\x59");
	// // on va envoyer la trame créée avec sendTrame(int xbeeToUse, struct TrameXbee * trameToSend){
	// // sendTrame(xbee1Pointer, trameTest);
	// // ON VEUT RECUPERER LA TRAME RETOUR
	// printf("test\n");
	// struct TrameXbee * trameRetour = getTrame(xbee1Pointer);
	// // j'essaie d'afficher la trame trouvee
	afficherTrame(trameTest);
	// assert(trameRetour);
	// // FIN DU PROGRAMME
	// close(xbee1);


	printf("Veuillez connecter un FPGA...\n");

	
  


    pthread_exit(NULL);
}