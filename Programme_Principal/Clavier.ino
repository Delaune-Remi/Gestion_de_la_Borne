#include "Clavier.h"

#define TAILLECODE 4

int detectionTouche (void){
  int val=0,detect=0;
  
  Wire.beginTransmission(0x22);
  Wire.write(0x0F);
  Wire.endTransmission();
  Wire.requestFrom(0x22,1);
  val=Wire.read();
  if (val!=15){
    detect++;
  }
  return detect;
}

char conversionTouche(void){
  int valColonne=0,valLigne=0;
  char valeur=' ';
  
  while (valeur == ' '){
    Wire.beginTransmission(0x22);
    Wire.write(0x0F);
    Wire.endTransmission();
    Wire.requestFrom(0x22,1);
    valLigne=Wire.read();
    if (valLigne!=15){
      Wire.beginTransmission(0x22);
      Wire.write(0x70);
      Wire.endTransmission();
      Wire.requestFrom(0x22,1);
      valColonne=Wire.read();
    }
    switch (valLigne){
      case 15:
         break;
      case 14:
        switch(valColonne){
          case 96:
            valeur = '1';
            break;
          case 80:
            valeur = '2';
            break;
          case 48:
            valeur = '3';
        }
        break;
      case 13:
        switch(valColonne){
          case 96:
            valeur = '4';
            break;
          case 80:
            valeur = '5';
            break;
          case 48:
            valeur = '6';
        }
        break;
      case 11:
         switch(valColonne){
          case 96:
            valeur = '7';
            break;
          case 80:
            valeur = '8';
            break;
          case 48:
            valeur = '9';
            break;
          default:
            valeur = 'A';
        }
        break;
      case 7:
        switch(valColonne){
          case 96:
            valeur = '*';
            break;
          case 80:
            valeur = '0';
            break;
          case 48:
            valeur = '#';
        }
      }
  }
  return valeur;
}

void lectureClavier(char* code){  
  int touchedetecter=0;
  int i=0;
  while (i<TAILLECODE){
     touchedetecter=detectionTouche();
     if (touchedetecter==1){
      *(code+i)= conversionTouche();
      if (*(code+i) != 'A'){
        i++;
      }else{
        digitalWrite(38,HIGH);
      }
     }
     switch(i){
        case 1:
          envoyerMessage(0x3B,"       *",LIGNE2);
          break;
        case 2:
          envoyerMessage(0x3B,"      **",LIGNE2);
          break;
        case 3:
          envoyerMessage(0x3B,"      ***",LIGNE2);
          break;
        case 4:
          envoyerMessage(0x3B,"     ****",LIGNE2);
     }
     
     delay(200);
  }
}
