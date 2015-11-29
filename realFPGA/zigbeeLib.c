#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include <netinet/in.h>
#include "zigbee/zigbeeLib.h"
#include "zigbee/checksum.h"
#include "hexLib/hexLib.h"
#include "zigbee/fpgalib.h"



struct TrameXbee * computeTrame(uint16_t taille, uint8_t idFrame, uint8_t * trameData){
	struct TrameXbee * trame = malloc(sizeof(struct TrameXbee) + sizeof(uint8_t)*(taille+1));
	trame->header.firstByte = 0x7E;
	trame->header.taille = taille;
	trame->header.frameID = idFrame;
	int writeSize = (int)taille;
	printf("Taille convertie : %d\n", writeSize);
	int i;
	for(i = 0;i<writeSize-1;i++){
		trame->trameData[i] = (uint8_t)trameData[i];
		//fprintf(stderr,"Caractere Hexa %d ecrit : %02x \n",i ,trame->trameData[i]);
	}
	uint8_t check = checksum(trame);   
	trame->trameData[i] = check;
	afficherTrame(trame);
	printf("Trame générée !\n");
	return trame;
}

struct TrameXbee * computeATTrame(uint16_t taille, uint8_t * dest, uint8_t * data){
	struct TrameXbee * trame = malloc(sizeof(struct TrameXbee) + sizeof(uint8_t)*(taille+1));
	trame->header.firstByte = 0x7E;
	trame->header.taille = taille;
	trame->header.frameID = 0x10;
	trame->trameData[0] = 0x01;
	uint8_t my[2];
	my[0] = 0xFF;
	my[1] = 0xFE;
	int i = 0;
	int j = 0;
	int writeSize = (int)taille;
	for(; i < 8 ; i++){
		trame->trameData[1+i] = dest[i];
	}
	for( ; j < 2 ; j++){
		trame->trameData[1+i+j] = my[j];
	}

	trame->trameData[1+i+j] = 0x00;
	trame->trameData[1+i+j+1] = 0x00;
	//trame->trameData[1+i+j+1+1] = 0x2A;
	printf("Taille convertie : %d\n", writeSize);
	int k;
	for(k = 0;k<writeSize-1-i-j-1-1;k++){
		trame->trameData[1+i+j+k+1+1] = (uint8_t)data[k];	
	}
	uint8_t check = checksum(trame);   
	trame->trameData[1+i+j+k+1] = check;
	afficherTrame(trame);
	printf("Trame générée !\n");
	return trame;
}






int sendTrame(int * xbeeToUse, struct TrameXbee * trameToSend){

	int sentSize =0;
	int tailleTemp = 0;
	if((tailleTemp = write(*xbeeToUse,&trameToSend->header.firstByte,1)) == -1){
		perror("error");
	}
	sentSize += tailleTemp;
	fprintf(stderr,"Caractere ecrit : %02x \n", trameToSend->header.firstByte);

	uint8_t tailleMSB = (uint8_t)(trameToSend->header.taille & 0xFF00) >> 8;
	uint8_t tailleLSB = (uint8_t)(trameToSend->header.taille & 0x00FF);
	
	if((tailleTemp = write(*xbeeToUse,&(tailleMSB),1)) == -1){
		perror("error");
	}
	sentSize += tailleTemp;
	fprintf(stderr,"MSB : %02x \n", tailleMSB);

	if((tailleTemp = write(*xbeeToUse,&(tailleLSB),1)) == -1){
		perror("error");
	}

	fprintf(stderr,"LSB : %02x \n", tailleLSB);

	sentSize += tailleTemp;
	// printf("Caractere Hexa ecrit : %04x \n", trameToSend->header.taille);
	// if((tailleTemp = write(*xbeeToUse,&(tailleLSB),1)) == -1){
	// 		perror("error");
	// 	}
	// sentSize += tailleTemp;

	if((tailleTemp = write(*xbeeToUse,&(trameToSend->header.frameID),1)) == -1){
		perror("error");
	}
	fprintf(stderr,"Frame Type : %02x \n", trameToSend->header.frameID);

	if((tailleTemp = write(*xbeeToUse,trameToSend->trameData, (trameToSend->header.taille+1)) == -1)){
		perror("error");
	}
	sentSize += tailleTemp;
	printf("Reste de la trame : ");
	int i = 0;
	for(i = 0;i<(trameToSend->header.taille);i++){
		fprintf(stderr,"%02x ", trameToSend->trameData[i]);
	}
	printf("\nEnvoi terminé !\n");
	return sentSize;
}


void afficherTrame(struct TrameXbee * trameToPrint){
	if(trameToPrint != NULL){
		printf("Voici votre trame : \n");
		fprintf(stderr,"%02x ", trameToPrint->header.firstByte);
		fprintf(stderr,"%04x ", trameToPrint->header.taille);
		fprintf(stderr,"%02x ", trameToPrint->header.frameID);
		for(int i = 0; i<(trameToPrint->header.taille);i++){
			fprintf(stderr,"%02x ", trameToPrint->trameData[i]);
		}
	
		printf("\n");
	}
}


