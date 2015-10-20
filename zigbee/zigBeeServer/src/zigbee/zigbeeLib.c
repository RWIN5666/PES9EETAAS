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
	struct TrameXbee * trame = malloc(sizeof(struct TrameXbee));
	trame->trameData = malloc(sizeof(uint8_t)*(taille));
	trame->header.firstByte = 0x7E;
	trame->header.taille = taille;

	int writeSize = (int) taille;
	printf("Taille convertie : %d\n", writeSize);
	int i;
	for(i = 0;i<writeSize;i++){
		trame->trameData[i] = (char)trameData[i];
		printf("Caractere Hexa %d ecrit : %02x \n",i ,trame->trameData[i]);
	}

	// TODO: rajouter appel à la fonction de la fonction checkSum ici quand les tests seront bons
	trame->checkSum = 0x50;	
	printf("Valeur Checksum : %02x \n", trame->checkSum);

	afficherTrame(trame);
	printf("Trame générée !\n\n\n\n\n");
	return trame;
}


int sendTrame(int * xbeeToUse, struct TrameXbee * trameToSend){
	printf("\n\n\nJe vais envoyer une Trame\n");
	int sentSize =0;
	int tailleTemp = 0;
	if((tailleTemp = write(*xbeeToUse,&trameToSend->header.firstByte,1)) == -1){
		perror("error");
	}
	printf("test\n");
	sentSize += tailleTemp;
	printf("Caractere Hexa ecrit : %02x \n", trameToSend->header.firstByte);
	if((tailleTemp = write(*xbeeToUse,&(trameToSend->header.taille),2)) == -1){
		perror("error");
	}
	sentSize += tailleTemp;
	printf("Caractere Hexa ecrit : %04x \n", trameToSend->header.taille);
	if((tailleTemp = write(*xbeeToUse,trameToSend->trameData, trameToSend->header.taille)) == -1){
		perror("error");
	}
	sentSize += tailleTemp;
	int i = 0;
	for(i = 0;i<trameToSend->header.taille;i++){
		printf("Caractere Hexa ecrit : %02x \n", trameToSend->trameData[i]);
	}
	sentSize += tailleTemp;
	printf("Caractere Hexa ecrit : %02x \n", trameToSend->checkSum);
	if((tailleTemp = write(*xbeeToUse,&(trameToSend->checkSum), 1)) == -1){
		perror("error");
	}
	printf("Envoi terminé !\n\n\n\n\n\n\n");
	sentSize += tailleTemp;
	return sentSize;
}


void afficherTrame(struct TrameXbee * trameToPrint){

	if(trameToPrint != NULL){
		printf("Voici votre trame : \n");
		fprintf(stderr,"%02x ", trameToPrint->header.firstByte);
		fprintf(stderr,"%02x ", trameToPrint->header.taille);
		for(int i = 0; i<trameToPrint->header.taille;i++){
			fprintf(stderr,"%02x ", trameToPrint->trameData[i]);
		}
		fprintf(stderr,"%02x ", trameToPrint->checkSum);
		printf("\n\n\n\n");
	}
}


struct TrameXbee * getTrame(int * usedXbee){

	printf("Je rentre dans getTrame\n");
	struct pollfd fds[1];
	fds[0].fd = *usedXbee;
	
	fds[0].events = POLLIN;
	uint8_t bufferHeader[3];
	uint8_t bufferCheckSum[1];
	struct TrameXbee * trameRetour = malloc(sizeof(struct TrameXbee));
	int retour = poll(fds,(nfds_t) 1, (int)100);
	if(retour == -1){ 
			perror("error");
		return NULL;
	}
	
	if(fds[0].revents & POLLIN){
	// on recupere lentete de la trame
	
	if (!read(fds[0].fd, bufferHeader, 3)) {
		perror("error header");
		return NULL;
	}

	trameRetour->header.firstByte = bufferHeader[0];
	trameRetour->header.taille = ((uint16_t)bufferHeader[1] << 8) | bufferHeader[2];

	int dataSize = (int) trameRetour->header.taille;
	printf("\n Taille de la donnée qui arrive : %d\n",dataSize);
	uint8_t bufferData[dataSize];

	trameRetour->trameData = malloc((trameRetour->header.taille)*sizeof(uint8_t));
	if (!read(fds[0].fd, bufferData, trameRetour->header.taille)) {
		perror("error frame");
		return NULL;
		}

	if (!read(fds[0].fd, bufferCheckSum, 1)) {
		perror("error frame");
		return NULL;
		}
	trameRetour->checkSum = bufferCheckSum[1];

	afficherTrame(trameRetour);
	}

	return trameRetour;
}


