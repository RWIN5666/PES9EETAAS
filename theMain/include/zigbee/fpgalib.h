#ifndef FPGALIB_H
#define FPGALIB_H

#include "zigbee/zigbeeLib.h"

struct __attribute__((packed)) donneeCaptor 
{
	uint8_t idCaptor;
	uint8_t dataSize;
	uint8_t unitData;
	uint8_t * minData;
	uint8_t * maxData;
	struct donneeCaptor * suivant;
};

typedef struct captorsList captorsList;
struct __attribute__((packed)) captorsList 
{	
	struct donneeCaptor * premier;
};


struct __attribute__((packed)) moduleFPGA 
{
	uint8_t myFPGA[2];
	uint8_t destFPGA[8];
	uint8_t numberCaptors;
	captorsList * listeCapteurs; 
	struct moduleFPGA * suivant;
};


typedef struct fpgaList fpgaList;
struct __attribute__((packed)) fpgaList 
{	
	struct moduleFPGA * premier;
};


// TYPE DE CAPTEUR
#define ID_TEMPERATURE (0xCC)
#define ID_LIGHT (0xDD)
#define ID_GYRO (0xEE)
#define ID_ANALOG (0xBB)

// UNITE CAPTEURS
#define LUM_LUMEN (0x0A)
#define LUM_CANDELA (0x0B)
#define TEMP_KELVIN (0x0E)
#define TEMP_CELSIUS (0x0C)
#define TEMP_FAHRENHEIT (0x0F)



void swap(uint8_t* s, int i, int j);
void rev(uint8_t* s, uint8_t taille);
struct donneeCaptor * computeCaptor(uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max);
captorsList * initCaptorsList();
void addCaptor(captorsList *liste, uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max);
struct moduleFPGA * computeModule(uint8_t * my, uint8_t * dest);
fpgaList * initFpgaList();
void addFpga(fpgaList *liste, struct moduleFPGA * fpga);
void addCaptorsListToFpga(struct moduleFPGA * fpga, int number, captorsList * listeCapteurs);
int computeData(uint8_t* s, uint8_t taille);
void copyMyandDest(uint8_t * myFPGA, uint8_t * destFPGA, struct TrameXbee * trame);
void getDest(uint8_t * destCopy, struct TrameXbee * trameOrigine);
uint8_t compareDest(uint8_t * destCopy, uint8_t * destFPGA);
void getUnitAndSize(uint8_t * dest, uint8_t typeCapteur, fpgaList * fpgaListe, uint8_t *unitRetour, uint8_t *sizeRetour);
void getResult(uint8_t * result, int size, struct TrameXbee * trameResult);


#endif
