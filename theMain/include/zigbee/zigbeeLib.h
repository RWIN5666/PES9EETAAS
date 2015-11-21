#ifndef ZIGBEELIB_H
#define ZIGBEELIB_H


#include "types.h"




void afficherTrame(struct TrameXbee * trameToPrint);
struct TrameXbee * computeTrame(uint16_t taille,uint8_t idFrame, uint8_t * trameData);
struct TrameXbee * computeATTrame(uint16_t taille, uint8_t * dest, uint8_t * data);
int sendTrame(int * xbeeToUse, struct TrameXbee * trameToSend);
void afficherTrame(struct TrameXbee * trameToPrint);
struct TrameXbee * getTrame(int * usedXbee);
int checkFPGAState(uint8_t * dest, int * xbeeCNEPointer);


int sendCaptorInfoRequestFrame(int * xbeeCNEPointer, uint8_t requestCode, uint8_t * dest);
int traiterTrameRetour(requestStruct requestTester, int * xbeePointer, struct TrameXbee * trameRetour, fpgaList * listeFPGA);

#endif