struct TrameXbee * getTrame(int * usedXbee){

	struct pollfd fds[1];
	struct TrameXbee * trameRetour = NULL;
	fds[0].fd = *usedXbee;
	fds[0].events = POLLIN;
	int retour;
	int decallage = 0;
	uint8_t bufferHeader[4];
	retour = poll(fds, 1, 1000);
	if(retour < 0){ 
		perror("error poll");
	}
	else if(retour == 0){
		printf("Timeout ! Nothing was read !\n");
		return NULL;
	}
	else if(fds[0].revents & POLLIN){
		// on recupere lentete de la trame
		if (!read(fds[0].fd, bufferHeader, 4)) {
			perror("error header");
			return NULL;
		}


		if(bufferHeader[0]!=0x7E){

			decallage = 1;

		}

		uint8_t premier = 0x7E;
		uint16_t tailleData = ntohs(((uint16_t)bufferHeader[2-decallage] << 8) | bufferHeader[1-decallage]);
		uint8_t ID = bufferHeader[3-decallage];
		fprintf(stderr,"Taille data %04x\n", tailleData);
		trameRetour = malloc(sizeof(struct TrameXbee) + (tailleData+1)*sizeof(uint8_t));
		trameRetour->header.firstByte = premier;
		trameRetour->header.taille = tailleData;
		trameRetour->header.frameID = ID;
		fprintf(stderr,"Premier octet : %02x\n",trameRetour->header.firstByte);
		int dataSize = (int) trameRetour->header.taille;
		printf("\nTaille de la donnée qui arrive (checksum compris): %d\n",dataSize+1);
		uint8_t bufferData[dataSize+1];
		if (!read(fds[0].fd, bufferData, trameRetour->header.taille + 1 - decallage)) {
			perror("error frame");
			return NULL;
			}

		// printf("Test Affichage bufferData :\n");
		// for(int i = 0; i < dataSize + 1 ; i++){
		// 	fprintf(stderr,"%02x ",bufferData[i]);
		// }
		if(decallage){
			trameRetour->trameData[0] = bufferHeader[3];
			for(int i = 0; i < dataSize; i++){
			trameRetour->trameData[i+1] = bufferData[i];
			}
		}
		else {
			for(int i = 0; i < dataSize + 1; i++){
			trameRetour->trameData[i] = bufferData[i];
			}
		}
		afficherTrame(trameRetour);
	}
	else{
		printf("Un truc etrange s'est passe... !\n");
		return NULL;
	}

	return trameRetour;
}

int checkFPGAState(uint8_t * dest, int * xbeeCNEPointer){
    // We'll send 3 FPGA frames to check the suspicious FPGA
	
	uint8_t diagCode = DIAG_CODE;   
    struct TrameXbee * trameCheck = computeATTrame(0x0F, dest, &diagCode);

   // int timeSent = 0;
    int failCount = 0;

    sendTrame(xbeeCNEPointer, trameCheck);
    struct TrameXbee * trameCheckRetour = getTrame(xbeeCNEPointer);
    	
    while(failCount < 3){	
	    if(trameCheckRetour->header.frameID != 0x8B){
				printf("On examine la trame Transmit Status\n");
				if(trameCheckRetour->trameData[5] == 0x00){					
					return 1;
				}
				else{
					printf("Un echec de plus");
					failCount++;
					trameCheckRetour = getTrame(xbeeCNEPointer);
				}
			}

	}
	return 0;
}

int sendCaptorInfoRequestFrame(int * xbeeCNEPointer, uint8_t requestCode, uint8_t * dest){
	fprintf(stderr,"Request code : %02x\n", requestCode);
	uint8_t testString [2*2 +1];
	sprintf(&testString[0],"%02x",0x2A);
	sprintf(&testString[2],"%02x",requestCode);
	uint8_t bufferInfo[2];
	convertZeroPadedHexIntoByte(testString,bufferInfo);
	struct TrameXbee * atToSend = computeATTrame(0x0010, dest,bufferInfo);
	int sizeSent = sendTrame(xbeeCNEPointer, atToSend);

	if(sizeSent) return 0;
	else return -1;
}


