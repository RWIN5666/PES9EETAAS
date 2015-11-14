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

    int timeSent = 0;
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