/***********  comXbee.c ***********/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>


struct termios oldattr;


struct HeaderXbee
{
	uint8_t firstByte;
	uint16_t taille;
};

struct TrameXbee
{
	struct HeaderXbee header;
	uint8_t * trameQuiSuit;
};



struct TrameXbee * recupTrame(int usedXbee){

	struct TrameXbee *trameRetour = malloc(sizeof(struct TrameXbee));
	
	struct pollfd fds;

	fds.fd = usedXbee;
	fds.events = POLLIN;

	int retourFd = poll(&fds, 1, 500);

	if(retourFd < 0) return -1;

	if(fds.revents & POLLIN){

		// on va recuperer le header 
		uint8_t buffer[4];
		if (read(fds.fd, buffer, 4) < 1) {
			perror("Error getting header");
			return NULL;
		}
		trameRetour->header.firstByte = buffer[0];
		trameRetour->header.taille = ((uint16_t)buffer[1] << 8) | buffer[2];

		trameRetour->trameQuiSuit = malloc((trameRetour->header.taille)*sizeof(uint8_t));


		if (read(fds.fd, trameRetour->trameQuiSuit, trameRetour->header.taille - 1) < 1) {
			perror("error getting remaining frame");
			return NULL;
		}
	}
		return trameRetour;
}


uint8_t getCheckSum(struct TrameXbee trameToCompute){

	return 0;

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



int main(int argc, char * argv[]){

	/*Initialisation UART XBEE */
	int xbee1 = serial_init("/dev/ttyUSB0",9600);
	char chaineTest[] = "\x7E\x00\x04\x08\x01\x4D\x59\x50";

	int tailleTest = strlen(chaineTest);
	int truc = 1;
	printf("%d et taille test : %d\n", truc, tailleTest);
	for(int k = 0; k < tailleTest - 1 ; k++){
		 fprintf(stderr,"%02x ",chaineTest[k]);
		//fprintf(stderr, "%s\n", );
	}



	printf("\n");
	int taille = write(xbee1,chaineTest, tailleTest);
	
	 struct TrameXbee * trameRetour = recupTrame(xbee1);

	 uint8_t trameToPrint[trameRetour->header.taille];

	trameToPrint[0] = trameRetour->header.firstByte;
	trameToPrint[1] = trameRetour->header.taille;

	for(int i = 3 ; i < trameRetour->header.taille -1;i++){


		trameToPrint[i] = trameRetour->trameQuiSuit[i-3];

	}
 

	printf("Trame renvoyee : \n");
	for(int i = 0; i < trameRetour->header.taille -1; i++){

		printf("%x",trameToPrint[i]);


	}
	return 0;

}


