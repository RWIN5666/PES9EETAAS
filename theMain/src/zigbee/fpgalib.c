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
#include "hexLib/hexLib.h"
#include "jansson/jansson.h"


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
// TODO : fonction a affiner en fonction des formats et tout... etc...
// TODO : AJOUTER ICI LES INFOS SUR CAPTEURS AU FICHIER JSON
int computeData(uint8_t* s, uint8_t taille, uint8_t type){
	switch(type){
        case 0x00:{
            // CAS PAR DEFAUT (UTILISE POUR LE TEST)
            uint32_t result = 0;
            for(int i = 0; i < taille ; i++){
                printf("Resultat %d = %d\n", i, result);
                result += s[i] << (i*8);
            }
            return 1;
            break;
        }
        case ID_TEMPERATURE:{

            // DANS LE CAS DU LM75 OU LA DONNEE TIENT SUR 2 OCTETS
            uint8_t byte1 = s[0];
            uint8_t byte2 = s[1];
            uint8_t byteSign = (byte1 & 0x80) >> 7;
            byte1 = byte1 & 0x7F;
            uint8_t byteHalf = (byte2 & 0x80) >> 7;
            printf("valeur de byteSign : %02x\n",byteHalf);
            uint8_t testTrame[(2*2)+1];
            int taille = 2;
            sprintf(&testTrame[0],"%02x",byte1);
            sprintf(&testTrame[2],"%02x",byte2);
            printf("test : %s\n", testTrame);
            uint8_t buffer[taille];
            convertZeroPadedHexIntoByte(testTrame,buffer);
            uint32_t test32u = 0x0F001500;
            int test32 = (int) test32u;
            printf("Valeur de test32u en int : %d\n", test32);
            int testByte = (int) buffer[0];
            printf("Valeur de testByte en int : %d\n", testByte);
            float trucFloat = (float) testByte;
            printf("Affichage de trucFloat apres conversion en float %f\n", trucFloat);
            if(byteHalf) trucFloat += 0.5;
            printf("Affichage de trucFloat apres ajout ou non de 0.5 %f\n", trucFloat);
            if(byteSign) trucFloat = -trucFloat;
            printf("Affichage de trucFloat  apres ou non changement de signe %f\n", trucFloat);
            return 1;
            break;
        }
        case ID_LIGHT:{
             return 1;
            break;
        }
        case ID_GYRO:{
            // 3 valeurs, la donnee arrive sous la forme de 6 octets, deux pour chaque axe.
            int x = (((int)s[1]) << 8) | s[0];
            int y = (((int)s[3]) << 8) | s[2];
            int z = (((int)s[5]) << 8) | s[4];
            printf("Voici les valeurs :\nX -> %d\nY -> %d\nZ -> %d", x,y,z);
             return 1;
            break;
        }
        case ID_ANALOG:{
            return 1;
            break;
        }
        default:
            return 0;


    }
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

void showCaptor(struct donneeCaptor * captor){

    fprintf(stderr,"idCaptor : %02x\n",captor->idCaptor);
    fprintf(stderr,"dataSize : %02x\n",captor->dataSize);
    fprintf(stderr,"unitData : %02x\n",captor->unitData);
    for(int i = 0; i < captor->dataSize ; i++){
        fprintf(stderr,"octet n°%d : %02x\n",i,captor->minData[i]);
    }
    
    for(int j = 0; j < captor->dataSize ; j++){
        fprintf(stderr,"octet n°%d : %02x\n",j,captor->maxData[j]);
    }
    fprintf(stderr,"suivant : %p\n",(void *)captor->suivant);


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

int compareDest(uint8_t * destCopy, uint8_t * destFPGA)
{
    int i = 0;
    int enCommun = 0;
    while(i<8){
        if(destCopy[i] == destFPGA[i]) enCommun++;
        i++;
    }
    if(enCommun == 8){
        printf("Les deux dest sont identiques !\n");
        return 1;
    }
    else{
        printf("Les deux dest ne sont pas identiques !\n");
        return 0;
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
            printf("Avant actualCaptor\n");
            struct donneeCaptor * actualCaptor = actuel->listeCapteurs->premier;
            showCaptor(actualCaptor);
            if(actualCaptor == NULL){
                printf("ActualCaptor est NULL\n");
            }
            printf("Après actualCaptor\n");
            while (actualCaptor != NULL)
            {
            printf("apres while actualCaptor\n");
            if (typeCapteur == actualCaptor->idCaptor)
            {
                
                printf("Avant unitRetour\n");
                fprintf(stderr,"actualCaptor->unitData : %02x\n", actualCaptor->unitData);
                fprintf(stderr,"actualCaptor->dataSize : %02x\n", actualCaptor->dataSize);
               *unitRetour= actualCaptor->unitData;
               *sizeRetour= actualCaptor->dataSize;
               printf("Après unitRetour\n"); 
               break;
            }
            else {
                actualCaptor = actualCaptor->suivant;
                
            }
            }
            break;
        }
        else actuel = actuel->suivant;
    }
    if(unitRetour == NULL){
        printf("Impossible de trouver l'unité pour ce capteur\n");
    }
    if(sizeRetour == NULL){
        printf("Impossible de trouver la taille des donnees pour ce capteur\n");
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


void setFpgaName(struct moduleFPGA * module, uint8_t firstNameByte, uint8_t secondNameByte){
            module->fpgaName[0] = firstNameByte;
            module->fpgaName[1] = secondNameByte;
}

int compareName(uint8_t * nameCopy, uint8_t * nameFPGA)
{
    int i = 0;
    int enCommun = 0;
    while(i<2){
        if(nameCopy[i] == nameFPGA[i]) enCommun++;
        i++;
    }
    if(enCommun == 2){
        printf("Les deux dest sont identiques !\n");
        return 1;
    }
    else{
        printf("Les deux dest ne sont pas identiques !\n");
        return 0;
    }
}

struct moduleFPGA * getModuleFromName(fpgaList * fpgaListe, uint8_t * name){

    if(fpgaListe == NULL){
        printf("Ya pas de liste gros !\n");
        return NULL;
    }

    else {
        struct moduleFPGA * actuel = fpgaListe->premier;
        while (actuel != NULL)
        {
            if (compareName(name,actuel->fpgaName))
            {
                printf("On a trouve le module !\n");
                return actuel;
            }
            else actuel = actuel->suivant;
        }
        return NULL;
    }
}

int hasCaptor(uint8_t * name, fpgaList * fpgaListe, uint8_t code){

    if (fpgaListe == NULL)
        {
            printf("Il n'y a pas de liste !\n");
            return 0;
        }

    struct moduleFPGA *actuel = getModuleFromName(fpgaListe, name);
    while (actuel != NULL)
    {
            struct donneeCaptor * actualCaptor = actuel->listeCapteurs->premier;
            showCaptor(actualCaptor);
            if(actualCaptor == NULL){
                printf("ActualCaptor est NULL\n");
                return 0;
            }
            while (actualCaptor != NULL)
            {
            if (code == actualCaptor->idCaptor)
            {             
              return 1;          
            }
            else {
                actualCaptor = actualCaptor->suivant;
            }
            } 
    }
    return 0;
}

uint8_t getCaptorsListSize(captorsList * listeCapteurs){

    int totalSizeInt = 0;
    uint8_t totalSizeHex = 0x00;
    struct donneeCaptor * actualCaptor = listeCapteurs->premier;
    if(actualCaptor == NULL){
                printf("ActualCaptor est NULL\n");
                perror("No Captor");
            }
    while (actualCaptor != NULL)
    {
        totalSizeInt++;
        fprintf(stderr,"TotalSize : %d\n",totalSizeInt);
        actualCaptor = actualCaptor->suivant;     
    }
    totalSizeHex = (uint8_t) totalSizeInt;
    return totalSizeHex;
}


uint8_t getFpgaListSize(fpgaList * listeFpga){

    int totalSizeInt = 0;
    uint8_t totalSizeHex = 0x00;
    struct moduleFPGA * actualFpga = listeFpga->premier;
    if(actualFpga == NULL){
                printf("ActualCaptor est NULL\n");
                perror("no fpga");
            }
    while (actualFpga != NULL)
    {
        totalSizeInt++;
        fprintf(stderr,"TotalSize : %d\n",totalSizeInt);
        actualFpga = actualFpga->suivant;     
    }
    totalSizeHex = (uint8_t) totalSizeInt;
    return totalSizeHex;
}

