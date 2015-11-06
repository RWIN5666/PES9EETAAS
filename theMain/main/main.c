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
#include "zigbee/zigbeeLib.h"
#include "zigbee/checksum.h"
#include "zigbee/fpgalib.h"
#include "serial0/serial0.h"
#include "dessinterminal/drawterminal.h"


typedef struct
{
   int requestFromServer;
   uint8_t requestCode;
   uint8_t destRequest[8];
   pthread_mutex_t mutex_server;
}
requestStruct;

// prototypes Threads & fonctions persos
void *thread_WebServer(void *arg);
void *thread_XBee(void *arg);



// TABLE DE MODULES FPGA
// On se dit qu'on en aura que 10 au maximum pour le moment...
int tailleTableau;
fpgaList * listeFPGA = NULL;
int premierPassage = 0;
int finish = 0;
requestStruct requestTester;


// MAIN
int main(void){


	// INITIALISATION VALEURS
	tailleTableau = 0;
	listeFPGA = initFpgaList();

	requestTester.requestFromServer = 0;
	requestTester.requestCode = 0x00;
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
    for(int i = 0; i < 1000 ; i++){
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
	int xbeeCNE = serial_init("/dev/ttyUSB0",9600);
	int * xbeeCNEPointer = &xbeeCNE;

	while(!finish){
 		pthread_mutex_lock(&requestTester.mutex_server);
		if(requestTester.requestFromServer){
			printf("On a reçu une requete du serveur");
			uint8_t code = requestTester.requestCode;
			uint8_t * dest = requestTester.destRequest;
			struct TrameXbee * atToSend = computeATTrame(0x0F, dest,&code);
			sendTrame(xbeeCNEPointer, atToSend);
			}
		
		pthread_mutex_unlock(&requestTester.mutex_server);


		// ROUTINE CLASSIQUE D'ATTENTE DE TRAME RETOUR
		printf("Nous allons attendre une trame!\nAllez, c'est parti !\n");
		printf("Veuillez connecter un FPGA...\n");
		// ON S'ATTEND A RECUPERER UNE TRAME LORS DE LA CONNEXION
		struct TrameXbee * trameRetour = getTrame(xbeeCNEPointer);

		if(trameRetour){
			afficherTrame(trameRetour);
			// // FIN DU PROGRAMME
			uint8_t idRetour = trameRetour->header.frameID;
			uint8_t destFPGA[8];
			uint8_t myFPGA[2];
			switch(idRetour){
			    case ID_NI :{
			    // ARRIVEE D'UN NOUVEAU FPGA DANS LE RESEAU, ON VA METTRE A JOUR LA TABLE
			    	printf("J'ai recu une trame\n");
					copyMyandDest(myFPGA, destFPGA, trameRetour);
				    struct moduleFPGA * nouveau = computeModule(myFPGA,destFPGA);
				    addFpga(listeFPGA,nouveau);
				    sleep(10);
				    //struct TrameXbee * trameTest = computeTrame(0x0011,0x10,"\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFE\x00\x00\x01\x02\x03");
				    struct TrameXbee * trameTest = computeTrame(0x000F,0x10,"\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFE\x00\x00\x3F");
					//on va envoyer la trame créée avec sendTrame(int xbeeToUse, struct TrameXbee * trameToSend)
					sendTrame(xbeeCNEPointer, trameTest);

					sleep(10);
					
					trameRetour = getTrame(xbeeCNEPointer);
			       	if(trameRetour->trameData[12] == 0x3F){
			       		captorsList * capList = initCaptorsList();
			       		uint8_t numberCaptors = trameRetour->trameData[13];
			       		uint8_t tempSize = 0x00;
			       		// BOUCLE POUR CHAQUE CAPTEUR
			       		for(int i = 0; i < (int)numberCaptors; i++){
			       		uint8_t id = trameRetour->trameData[14+i*(2*tempSize+3)];
			       		uint8_t dataSize = trameRetour->trameData[15+i*(2*tempSize+3)];
			       		tempSize = dataSize;
			       		uint8_t unit = trameRetour->trameData[16+i*(2*tempSize+3)];
			       		uint8_t * minValue = trameRetour->trameData + (17+i*(2*tempSize+3));
			       		uint8_t * maxValue = trameRetour->trameData + (17+dataSize+i*(2*tempSize+3));
			       		addCaptor(capList, id, dataSize, unit, minValue, maxValue);
			       	}
			       		addCaptorsListToFpga(nouveau, numberCaptors, capList);
			       	}
			       	break;
			       }

			    case ID_TX_STATUS :{
			    	if (trameRetour->trameData[4] == 0x00){
			    		printf("La trame a bien ete tranmise");
			    	} 			    	
			    	break;
			    }

			    case ID_RX :{



			    	break;
			    }
			    default :  
			       break;
			}

		}
		else printf("Pas de trame reçu on recommence !\n");
	}



	close(xbeeCNE);
    pthread_exit(NULL);
}