int sendInfoCaptorValueFrame(int * xbeeRNEPointer, uint8_t * minTemp, uint8_t * maxTemp, uint8_t * fpgaName, uint8_t numberCaptors, uint8_t id, uint8_t tailleData,uint8_t unitData){
	// REQUETE INFO CAPTEUR
	printf("On a reçu une requete de demande d'infos sur les capteurs !\n");
	minTemp[0] = 0x00;
	minTemp[1] = 0x00;
	maxTemp[0] = 0x00;
	maxTemp[1] = 0x40;
	uint8_t destRequest[8];
	destRequest[0] = 0x00;
	destRequest[1] = 0x00;
	destRequest[2] = 0x00;
	destRequest[3] = 0x00;
	destRequest[4] = 0x00;
	destRequest[5] = 0x00;
	destRequest[6] = 0x00;
	destRequest[7] = 0x00;
	uint8_t question = 0x3F;
	uint8_t testString [11*2 +1];
	sprintf(&testString[0],"%02x",question);
	sprintf(&testString[2],"%02x",fpgaName[0]);
	sprintf(&testString[4],"%02x",fpgaName[1]);
	sprintf(&testString[6],"%02x",numberCaptors);
	sprintf(&testString[8],"%02x",id);
	sprintf(&testString[10],"%02x",tailleData);
	sprintf(&testString[12],"%02x",unitData);
	sprintf(&testString[14],"%02x",minTemp[0]);
	sprintf(&testString[16],"%02x",minTemp[1]);
	sprintf(&testString[18],"%02x",maxTemp[0]);
	sprintf(&testString[20],"%02x",maxTemp[1]);
	uint8_t bufferInfo[11];
		convertZeroPadedHexIntoByte(testString,bufferInfo);
	struct TrameXbee * atToSend = computeATTrame(0x19, destRequest,bufferInfo);
	int sizeSent = sendTrame(xbeeRNEPointer, atToSend);
	if(sizeSent) return 0;
	else return -1;





}



int traiterTrameRetour(struct requestStruct requestTester, int * toSetRequest, int * xbeePointer, struct TrameXbee * trameRetour, fpgaList * listeFPGA){

	// OK = 1, !OK = 0
	int codeRetour = 0;
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
					sendTrame(xbeePointer, trameTest);
					trameRetour = getTrame(xbeePointer);
					printf("Avant de checker le resultat\n");
					fprintf(stderr,"Test : %02x\n", trameRetour->trameData[11]);
					if(trameRetour->trameData[11] != 0x3F){
						printf("On a eu autre chose\n");
						trameRetour = getTrame(xbeePointer);
						while(trameRetour == NULL){
							trameRetour = getTrame(xbeePointer);
						}
						printf("On a recupere une autre trame\n\n");
						afficherTrame(trameRetour);
					}
			       	if(trameRetour->trameData[11] == 0x3F){
			       		printf("On recoit une reponse a la requete ?\n");
			       		captorsList * capList = initCaptorsList();
			     		setFpgaName(nouveau, trameRetour->trameData[12], trameRetour->trameData[13]);
			       		uint8_t numberCaptors = trameRetour->trameData[14];
			       		uint8_t tempSize = 0x00;
			       		// BOUCLE POUR CHAQUE CAPTEUR			       		
			       		for(int i = 0; i < (int)numberCaptors; i++){
			       		uint8_t id = trameRetour->trameData[15+i*(2*tempSize+3)];
			       		uint8_t dataSize = trameRetour->trameData[16+i*(2*tempSize+3)];
			       		tempSize += dataSize;
			       		uint8_t unit = trameRetour->trameData[17+i*(2*tempSize+3)];
			       		uint8_t * minValue = trameRetour->trameData + (18+i*(2*tempSize+3));
			       		uint8_t * maxValue = trameRetour->trameData + (18+dataSize+i*(2*tempSize+3));
			       		addCaptor(capList, id, dataSize, unit, minValue, maxValue);
			       		showCaptor(capList->premier);
			       	}
			       		addCaptorsListToFpga(nouveau, numberCaptors, capList);

			       	}
			       	else {printf("Ce n'est pas une requete comme prevu...\n\n");}
			       	requestTester.requestFromServer = 1;
			       	*toSetRequest = 1;
			       	codeRetour = 1;
			       		break;
			       }

			    case ID_TX_STATUS :{
			    	if (trameRetour->trameData[4] == 0x00){
			    		printf("La trame a bien ete transmise\n\n");
			    		codeRetour = 1;
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
					    			int resultatFinal = computeData(result,taille, typeCapteur);
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
					    			return 1;
					       			break;
					       			}
					       		case ID_GYRO:{
					    			printf("On a la valeur retour pour l'accelerometre\n");
					    			printf("Sur l'axe X : \n");
					    			printf("Sur l'axe Y : \n");
					    			printf("Sur l'axe Z : \n");
					    			//TODO: METTRE A JOUR LE FICHIER QUI STOCKE LES VALEURS;
					       			break;
					       			}
					       		case ID_ANALOG:{
					    			printf("On a la valeur retour pour la valeur des potentiomètres\n");
					    			//TODO: METTRE A JOUR LE FICHIER QUI STOCKE LES VALEURS
					       			break;
					       			}
								default :  ;
					       			break;
			    				}
			    			}
			       			break;
			       			}
						default :  
			       			break;
			    	}
			    	codeRetour = 1;
			    	break;
			    }
			    default :  
			    	codeRetour = 0;
			        break;
			}

		}
		else {
			printf("Il y a eu un petit souci\n");
			codeRetour = 1;
		}
		printf("On sort de traiterTrameRetour\n");
		return codeRetour;

}