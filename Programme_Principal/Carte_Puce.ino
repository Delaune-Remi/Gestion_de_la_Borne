#include "Carte_Puce.h"

void detecterCarte (int& carte){
  Wire.beginTransmission(0x21);   // Initialisation de la transmission du bus I2C pour le capteur de carte a puce qui est a l'adresse 0x21
  Wire.requestFrom (0x21,2);
  carte=Wire.read();
}

void lectureCodeCarte(char* code){
  byte* valCode(NULL);
  valCode = new byte [5];
  
  Wire.beginTransmission(0x21);
  Wire.requestFrom(0x21,2); // 0x21 adresse de la carte a puce
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.beginTransmission(0x50);
  Wire.requestFrom(0x50,5,true); // 0x50 adresse de l'EPROM I2C de la carte a puce
  setEclairage(0x21,HIGH);
  *valCode=Wire.read();
  *(valCode+1)=Wire.read();
  envoyerMessage(0x3B,"       *",LIGNE2);
  *(valCode+2)=Wire.read();
  envoyerMessage(0x3B,"      **",LIGNE2);
  *(valCode+3)=Wire.read();
  envoyerMessage(0x3B,"      ***",LIGNE2);
  *(valCode+4)=Wire.read();
  envoyerMessage(0x3B,"     ****",LIGNE2);
  effacerAfficheur(0x3B);
  Wire.endTransmission();
  Wire.beginTransmission(0x21);
  Wire.write(0x01);
  for (int i = 0;i<5;i++){
     *(code+i)=static_cast<char>(*(valCode+1+i));
   }
  
  delete [] valCode;
}
