#include "ArduinoEEPROM.h"

#define ADRESSEVOITURE 1
#define ADRESSEBASECODES 3


void ecritureVoitureEEPROM(int nbVoiture){
  
   EEPROM.write(ADRESSEVOITURE,nbVoiture);
}

int lectureVoitureEEPROM(void){
  int nombreVoiture;

  nombreVoiture = EEPROM.read(ADRESSEVOITURE);
  
  return nombreVoiture;
}

int lectureCodeMaxEEPROM(void){
  int maxcode;

   maxcode = EEPROM.read(2);
  Serial.println(maxcode);
  return maxcode;
}

void ecritureCodesEEPROM(char caractere,int i){ 
   EEPROM.write((lectureCodeMaxEEPROM()+i),caractere);
}

void lectureCodesEEPROM(char* const codes,int& maxCode){
  for (int i=0;i<(lectureCodeMaxEEPROM()-ADRESSEBASECODES);i++){
    *(codes+i)=(char)EEPROM.read((ADRESSEBASECODES+i));
  }
  maxCode = lectureCodeMaxEEPROM();
}

