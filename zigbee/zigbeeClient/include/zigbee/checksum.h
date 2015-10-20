#ifndef CHECKSUM_H
#define CHECKSUM_H


int hex_to_int(char c);
int subHextoInt(unsigned char * chaine, int start, int longueur, int octet);
int checksum (unsigned char *chaine, unsigned char *chaineFinale);


#endif
