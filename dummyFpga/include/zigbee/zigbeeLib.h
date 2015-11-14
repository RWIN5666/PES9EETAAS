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
#define INFO_CAPTOR_REQUEST (0x3F)
#define DIAG_CODE (0x21)



void afficherTrame(struct TrameXbee * trameToPrint);
struct TrameXbee * computeTrame(uint16_t taille,uint8_t idFrame, uint8_t * trameData);
struct TrameXbee * computeATTrame(uint16_t taille, uint8_t * dest, uint8_t * data);
int sendTrame(int * xbeeToUse, struct TrameXbee * trameToSend);
void afficherTrame(struct TrameXbee * trameToPrint);
struct TrameXbee * getTrame(int * usedXbee);
int checkFPGAState(uint8_t * dest, int * xbeeCNEPointer);

#endif
