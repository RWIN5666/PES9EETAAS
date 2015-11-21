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
#include <unistd.h>

// include persos
#include "types.h"
#include "zigbee/zigbeeLib.h"
#include "zigbee/checksum.h"
#include "zigbee/fpgalib.h"
#include "serial0/serial0.h"
#include "dessinterminal/drawterminal.h"
#include "hexLib/hexLib.h"




// prototypes Threads & fonctions persos
void *thread_WebServer(void *arg);
void *thread_XBee(void *arg);



// TABLE DE MODULES FPGA
// On se dit qu'on en aura que 10 au maximum pour le moment...
int tailleTableau;
fpgaList * listeFPGA = NULL;
int premierPassage = 0;
int finish = 0;
int count = 0;
requestStruct requestTester; 	// POUR TESTER LES REQUETES RECUES PAR LE SERVEUR
								// LE THREAD SERVER METTRA A JOUR CES VALEURS POUR LA PARTIE ZIGBEE




// MAIN
int main(void){

	// INITIALISATION VALEURS
	tailleTableau = 0;
	listeFPGA = initFpgaList();
	// ON PREND LE CAS OU LE SERVEUR VEUT LA TEMPERATURE
	requestTester.requestFromServer = 0;
	requestTester.requestCode = ID_TEMPERATURE;
	requestTester.destRequest[0] = 0x00;
	requestTester.destRequest[1] = 0x00;
	requestTester.destRequest[2] = 0x00;
	requestTester.destRequest[3] = 0x00;
	requestTester.destRequest[4] = 0x00;
	requestTester.destRequest[5] = 0x00;
	requestTester.destRequest[6] = 0xFF;
	requestTester.destRequest[7] = 0xFF;
	pthread_mutex_init(&requestTester.mutex_server, NULL); /* Création du mutex */
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

    pthread_mutex_lock(&requestTester.mutex_server);
    for(int i = 0; i < 10000 ; i++){
    	i++;
    }
    pthread_mutex_unlock(&requestTester.mutex_server);

    pthread_exit(NULL);
}

void *thread_XBee(void *arg)
{
    printf("Nous sommes dans ce thread car vous etes prets a recevoir la connexion d'un FPGA.\n");
    /* Pour enlever le warning */
    (void) arg;
    // POUR TESTER LA CREATION D'UNE TRAME
    // printf("Test calcul checksum :\n");
    // Pour creer une trame on utilise la fonction computeTrame codee dans zigbeeLib.c
    // struct TrameXbee * computeTrame(uint16_t taille,uint8_t idFrame, char * trameData);
    // L'exemple suivant envoie une trame TX avec 010203 en donnée en broadcast
    //struct TrameXbee * trameTest = computeTrame(0x0011,0x10,"\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFE\x00\x00\x01\x02\x03");

	//Initialisation UART XBEE
	int xbeeCNE = serial_init("/dev/ttyUSB0",115200);
	int * xbeeCNEPointer = &xbeeCNE;
	struct TrameXbee * trameRetour = NULL;
	while(!finish){
 		pthread_mutex_lock(&requestTester.mutex_server);
		if(requestTester.requestFromServer){
			printf("On a reçu une requete du serveur\n");
			uint8_t code = requestTester.requestCode;
			requestTester.requestFromServer = 0;
			uint8_t * dest = requestTester.destRequest;
			sendCaptorInfoRequestFrame(xbeeCNEPointer, code, dest);
			printf("On a envoye la trame pour la requete serveur\n\n");
		}
		if(count == 20){
			requestTester.requestFromServer = 1;
		}
		if(count == 40){
			finish = 1;
		}
		count++;
		pthread_mutex_unlock(&requestTester.mutex_server);
		// ROUTINE CLASSIQUE D'ATTENTE DE TRAME RETOUR
		printf("Nous allons attendre une trame!\nAllez, c'est parti !\n");
		printf("Veuillez connecter un FPGA...\n\n");
		// ON S'ATTEND A RECUPERER UNE TRAME LORS DE LA CONNEXION
		trameRetour = getTrame(xbeeCNEPointer);
		if(trameRetour) traiterTrameRetour(requestTester, xbeeCNEPointer, trameRetour, listeFPGA);
		else printf("Pas de trame reçu on recommence !\n\n");
	}

	// FIN DU PROGRAMME 
	close(xbeeCNE);
    pthread_exit(NULL);
}
