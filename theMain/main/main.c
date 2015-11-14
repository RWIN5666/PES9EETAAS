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
	int xbeeCNE = serial_init("/dev/ttyUSB0",9600);
	int * xbeeCNEPointer = &xbeeCNE;
	struct TrameXbee * trameRetour = NULL;
	while(!finish){
 		pthread_mutex_lock(&requestTester.mutex_server);
		if(requestTester.requestFromServer){
			printf("On a reçu une requete du serveur\n");
			uint8_t code = requestTester.requestCode;
			fprintf(stderr,"code : %02x\n", code);
			uint8_t testString [2*2 +1];
			sprintf(&testString[0],"%02x",0x2A);
			sprintf(&testString[2],"%02x",code);
			uint8_t bufferInfo[2];
   			convertZeroPadedHexIntoByte(testString,bufferInfo);
			uint8_t * dest = requestTester.destRequest;
			struct TrameXbee * atToSend = computeATTrame(0x0010, dest,bufferInfo);
			requestTester.requestFromServer = 0;
			sendTrame(xbeeCNEPointer, atToSend);
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

		if(trameRetour){
			afficherTrame(trameRetour);
			// // FIN DU PROGRAMME
			uint8_t idRetour = trameRetour->header.frameID;
			switch(idRetour){
			    case ID_NI :{
			    // ARRIVEE D'UN NOUVEAU FPGA DANS LE RESEAU, ON VA METTRE A JOUR LA TABLE
			    	printf("J'ai recu une trame\n");
			    	uint8_t destFPGA[8];
					uint8_t myFPGA[2];
					copyMyandDest(myFPGA, destFPGA, trameRetour);
				    struct moduleFPGA * nouveau = computeModule(myFPGA,destFPGA);
				    addFpga(listeFPGA,nouveau);
				    sleep(10);
				    //struct TrameXbee * trameTest = computeTrame(0x0011,0x10,"\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFE\x00\x00\x01\x02\x03");
				   // struct TrameXbee * trameTest = computeTrame(0x000F,0x10,"\x01\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFE\x00\x00\x3F");
				    printf("On a un nouveau FPGA\n");
					uint8_t code = requestTester.requestCode;
					fprintf(stderr,"code : %02x\n", code);
					uint8_t testString [1*2 +1];
					sprintf(&testString[0],"%02x",0x3F);
					uint8_t bufferInfo[1];
		   			convertZeroPadedHexIntoByte(testString,bufferInfo);
				   	struct TrameXbee * trameTest = computeATTrame(0x000F,destFPGA,bufferInfo);
					//on va envoyer la trame créée avec sendTrame(int xbeeToUse, struct TrameXbee * trameToSend)
					sendTrame(xbeeCNEPointer, trameTest);
					trameRetour = getTrame(xbeeCNEPointer);
					printf("Avant de checker le resultat\n");
					fprintf(stderr,"Test : %02x\n", trameRetour->trameData[11]);
					if(trameRetour->trameData[11] != 0x3F){
						printf("On a eu autre chose\n");
						trameRetour = getTrame(xbeeCNEPointer);
						while(trameRetour == NULL){
							trameRetour = getTrame(xbeeCNEPointer);
						}
						printf("On a recupere une autre trame\n\n");
						afficherTrame(trameRetour);
					}
			       	if(trameRetour->trameData[11] == 0x3F){
			       		printf("On recoit une reponse a la requete ?\n");
			       		captorsList * capList = initCaptorsList();
			       		uint8_t numberCaptors = trameRetour->trameData[12];
			       		uint8_t tempSize = 0x00;
			       		// BOUCLE POUR CHAQUE CAPTEUR
			       		for(int i = 0; i < (int)numberCaptors; i++){
			       		uint8_t id = trameRetour->trameData[13+i*(2*tempSize+3)];
			       		uint8_t dataSize = trameRetour->trameData[14+i*(2*tempSize+3)];
			       		tempSize += dataSize;
			       		uint8_t unit = trameRetour->trameData[15+i*(2*tempSize+3)];
			       		uint8_t * minValue = trameRetour->trameData + (16+i*(2*tempSize+3));
			       		uint8_t * maxValue = trameRetour->trameData + (16+dataSize+i*(2*tempSize+3));
			       		addCaptor(capList, id, dataSize, unit, minValue, maxValue);
			       		showCaptor(capList->premier);
			       	}
			       		addCaptorsListToFpga(nouveau, numberCaptors, capList);
			       	}
			       	else {printf("Ce n'est pas une requete comme prevu...\n\n");}
			       	requestTester.requestFromServer = 1;
			       	break;
			       }

			    case ID_TX_STATUS :{
			    	if (trameRetour->trameData[4] == 0x00){
			    		printf("La trame a bien ete transmise\n\n");

			    	} 			    	
			    	break;
			    }

			    case ID_RX :{
			    	printf("On a recu une trame RX.\n\n");
			    	// NUMERO OCTET A DETERMINER
			    	uint8_t action = trameRetour->trameData[11];
			    	fprintf(stderr,"Valeur de l'octet RX : %02x\n", trameRetour->trameData[11]);
			    	switch(action){
			    		case INFO_FPGA_REQUEST:{
			    			printf("FPGA_REQUEST : On aurait pas du avoir cela ici\n");
			       			break;
			       			}
			       		case INFO_CAPTOR_REQUEST:{
			    			printf("CAPTOR_REQUEST : On va recuperer la valeur\n");
			    			uint8_t typeCapteur = trameRetour->trameData[12];
			    			uint8_t destTemp[8];
			    			getDest(destTemp, trameRetour);
			    			uint8_t  sizeRetour;
			    			uint8_t  unitRetour;
			    			getUnitAndSize(destTemp, typeCapteur, listeFPGA, &unitRetour, &sizeRetour);
			    			fprintf(stderr,"sizeRetour : %02x\n", sizeRetour);
			    			fprintf(stderr, "unitRetour : %02x\n",unitRetour);
			    			if((sizeRetour!=0x00) && (unitRetour!=0x00)){
			    				switch(typeCapteur){
					    		case ID_TEMPERATURE:{
					    			printf("On a la valeur retour pour la temperature\n");
					    			int taille = (int)(sizeRetour);
					    			uint8_t result[taille];
					    			getResult(result, taille, trameRetour);
					    			rev(result,taille);
					    			int resultatFinal = computeData(result,taille);



					    			// POUR TESTER LAFFICHAGE DE LA VALEUR
					    			if((unitRetour) == TEMP_KELVIN){
					    				printf("La temperature est de %d degrés KELVIN\n",resultatFinal);
					    			}
					    			if((unitRetour) == TEMP_CELSIUS){
					    				printf("La temperature est de %d degrés CELSIUS\n",resultatFinal);
					    			}
					    			if((unitRetour) == TEMP_FAHRENHEIT){
										printf("La temperature est de %d degrés FAHRENHEIT\n",resultatFinal);
					    			}


					    			//TODO: METTRE A JOUR LE FICHIER QUI STOCKE LES VALEURS

					    			
					       			break;
					       			}

					       		case ID_LIGHT:{
					    			printf("On a la valeur retour pour la lumiere\n");
					    			//TODO: METTRE A JOUR LE FICHIER QUI STOCKE LES VALEURS
					       			break;
					       			}
					       		case ID_GYRO:{
					    			printf("On a la valeur retour pour l'accelerometre\n");
					    			printf("Sur l'axe X : \n");
					    			printf("Sur l'axe Y : \n");
					    			printf("Sur l'axe Z : \n");
					    			//TODO: METTRE A JOUR LE FICHIER QUI STOCKE LES VALEURS
					       			break;
					       			}
					       		case ID_ANALOG:{
					    			printf("On a la valeur retour pour la valeur des potentiomètres\n");
					    			//TODO: METTRE A JOUR LE FICHIER QUI STOCKE LES VALEURS
					       			break;
					       			}
								default :  
					       			break;
			    				}
			    			}
			       			break;
			       			}
						default :  
			       			break;
			    	}
			    	break;
			    }
			    default :  
			       break;
			}

		}
		else printf("Pas de trame reçu on recommence !\n\n");
	}


	// FIN DU PROGRAMME 
	close(xbeeCNE);
    pthread_exit(NULL);
}