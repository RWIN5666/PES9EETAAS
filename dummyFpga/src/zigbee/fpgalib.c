#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdint.h>
#include <poll.h>
#include <netinet/in.h>
#include "zigbee/fpgalib.h"




// POUR INVERSER LES CARACTERES (vu qu'ils arrivent dans le desordre)
void swap(uint8_t* s, int i, int j)
{
    uint8_t temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}
 
void rev(uint8_t* s, uint8_t taille)
{
    int i = 0, j = taille-1;
    for(; i < j; ++i, --j)
        swap(s, i, j);
}

// Pour transformer les bouts de trame en vraie valeur a afficher 
// fonction a affiner en fonction des formats et tout... etc...
int computeData(uint8_t* s, uint8_t taille){
	uint32_t result = 0;
	for(int i = 0; i < taille ; i++){
		printf("Resultat %d = %d\n", i, result);
		result += s[i] << (i*8);

	}
	return result;
}


struct donneeCaptor * computeCaptor(uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max){

struct donneeCaptor * captor = malloc(sizeof(struct donneeCaptor) + sizeof(uint8_t *) + sizeof(uint8_t *) + sizeof(struct donneeCaptor *));
    captor->idCaptor = id;
    captor->dataSize = size;
    captor->unitData = unit;
    uint8_t minCopy[size];
    uint8_t maxCopy[size];
    for(int i = 0; i < size ; i++){
        minCopy[i] = min[i];
        maxCopy[i] = max[i];
    }


    // rev(minCopy,size);
    // rev(maxCopy,size);

    captor->minData = malloc(sizeof(uint8_t) * (int)size);
    captor->maxData = malloc(sizeof(uint8_t) * (int)size);

    for(int j = 0; j < size ; j++){
        captor->minData[j] = minCopy[j];
        captor->maxData[j] = maxCopy[j];
    }


    return captor;
}


captorsList * initCaptorsList(){

    captorsList *liste = malloc(sizeof(*liste));
    struct donneeCaptor *captor = malloc(sizeof(*captor));
    if (liste == NULL || captor == NULL)
    {
        exit(EXIT_FAILURE);
    }
    captor->suivant = NULL;
    liste->premier = captor;
    return liste;

}


void addCaptor(captorsList *liste, uint8_t id, uint8_t size, uint8_t unit, uint8_t* min, uint8_t* max)
{
    /* Création du nouvel élément */
    struct donneeCaptor* nouveau = computeCaptor( id, size,  unit, min,  max);
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;

}

void deleteCaptor(captorsList *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL)
    {
        struct donneeCaptor *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}




struct moduleFPGA * computeModule(uint8_t * my, uint8_t * dest){

	struct moduleFPGA * fpga = malloc(sizeof(struct moduleFPGA));
	for(int i = 0; i<2 ; i++){
		fpga->myFPGA[i] = my[i];
	}
	for(int j = 0; j<8 ; j++){
		fpga->destFPGA[j] = dest[j];
	}
	return fpga;

}


fpgaList * initFpgaList(){

    fpgaList *liste = malloc(sizeof(*liste));
    struct moduleFPGA *fpga = malloc(sizeof(*fpga));
    if (liste == NULL || fpga == NULL)
    {
        exit(EXIT_FAILURE);
    }
    fpga->suivant = NULL;
    liste->premier = fpga;
    return liste;

}


void addFpga(fpgaList *liste, struct moduleFPGA * fpga)
{
    /* Création du nouvel élément */
    if (liste == NULL || fpga == NULL)
    {
        exit(EXIT_FAILURE);
    }
    /* Insertion de l'élément au début de la liste */
    fpga->suivant = liste->premier;
    liste->premier = fpga;

}


void deleteFpga(fpgaList *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL)
    {
        struct moduleFPGA *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}


void addCaptorsListToFpga(struct moduleFPGA * fpga, int number, captorsList * listeCapteurs)
{
    fpga->numberCaptors = number;
    fpga->listeCapteurs = listeCapteurs;
}

void copyMyandDest(uint8_t * myFPGA, uint8_t * destFPGA, struct TrameXbee * trame)
{
	for(int i = 0; i < 8 ; i++){
    		destFPGA[i] = trame->trameData[i];
    }

	for(int j = 0; j < 2  ; j++){
    		myFPGA[j] = trame->trameData[8+j];
    }

}


void getDest(uint8_t * destCopy, struct TrameXbee * trameOrigine)
{
    for(int i = 0; i < 8 ; i++){
            destCopy[i] = trameOrigine->trameData[i];
    }

}

uint8_t compareDest(uint8_t * destCopy, uint8_t * destFPGA)
{
    int i = 0;
    int enCommun = 0;
    while(i<8){
        if(destCopy[i] == destFPGA[i]) enCommun++;
        i++;
    }
    if(enCommun == 8){
        printf("Les deux dest sont identiques !\n");
        return 0x01;
    }
    else{
        printf("Les deux dest ne sont pas identiques !\n");
        return 0x00;
    }
}


void getUnitAndSize(uint8_t * dest, uint8_t typeCapteur, fpgaList * fpgaListe, uint8_t * unitRetour, uint8_t * sizeRetour)
{
   
     if (fpgaListe == NULL)
    {
        printf("Il n'y a pas de liste !\n");

    }
    struct moduleFPGA *actuel = fpgaListe->premier;
    while (actuel != NULL)
    {
        if (compareDest(dest,actuel->destFPGA))
        {
            struct donneeCaptor * actualCaptor = actuel->listeCapteurs->premier;
            while (actualCaptor != NULL)
            {
            if (typeCapteur == actualCaptor->unitData)
            {
               *unitRetour = actualCaptor->unitData;
               *sizeRetour = actualCaptor->dataSize; 
            }
            else actualCaptor = actualCaptor->suivant;
            }
        }
        else actuel = actuel->suivant;
    }
    if(unitRetour == 0x00){
        printf("Impossible de trouver l'unité pour ce capteur");
    }
}

void getResult(uint8_t * result, int size, struct TrameXbee * trameResult)
{
     if (trameResult == NULL)
    {
        printf("Il n'y a pas de trame donc pas de resultat a recuperer\n");
    }
    int taille = (int)size;
    for(int i = 0;i<taille;i++){
        result[i] = trameResult->trameData[i+15];
    }
}

