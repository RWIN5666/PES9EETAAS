#ifndef FPGALIB_H
#define FPGALIB_H

#include "types.h"




void swap(uint8_t* s, int i, int j);
void rev(uint8_t* s, uint8_t taille);
struct donneeCaptor * computeCaptor(uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max);
captorsList * initCaptorsList();
void addCaptor(captorsList *liste, uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max);
void showCaptor(struct donneeCaptor * captor);
struct moduleFPGA * computeModule(uint8_t * my, uint8_t * dest);
fpgaList * initFpgaList();
void addFpga(fpgaList *liste, struct moduleFPGA * fpga);
void addCaptorsListToFpga(struct moduleFPGA * fpga, int number, captorsList * listeCapteurs);
int computeData(uint8_t* s, uint8_t taille, uint8_t type);
void copyMyandDest(uint8_t * myFPGA, uint8_t * destFPGA, struct TrameXbee * trame);
void getDest(uint8_t * destCopy, struct TrameXbee * trameOrigine);
int compareDest(uint8_t * destCopy, uint8_t * destFPGA);
void getUnitAndSize(uint8_t * dest, uint8_t typeCapteur, fpgaList * fpgaListe, uint8_t *unitRetour, uint8_t *sizeRetour);
void getResult(uint8_t * result, int size, struct TrameXbee * trameResult);


void setFpgaName(struct moduleFPGA * module, uint8_t firstNameByte, uint8_t secondNameByte);
int compareName(uint8_t * nameCopy, uint8_t * nameFPGA);
struct moduleFPGA * getModuleFromName(fpgaList * fpgaListe, uint8_t * name);
int hasCaptor(uint8_t * name, fpgaList * fpgaListe, uint8_t code);


#endif
