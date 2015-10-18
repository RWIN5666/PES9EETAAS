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
	sentSize += tailleTemp;
	return sentSize;
}


void afficherTrame(struct TrameXbee * trameToPrint){

	if(trameToPrint != NULL){
		fprintf(stderr,"Header : %02x \n", trameToPrint->header.firstByte);
		fprintf(stderr,"Taille : %04x \n", trameToPrint->header.taille);
		fprintf(stderr,"Type : %02x \n", *(trameToPrint->trameData));
		trameToPrint->trameData++;

		if(trameToPrint->trameData[0] == 0x08){
			for(int k = 0; k<trameToPrint->header.taille-1 ; k++){
		 		fprintf(stderr,"%02x \n",*(trameToPrint->trameData));
		 		trameToPrint++;
			}
			fprintf(stderr,"Checksum : %02x \n", trameToPrint->checkSum);
		}
	
		if(trameToPrint->trameData[0] == 0x88){
				for(int k = 0; k<trameToPrint->header.taille-1 ; k++){
			 		fprintf(stderr,"%02x \n", *(trameToPrint->trameData));
			 		trameToPrint->trameData++;
				}
				fprintf(stderr,"Checksum : %02x \n", trameToPrint->checkSum);
			}
		printf("\n");
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
	printf("test debug\n");
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
	}
	return trameRetour;
}


