#include <Wire.h>
#include "I2C.h"

void setup() {
    initI2C(255);       
    Serial.begin(9600);
}

void loop() {
  int val,valCode;
  
  Wire.beginTransmission(0x21);
  Wire.requestFrom(0x21,1); // 0x21 adresse de la carte a puce
  while(Wire.available()){
     val=Wire.read();
  }
  Serial.print("Carte Detecter :");
  Serial.println(val,BIN);
  if (val == 0){
      Wire.write(0x02);
      Wire.beginTransmission(0x50);
      Wire.requestFrom(0x50,2); // 0x50 adresse de la carte a puce
      valCode=Wire.read();
      Wire.beginTransmission(0x21);
      Wire.requestFrom(0x21,2); // 0x21 adresse de la carte a puce
      Wire.write(0x00);
      Serial.print("Signaux de la carte a puce :");
      Serial.println(valCode);
  }
 Serial.end();
 Wire.endTransmission();
}

/*
 *        Valeurs donnees :
 * 1 = pas de carte a puce detecter
 * 0 = carte a puce detecter
 */
