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



struct TrameXbee * computeTrame(uint16_t taille, uint8_t idFrame, char * trameData){
	struct TrameXbee * trame = malloc(sizeof(struct TrameXbee) + sizeof(uint8_t)*(taille+1));
	trame->header.firstByte = 0x7E;
	trame->header.taille = taille;
	trame->header.frameID = idFrame;
	int writeSize = (int)taille;
	printf("Taille convertie : %d\n", writeSize);
	int i;
	for(i = 0;i<writeSize-1;i++){
		trame->trameData[i] = (char)trameData[i];
		//fprintf(stderr,"Caractere Hexa %d ecrit : %02x \n",i ,trame->trameData[i]);
	}
	uint8_t check = checksum(trame);   
	trame->trameData[i] = check;
	afficherTrame(trame);
	printf("Trame générée !\n\n");
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

	trame->trameData[1+i+j+1] = 0x00;
	trame->trameData[1+i+j+1+1] = 0x00;
	trame->trameData[1+i+j+1+1+1] = 0x2A;
	printf("Taille convertie : %d\n", writeSize);
	int k;
	for(k = 0;k<writeSize-1-i-j-1-1;k++){
		trame->trameData[1+i+j+k] = (uint8_t)data[k];	
	}
	uint8_t check = checksum(trame);   
	trame->trameData[i] = check;
	afficherTrame(trame);
	printf("Trame générée !\n\n");
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

	

	if((tailleTemp = write(*xbeeToUse,trameToSend->trameData, (trameToSend->header.taille+1)) == -1)){
		perror("error");
	}
	sentSize += tailleTemp;
	printf("Reste de la trame : ");
	int i = 0;
	for(i = 0;i<(trameToSend->header.taille + 1);i++){
		fprintf(stderr,"%02x ", trameToSend->trameData[i]);
	}

	// if((tailleTemp = write(*xbeeToUse,&(trameToSend->checkSum), 1)) == -1){
	// 	perror("error");
	// }
	//	sentSize += tailleTemp;



	printf("Envoi terminé !\n\n\n\n\n\n\n");
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
	
		printf("\n\n\n\n");
	}
}


struct TrameXbee * getTrame(int * usedXbee){

	
	struct pollfd fds[1];
	struct TrameXbee * trameRetour = NULL;
	fds[0].fd = *usedXbee;
	fds[0].events = POLLIN;
	int retour = 0;
	uint8_t bufferHeader[4];
	

	do{

		retour = poll(fds,(nfds_t) 1, (int)10000);
	}while(retour == 0);

	if(retour < 0){ 
			perror("error");
		return NULL;
	}
	

	if(fds[0].revents & POLLIN){
	// on recupere lentete de la trame
	
	if (!read(fds[0].fd, bufferHeader, 4)) {
		perror("error header");
		return NULL;
	}


	uint8_t premier = bufferHeader[0];
	uint16_t tailleData = ntohs(((uint16_t)bufferHeader[2] << 8) | bufferHeader[1]);
	uint8_t ID = bufferHeader[3];
	fprintf(stderr," taille data %04x\n", tailleData);


	trameRetour = malloc(sizeof(struct TrameXbee) + (tailleData +1)*sizeof(uint8_t));
	trameRetour->header.firstByte = premier;
	trameRetour->header.taille = tailleData;
	trameRetour->header.frameID = ID;

	int dataSize = (int) trameRetour->header.taille;

	printf("\n Taille de la donnée qui arrive : %d\n",dataSize+1);

	uint8_t bufferData[dataSize+1];
	if (!read(fds[0].fd, bufferData, trameRetour->header.taille + 1)) {
		perror("error frame");
		return NULL;
		}




	printf("Test Affichage bufferData :\n");
	for(int i = 0; i < dataSize + 1 ; i++){

		fprintf(stderr,"%02x ",bufferData[i]);

	}
	printf("\nFini !\n");


	printf("Copie dans la trame\n");

	for(int i = 0; i < dataSize + 1; i++){

		trameRetour->trameData[i] = bufferData[i];

	}

	// if (!read(fds[0].fd, bufferCheckSum, 1)) {
	// 	perror("error frame");
	// 	return NULL;
	// 	}
	// trameRetour->checkSum = bufferCheckSum[1];

	printf("Bonjour\n");
	afficherTrame(trameRetour);
	}

	return trameRetour;
}