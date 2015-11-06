#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include "dessinterminal/drawterminal.h"




void print_image(FILE *fptr)
{
    	char read_string[MAX_LEN];
    	while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}

