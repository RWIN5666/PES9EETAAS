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
int sendInfoCaptorValueFrameTest(int * xbeeCNEPointer,uint8_t * minTemp, uint8_t * maxTemp, uint8_t * fpgaName, uint8_t numberCaptors, uint8_t id, uint8_t tailleData,uint8_t unitData);
int traiterTrameRetour(requestStruct requestTester, int * xbeePointer, struct TrameXbee * trameRetour, fpgaList * listeFPGA);
int sendInfoCaptorValueFrameWithList(int * xbeeRNEPointer, uint8_t * name, captorsList * liste);
int computeCaptorsListWithReceivedInfoFrame(struct moduleFPGA * nouveau, struct TrameXbee * trameRetour);



#endif
