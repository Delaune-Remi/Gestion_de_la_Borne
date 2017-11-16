#include <Wire.h>
#include "I2C.h"

void setup() {
   initI2C(120);  
}

void loop() {
  int val;
  int password;
  
  
  Wire.beginTransmission(0x21);
  Wire.requestFrom(0x21,2); // 0x21 adresse de la carte a puce
  val=Wire.read();
  val&=0x01; 
  Serial.begin(9600);
      
  Serial.print("Val: ");
  Serial.println(val);
    if (val == 0){
      Wire.write(0x03);
      Serial.end();
      Serial.begin(9600);
      initI2C(120);  
      Wire.beginTransmission(0x50);
     // Wire.requestFrom(0x50,2);
      password=Wire.read();
      
      Serial.print("PassWord: ");
      Serial.println(password);
      
      Wire.endTransmission();  
      Serial.end();
    }
}

/*
 *        Valeurs donnees :
 * 1 = pas de carte a puce detecter
 * 0 = carte a puce detecter
 */
