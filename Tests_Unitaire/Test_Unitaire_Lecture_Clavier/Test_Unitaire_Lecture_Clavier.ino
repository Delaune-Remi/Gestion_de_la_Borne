#include "Clavier.h"

#define TAILLECODE 4

void setup() {
    Wire.begin();
    initI2C(255);
    Serial.begin(9600);
    Serial.println("test du clavier");
}

void loop() {
  int touchedetecter=0;
  int i=0;
  char* code(NULL);
  
  code = new char [TAILLECODE];
  while (i<TAILLECODE){
     touchedetecter=detectionTouche();
     if (touchedetecter==1){
       *(code+i)=conversionTouche();
       i++;
     }
     delay(200);
  }
    
  if (i==TAILLECODE){
    affichageCode(code,i);
  }  
  delete code;
}
