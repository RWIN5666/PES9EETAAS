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
#include "types.h"
#include "zigbee/zigbeeLib.h"
#include "zigbee/checksum.h"
#include "zigbee/fpgalib.h"
#include "serial0/serial0.h"
#include "dessinterminal/drawterminal.h"
#include "hexLib/hexLib.h"

// POUR SIMULER LE FONCTIONNEMENT
captorsList * listeCapteurs;
char * devname;
// MAIN
int main(int argc, char ** argv){
	printf("Lancement du programme Main...\n");
	// CHOIX PERIPHERIQUE POUR LE ZIGBEE
	if(argc < 1){
		printf("Please provide a dev name.\n");
		return 0;
	} 
	devname = argv[1];
	// POUR POUVOIR FACILEMENT ENVOYER VERS LE COORDINATEUR
    uint8_t destRequest[8];  
    destRequest[0] = 0x00;
	destRequest[1] = 0x00;
	destRequest[2] = 0x00;
	destRequest[3] = 0x00;
	destRequest[4] = 0x00;
	destRequest[5] = 0x00;
	destRequest[6] = 0x00;
	destRequest[7] = 0x00;

	//CREATION D'UNE LISTE DE CAPTEUR
	listeCapteurs = initCaptorsList();
	uint8_t question = 0x3F; // Pour pouvoir repondre a la demande '?'
	uint8_t numberCaptors = 0x01; // Nombre de capteurs

	// INITIALISATION D'UN UNIQUE CAPTEUR (A FAIRE POUR TOUS LES CAPTEURS)
	uint8_t id = ID_TEMPERATURE; // Type de capteur
	uint8_t unitData = 0x0C; // unite (ici en degre celsius)
	uint8_t dataSize = 0x02; // le nombre d'octets qui composent la donnee (ici 2)
	uint8_t minTemp[2]; // Valeurs min et max et leur affectation (on suppose dataSize = 0x02)
	uint8_t maxTemp[2];
	minTemp[0] = 0x00;
	minTemp[1] = 0x00;
	maxTemp[0] = 0x00;
	maxTemp[1] = 0x40;
	uint8_t fpgaName[2]; 	// Nom du FPGA (ici "#1")
	fpgaName[0] = 0x23;
	fpgaName[1] = 0x31;
	addCaptor(listeCapteurs,ID_TEMPERATURE,dataSize,unitData,minTemp,maxTemp);
	//showCaptor(listeCapteurs->premier); // Pour afficher les differents champs du capteur

	// A FAIRE POUR TOUS LES AUTRES CAPTEURS

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

	if(argc < 1){
		printf("Please provide a dev name.\n");
		return 0;
	} 
		
	char * devname = argv[1];
	printf("Lancement du programme DUMMYFPGA...\n");
	int xbeeRNE = serial_init(devname,9600);
	int * xbeeRNEPointer = &xbeeRNE;


	int count = 0;
	int finish = 0;
	while(!finish){
		printf("Count Value : %d", count);
		count++;
		struct TrameXbee * trameRetour = getTrame(xbeeRNEPointer);
		if(trameRetour){
				afficherTrame(trameRetour);
				// // FIN DU PROGRAMME
				uint8_t idRetour = trameRetour->header.frameID;
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

				    	uint8_t askCode = trameRetour->trameData[11];
				    	switch(askCode){
							case 0x3F :{
								// REQUETE INFO CAPTEUR
								printf("On a reçu une requete de demande d'infos sur les capteurs !\n");
								minTemp[0] = 0x00;
								minTemp[1] = 0x00;
								maxTemp[0] = 0x00;
								maxTemp[1] = 0x40;
								uint8_t testString [11*2 +1];
								sprintf(&testString[0],"%02x",question);
								sprintf(&testString[2],"%02x",fpgaName[0]);
								sprintf(&testString[4],"%02x",fpgaName[1]);
								sprintf(&testString[6],"%02x",numberCaptors);
								sprintf(&testString[8],"%02x",id);
								sprintf(&testString[10],"%02x",dataSize);
								sprintf(&testString[12],"%02x",unitData);
								sprintf(&testString[14],"%02x",minTemp[0]);
								sprintf(&testString[16],"%02x",minTemp[1]);
								sprintf(&testString[18],"%02x",maxTemp[0]);
								sprintf(&testString[20],"%02x",maxTemp[1]);
								uint8_t bufferInfo[11];
					   			convertZeroPadedHexIntoByte(testString,bufferInfo);
								struct TrameXbee * atToSend = computeATTrame(0x19, destRequest,bufferInfo);
								sendTrame(xbeeRNEPointer, atToSend);
								break;
							}

							case 0x2A :{
							// REQUETE VALEUR CAPTEUR
							uint8_t capteurCode = trameRetour->trameData[12];
				    		fprintf(stderr, "Voici le code reçu : %02x\n", capteurCode);
				    		switch(capteurCode){
								case ID_TEMPERATURE :{
							    printf("On a recu une requête du maitre qui veut connaitre la temperature\n");
							    uint8_t valeur[2];
							    valeur[0] = 0x00;
							    valeur[1] = 0x3F;
							    uint8_t destRequest[8];
							    destRequest[0] = 0x00;
								destRequest[1] = 0x00;
								destRequest[2] = 0x00;
								destRequest[3] = 0x00;
								destRequest[4] = 0x00;
								destRequest[5] = 0x00;
								destRequest[6] = 0x00;
								destRequest[7] = 0x00;
								uint8_t testString [4*2 +1];
								sprintf(&testString[0],"%02x",0x2A);
								sprintf(&testString[2],"%02x",capteurCode);
								sprintf(&testString[4],"%02x",valeur[0]);
								sprintf(&testString[6],"%02x",valeur[1]);
								uint8_t bufferInfo[4];
		   						convertZeroPadedHexIntoByte(testString,bufferInfo);
							    struct TrameXbee * atToSend = computeATTrame(0x12, destRequest ,bufferInfo);
							    sendTrame(xbeeRNEPointer, atToSend);
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
							default:
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

	}


    printf("Fin Du Programme. Merci d'avoir participe au test!\n");
    close(xbeeRNE);
	
}



