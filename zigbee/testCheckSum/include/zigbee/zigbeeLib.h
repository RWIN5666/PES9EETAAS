#ifndef ZIGBEELIB_H
#define ZIGBEELIB_H

struct __attribute__((packed)) HeaderXbee
{
	uint8_t firstByte;
	uint16_t taille;
	uint8_t frameID;
};

struct __attribute__((packed)) TrameXbee
{
	struct HeaderXbee header;
	uint8_t trameData[];
};



struct __attribute__((packed)) moduleFPGA 
{
	uint8_t myFPGA[2];
	uint8_t destFPGA[8];
	uint8_t numberCaptors;
	struct donneeCaptor* listeCapteur; 
};


struct __attribute__((packed)) donneeCaptor 
{
	uint8_t idCaptor;
	uint8_t dataSize;
	uint8_t unitData;
	uint8_t* minData;
	uint8_t* maxData;
};

void afficherTrame(struct TrameXbee * trameToPrint);
struct TrameXbee * computeTrame(uint16_t taille, char * trameData);
int sendTrame(int * xbeeToUse, struct TrameXbee * trameToSend);
void afficherTrame(struct TrameXbee * trameToPrint);
struct TrameXbee * getTrame(int * usedXbee);







#endif
