#include <Wire.h>
#include "I2C.h"

void setup() {
    initI2C(255);       
    Serial.begin(9600);
}

void loop() {
  int val;
  byte* valCode(NULL);
  char* code(NULL);
  code= new char [4];
  valCode = new byte [5];
  
  Wire.beginTransmission(0x21);
  Wire.requestFrom(0x21,2); // 0x21 adresse de la carte a puce
  val=Wire.read();
  val&=0x01;
  Serial.print("Carte Detecter :");
  Serial.println(val);
  
  if (val == 0){
      Wire.write(0x02);
      Wire.endTransmission();
      Wire.beginTransmission(0x50);
      Wire.requestFrom(0x50,5,true); // 0x50 adresse de l'EPROM I2C de la carte a puce
      *valCode=Wire.read();
      *(valCode+1)=Wire.read();
      *(valCode+2)=Wire.read();
      *(valCode+3)=Wire.read();
      *(valCode+4)=Wire.read();
      Wire.endTransmission();
      Wire.beginTransmission(0x21);
      Wire.requestFrom(0x21,2); // 0x21 adresse de la carte a puce
      Wire.write(0x01);
      for (int i = 0;i<5;i++){
        *(code+i)=static_cast<char>(*(valCode+1+i));
      }
      Serial.print("Code de la carte a puce :");
      Serial.print(*code);
      Serial.print(*(code+1));
      Serial.print(*(code+2));
      Serial.println(*(code+3));
      
  }
  delete [] valCode;
  delete [] code;
  Serial.end();
 Wire.endTransmission();
}

/*
 *        Valeurs donnees :
 * 1 = pas de carte a puce detecter
 * 0 = carte a puce detecter
 */
