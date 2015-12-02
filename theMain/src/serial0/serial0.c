#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include "serial0/serial0.h"
struct termios oldattr;

int serial_init(const char *devname, speed_t baudrate)
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


int serial_init_V2(const char *devname, speed_t baudrate)
{

	/* Open device */
	/*
	* configuration options
	* O_RDWR - we need read and write access
	* O_CTTY - prevent other input (like keyboard) from affecting what we read
	* O_NDELAY - We don't care if the other side is connected (some devices don't explicitly connect)
	*/
	int xbeeCNE;
	if (( xbeeCNE= open(devname, O_RDWR | O_NOCTTY )) < 0) {
	perror("/dev/ttyUSB0");
	exit(1);
	}
	/* Read parameters */
	tcgetattr(xbeeCNE, &oldattr);
	// Change baud rate (output/input) to 9600
	cfsetispeed(&oldattr, baudrate);
	cfsetospeed(&oldattr, baudrate);
	// Set 8-bit mode
	oldattr.c_cflag &= ~CSIZE;
	oldattr.c_cflag |= CS8;
	oldattr.c_cc[VMIN] = 100;
	oldattr.c_cc[VTIME] = 10;
	// Enable the receiver and set local mode...
	//tty.c_cflag |= (CLOCAL | CREAD); | ICANON
	oldattr.c_lflag &= ~(ECHO | ECHONL | IEXTEN);
	/* Apply new configuration*/
	if (tcsetattr(xbeeCNE, TCSANOW, &oldattr) == -1) {
	return -1;
	}
	return xbeeCNE;
}




