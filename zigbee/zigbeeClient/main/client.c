/***********  comXbee.c ***********/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include "zigbee/zigbeeLib.h"
#include "serial/serial0.h"

#define MAX_LEN 128



void print_image(FILE *fptr);
// static int serial_init(const char *devname, speed_t baudrate);

struct termios oldattr;

// TABLE DE MODULES FPGA
struct moduleFPGA tableauFPGA[10];


int main(void){


	 char *filename = "main/image2.txt";
	 FILE *fptr = NULL;
	 
	 if((fptr = fopen(filename,"r")) == NULL)
	  {
		fprintf(stderr,"error opening %s\n",filename);
		return 1;
	    }
	 
	 print_image(fptr);
	 
	 fclose(fptr);

	printf("Lancement du programme de test XBEE\n");
	printf("Nous allons attendre une trame!\nAllez, c'est parti !\n");
	/*Initialisation UART XBEE */
	
	int xbee1 = serial_init("/dev/ttyUSB0",9600);
	int * xbee1Pointer = &xbee1;



	// Fonction pour creer une trame : computeTrame(uint16_t taille, uint8_t type, uint8_t * trameData)
	// On envoie cette trame pour le test : 7E 00 04 08 01 4D 59 50
	//TODO : calculer la taille de la chaine envoyee
//	struct TrameXbee * trameTest = computeTrame(0x0004, "\x08\x01\x4D\x59");
	//on va envoyer la trame créée avec sendTrame(int xbeeToUse, struct TrameXbee * trameToSend){
	//sendTrame(xbee1Pointer, trameTest);


	// ON VEUT RECUPERER LA TRAME RETOUR
	struct TrameXbee * trameRetour = getTrame(xbee1Pointer);

	// j'essaie d'afficher la trame trouvee
	//afficherTrame(trameRetour);



	// FIN DU PROGRAMME
	close(xbee1);

}


void print_image(FILE *fptr)
{
    	char read_string[MAX_LEN];
    	while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}


static int serial_init(const char *devname, speed_t baudrate)
{
	int fd;
	struct termios newattr;
 	//| O_NOCTTY
	if((fd = open(devname, O_RDWR)) < 0) {
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


