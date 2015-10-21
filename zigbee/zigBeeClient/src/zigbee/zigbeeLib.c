#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include "zigbee/zigbeeLib.h"



struct TrameXbee * computeTrame(uint16_t taille, char * trameData){
	struct TrameXbee * trame = malloc(sizeof(struct TrameXbee) + sizeof(uint8_t)*(taille+1));
	trame->header.firstByte = 0x7E;
	trame->header.taille = taille;

	int writeSize = (int)taille + 1;
	printf("Taille convertie : %d\n", writeSize);
	int i;
	for(i = 0;i<writeSize+1;i++){
		trame->trameData[i] = (char)trameData[i];
		printf("Caractere Hexa %d ecrit : %02x \n",i ,trame->trameData[i]);
	}

	// TODO: rajouter appel à la fonction de la fonction checkSum ici quand les tests seront bons
	// trame->checkSum = 0x50;	
	// printf("Valeur Checksum : %02x \n", trame->checkSum);

	afficherTrame(trame);
	printf("Trame générée !\n\n\n\n\n");
	return trame;
}


int sendTrame(int * xbeeToUse, struct TrameXbee * trameToSend){

	int sentSize =0;
	int tailleTemp = 0;
	if((tailleTemp = write(*xbeeToUse,&trameToSend->header.firstByte,1)) == -1){
		perror("error");
	}
	sentSize += tailleTemp;
	printf("Caractere ecrit : %02x \n", trameToSend->header.firstByte);

	uint8_t tailleMSB = (uint8_t)(trameToSend->header.taille & 0xFF00) >> 8;
	uint8_t tailleLSB = (uint8_t)(trameToSend->header.taille & 0x00FF);

	
	if((tailleTemp = write(*xbeeToUse,&(tailleMSB),1)) == -1){
		perror("error");
	}
	sentSize += tailleTemp;
	printf("MSB : %02x \n", tailleMSB);

	if((tailleTemp = write(*xbeeToUse,&(tailleLSB),1)) == -1){
		perror("error");
	}

	printf("LSB : %02x \n", tailleLSB);

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
		printf("%02x ", trameToSend->trameData[i]);
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
		fprintf(stderr,"%02x ", trameToPrint->header.taille);
		for(int i = 0; i<(trameToPrint->header.taille + 1);i++){
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

	uint8_t bufferHeader[3];
	
	int retour = poll(fds,(nfds_t) 1, (int)10000);
	
	if(retour == -1){ 
			perror("error");
		return NULL;
	}
	

	fprintf(stderr,"erreur\n");
	if(fds[0].revents & POLLIN){
	// on recupere lentete de la trame
	
	if (!read(fds[0].fd, bufferHeader, 3)) {
		perror("error header");
		return NULL;
	}


	uint8_t premier = bufferHeader[0];
	uint16_t tailleData = (uint16_t)(((uint16_t)(bufferHeader[2] << 8)) | ((uint16_t)(bufferHeader[1])));

	fprintf(stderr," taille data %04x\n", tailleData);


	trameRetour = malloc(sizeof(struct TrameXbee) + (tailleData +1)*sizeof(uint8_t));
	trameRetour->header.firstByte = premier;
	trameRetour->header.taille = tailleData;

	printf("erreur\n");


	int dataSize = (int) trameRetour->header.taille;

	printf("\n Taille de la donnée qui arrive : %d\n",dataSize+1);

	uint8_t bufferData[dataSize+1];
	if (!read(fds[0].fd, bufferData, trameRetour->header.taille + 1)) {
		perror("error frame");
		return NULL;
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