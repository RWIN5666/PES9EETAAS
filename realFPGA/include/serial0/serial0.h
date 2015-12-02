#ifndef SERIAL0_H
#define SERIAL0_H


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 

struct termios oldattr;

int serial_init(const char *devname, speed_t baudrate);


#endif
	