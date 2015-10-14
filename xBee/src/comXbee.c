/***********  comXbee.c ***********/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include "checksum.h"


// TABLE DE MODULES FPGA



struct termios oldattr;
struct __attribute__((packed)) HeaderXbee
{
	uint8_t firstByte;
	uint16_t taille;
};

struct __attribute__((packed)) TrameXbee
{
	struct HeaderXbee header;
	uint8_t * trameData;
	uint8_t checkSum;
};





struct __attribute__((packed)) moduleFPGA 
{
	uint8_t myFPGA[2];
	uint8_t destFPGA[8];
};

struct moduleFPGA tableauFPGA[10];

void afficherTrame(struct TrameXbee * trameToPrint);

struct TrameXbee * computeTrame(uint16_t taille, uint8_t type, char * trameData){
	struct TrameXbee * trame = malloc(sizeof(struct TrameXbee));
	trame->trameData = malloc(sizeof(uint8_t)*(taille));
	trame->header.firstByte = 0x7E;
	trame->header.taille = taille;
	for(int i = 0;i<taille;i++){
		trame->trameData[i] = (char)trameData[i];
	}

	// TODO: rajouter appel à la fonction de la fonction checkSum ici quand les tests seront bons
	trame->checkSum = 0x50;	
	return trame;
}


int sendTrame(int xbeeToUse, struct TrameXbee * trameToSend){
	printf("Je vais ecrire une trame\n");
	int taille = write(xbeeToUse,trameToSend, trameToSend->header.taille + 4);
	printf("Voici la trame qui a ete envoyee : \n");
	afficherTrame(trameToSend);
	return taille;
}


void afficherTrame(struct TrameXbee * trameToPrint){

	if(trameToPrint != NULL){

	// fprintf(stderr,"%02x \n", trameToPrint->header.firstByte);
	// fprintf(stderr,"%04x \n", trameToPrint->header.taille);
	// fprintf(stderr,"%02x \n", trameToPrint->header.type);

	int taille = (int)(trameToPrint->header.taille);
	printf("voici la taille : %d\n",taille);

	for(int k = 0; k<taille+4 ; k++){
		 fprintf(stderr,"%02x \n",*((uint8_t*)(trameToPrint)));
		 trameToPrint++;
	}

	// fprintf(stderr,"%02x \n",trameToPrint);
	printf("\n");
	}

}

struct TrameXbee * getTrame(int usedXbee){

	struct pollfd fds[1];
	fds[0].fd = usedXbee;
	fds[0].events = POLLIN;
	struct TrameXbee * trameRetour = malloc(sizeof(struct TrameXbee));
	
	int retour = poll(fds,(nfds_t) 1, (int)100);
	if(retour == -1){ 
			perror("error");
		return NULL;
	}
	
	if(fds[0].revents & POLLIN){
	// on recupere lentete de la trame
	uint8_t buffer[5];
	if (!read(fds[0].fd, buffer, 5)) {
		perror("error header");
		return NULL;
	}


	trameRetour->header.firstByte = buffer[0];
	trameRetour->header.taille = ((uint16_t)buffer[1] << 8) | buffer[2];



	trameRetour->trameData = malloc((trameRetour->header.taille)*sizeof(uint8_t));
	if (!read(fds[0].fd, trameRetour->trameData, trameRetour->header.taille - 1)) {
		perror("error frame");
		return NULL;
		}
	}

	return trameRetour;
}





static int serial_init(const char *devname, speed_t baudrate)
{
	int fd;
	struct termios newattr;
	if((fd = open(devname, O_RDWR | O_NOCTTY)) < 0) {
		perror("Failed to open serial port");
		exit(EXIT_FAILURE);
	} else if(tcgetattr(fd, &oldattr) != 0) {
		perror("Failed to get configuration");
		exit(EXIT_FAILURE);
	}
	newattr = oldattr;

	cfsetispeed(&newattr, baudrate);
	cfsetospeed(&newattr, baudrate);
	newattr.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
    newattr.c_oflag &= ~OPOST;
    newattr.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    newattr.c_cflag &= ~(CSIZE | PARENB | HUPCL);
    newattr.c_cflag |= CS8;
    newattr.c_cc[VMIN]  = 50;
    newattr.c_cc[VTIME] = 10;

	if(tcsetattr(fd, TCSANOW, &newattr) != 0) {
		perror("Failed to set configuration");
		exit(EXIT_FAILURE);
	}

	tcflush(fd,TCIOFLUSH);

	return fd;
}


//int argc, char * argv[]
int main(void){




	/*Initialisation UART XBEE */
	int xbee1 = serial_init("/dev/ttyUSB0",9600);

	// Outil pour creer une trame : computeTrame(uint16_t taille, uint8_t type, uint8_t * trameData)
	// On envoie cette trame pour le test : 7E 00 04 08 01 4D 59 50
	//TODO : calculer la taille de la chaine envoyee
	
	struct TrameXbee * trameTest = computeTrame(0x0004, 0x08, "\x08\x01\x4D\x59");
	

	//on va envoyer la trame créée avec sendTrame(int xbeeToUse, struct TrameXbee * trameToSend){
	sendTrame(xbee1, trameTest);


	// ON VEUT RECUPERER LA TRAME RETOUR
	struct TrameXbee * trameRetour = getTrame(xbee1);

	// j'essaie d'afficher la trame trouvee
	afficherTrame(trameRetour);
	// FIN DU PROGRAMME
	free(trameTest);
	close(xbee1);

}