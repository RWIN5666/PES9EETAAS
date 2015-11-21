#ifndef TYPES_H
#define TYPES_H



#include <pthread.h>


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

typedef struct
{
   int requestFromServer;
   uint8_t requestCode;
   uint8_t destRequest[8];
   pthread_mutex_t mutex_server;
}
requestStruct;



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
	uint8_t fpgaName[2];
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

// POUR LE CALCUL DES NOMBRES EN NORME IEE754
typedef union {
  float f;
  struct {
    unsigned int mantisa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
  } parts;
} double_cast;


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



// TYPES DE TRAMES NECESSAIRES
#define ID_AT (0x08)
#define ID_TX (0x10)
#define ID_TX_STATUS (0x8B)
#define ID_RX (0x90)
#define ID_NI (0x95)
#define ID_AT_REMOTE (0x17)


// COMMANDE UTILES POUR AT_COMMAND
#define AT_DH (0x4448)
#define AT_DL (0x444C)
#define AT_MY (0x4D59)
#define AT_SH (0x4D59)
#define AT_SL (0x5348)
#define AT_NI (0x4E49)
#define AT_ID (0x4944)
#define AT_ND (0x4E44)




// CODE TRAME INFOS
#define INFO_FPGA_REQUEST (0x3F)
#define INFO_CAPTOR_REQUEST (0x2A)
#define DIAG_CODE (0x21)



#endif
