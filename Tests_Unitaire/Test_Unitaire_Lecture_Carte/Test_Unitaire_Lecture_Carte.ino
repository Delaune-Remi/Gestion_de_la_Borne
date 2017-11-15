#include <Wire.h>
#include "I2C.h"

void setup() {
    initI2C(120);       
    Serial.begin(9600);
}

void loop() {
  int val,valCode;
  
  Wire.beginTransmission(0x21);
  Wire.requestFrom(0x21,2); // 0x21 adresse de la carte a puce
  val=Wire.read();
  val&=0x01; 
  Serial.print("Carte Detecter :");
  Serial.println(val);
  if (val == 0){
      val&=0x02;
      val=Wire.read();
      Serial.print("Signaux distribue a la carte a puce :");
      Serial.println(val);
  }
 Serial.end();
 Wire.endTransmission();
}

/*
 *        Valeurs donnees :
 * 1 = pas de carte a puce detecter
 * 0 = carte a puce detecter
 */
