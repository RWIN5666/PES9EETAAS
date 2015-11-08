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
#include "zigbee/fpgalib.h"
#include "serial0/serial0.h"
#include "dessinterminal/drawterminal.h"
#include "hexLib/hexLib.h"

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


	printf("Lancement du programme DUMMYFPGA\n");
	int xbeeRNE = serial_init("/dev/ttyUSB1",9600);
	int * xbeeRNEPointer = &xbeeRNE;
	struct TrameXbee * trameRetour = getTrame(xbeeRNEPointer);

	if(trameRetour){
			afficherTrame(trameRetour);
			// // FIN DU PROGRAMME
			uint8_t idRetour = trameRetour->header.frameID;
			uint8_t destFPGA[8];
			uint8_t myFPGA[2];
			switch(idRetour){
			    case ID_NI :{
			    // ARRIVEE D'UN NOUVEAU FPGA DANS LE RESEAU, ON VA METTRE A JOUR LA TABLE
			    // ICI ON NE SERA PAS DANS CE CAS LA
			       	break;
			       }
			    case ID_TX_STATUS :{
			    	if (trameRetour->trameData[4] == 0x00){
			    		printf("La trame a bien ete tranmise");
			    	} 			    	
			    	break;
			    }

			    case ID_RX :{
			    	uint8_t capteurCode = trameRetour->trameData[11];
			    	fprintf(stderr, "Voici le code reçu : %02x\n", capteurCode);
			    	switch(capteurCode){
						case ID_TEMPERATURE :{
					    printf("On a recu une requête du maitre qui veut connaitre la temperature\n");
					    uint8_t valeur = 0xEF;
					    uint8_t destRequest[8];
					    destRequest[0] = 0x00;
						destRequest[1] = 0x00;
						destRequest[2] = 0x00;
						destRequest[3] = 0x00;
						destRequest[4] = 0x00;
						destRequest[5] = 0x00;
						destRequest[6] = 0x00;
						destRequest[7] = 0x00;
						uint8_t testString [3*2 +1];
						sprintf(&testString[0],"%02x",0x2A);
						sprintf(&testString[2],"%02x",capteurCode);
						sprintf(&testString[4],"%02x",valeur);
						uint8_t bufferInfo[3];

   						convertZeroPadedHexIntoByte(testString,bufferInfo);

					    struct TrameXbee * atToSend = computeATTrame(0x10, destRequest ,bufferInfo);
					    break;
					    }
					    case ID_LIGHT :{
					 	printf("On a recu une requête du maitre qui veut connaitre la luminosite\n");
					    break;
					    }
					    case ID_GYRO :{
						printf("On a recu une requête du maitre qui veut connaitre l'orientation\n");
					    break;
					    }
					    case ID_ANALOG :{
					   	printf("On a recu une requête du maitre qui veut connaitre la valeur analogique\n");
					    break;
					    }
					    default :  
					    printf("ERREUR PAS DE CAPTEUR ICI...\n");
			       		break;
			    	}

			    	break;
			    }

			    default :  
			       break;
			}
		}
		else {
			printf("Pas de trame reçu on recommence !\n");
		}

		
    printf("Fin Du Programme. Merci d'avoir participe au test!\n");
    close(xbeeRNE);
	
}



