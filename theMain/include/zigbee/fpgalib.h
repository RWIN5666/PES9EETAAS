#ifndef FPGALIB_H
#define FPGALIB_H



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


void swap(uint8_t* s, int i, int j);
void rev(uint8_t* s, uint8_t taille);
struct donneeCaptor * computeCaptor(uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max);
captorsList * initCaptorsList();
void addCaptor(captorsList *liste, uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max);
struct moduleFPGA * computeModule(uint8_t * my, uint8_t * dest, uint8_t number, captorsList * liste);
fpgaList * initFpgaList();
void addFpga(fpgaList *liste, uint8_t * my, uint8_t * dest, uint8_t number, captorsList * listeCapteurs);
int computeData(uint8_t* s, uint8_t taille);




#endif
