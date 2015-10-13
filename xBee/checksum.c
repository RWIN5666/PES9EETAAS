
#include <stdio.h>


int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        //printf("result %d\n", result );
        return result;
}


/*int twoCharHex(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}*/


int subHextoInt(unsigned char * chaine, int start, int longueur, int octet)
{
    int resultat = 0;
    int temp = 0;
    int mult =1;
    int j = 0;
   int i =0;

    for(j;j<= (longueur/octet -1);j++){
        
                i = start+ (octet-1) + (j)*octet;
                temp = 0; 
                mult =1;
                for(i;i>=start + j*octet; i--){
                    
                        temp += (hex_to_int(chaine[i]) * mult); 
                        //printf("chaine[%d] = %c\n", i, chaine[i]);
                        mult = mult <<4  ;
                        
                }
                //printf("temp = %x\n", temp);
                resultat += temp;
    }
    
    
    return resultat;
    
}







int checksum (unsigned char *chaine, unsigned char *chaineFinale) {
    
      
    
    unsigned int bitDeStart  = subHextoInt(chaine,0,2,2);
    //printf("bitDeStart  -> %X\n",bitDeStart);
    unsigned int dataLenght  = subHextoInt(chaine,2,4,4);
    //printf("dataLenght  -> %X\n",dataLenght);
    unsigned int aT  = subHextoInt(chaine,6,2,2);
    //printf("aT  -> %X\n",aT);
    unsigned int requestCode  = subHextoInt(chaine,8,2,2);
    //printf("requestCode  -> %X\n",requestCode);
    unsigned int data  = subHextoInt(chaine,10,dataLenght,2);
    //printf("data  -> %d\n",data);
    unsigned int check = aT + requestCode +data;
    
    
    check = check <<( sizeof(unsigned int)*8 - 8) >> ( sizeof(unsigned int)*8 - 8)  ; // on garde les 8 derniers bits
                
    check = 255- check;//on soustrait 0xFF
    //printf("checksum  -> %X\n", check);
 
    //printf(" lenght %d\n", hex_to_ascii(chaine[2],chaine[3])* 255 +  hex_to_ascii(chaine[4],chaine[5]) );
    //printf( "hexToInt %d\n" , hexToInt(chaine,2));
    
    unsigned char hex[3];
    sprintf(hex, "%x", check);
    
    int i =0;
    
    while(chaine[i] != '\0'){
        
        chaineFinale[i] = chaine[i];
        i++;
        
    }
    

    chaineFinale[i] = hex[0];
    chaineFinale[i+1] = hex[1];
    chaineFinale[i+2] = '\0';

    return check;
      
}




int main(int argc, char* argv[])
{
    
    unsigned char* chaine = (unsigned char*) argv[1];
    int i = 0;
    
    while(chaine[i] != '\0'){
        
        i++;
        
        
        
    }
    
    unsigned char test[i+2+1]; 
    
    
    int  check = checksum(chaine,test);
     
     
     
    printf ("checksum : %x\n", check );
    printf ("chaine : %s\n", test );
    return 0;
    
    
}



    

