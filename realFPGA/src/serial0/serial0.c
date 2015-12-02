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
	} 

	cfsetispeed(&newattr, baudrate);
	cfsetospeed(&newattr, baudrate);

	/*else if(tcgetattr(fd, &oldattr) != 0) {
		perror("Failed to get configuration");
		exit(EXIT_FAILURE);
	}
	newattr = oldattr;

	
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

	tcflush(fd,TCIOFLUSH);*/

	return fd;
}

