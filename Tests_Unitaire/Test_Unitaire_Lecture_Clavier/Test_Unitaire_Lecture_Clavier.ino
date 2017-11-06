#include <Wire.h>
#include "I2C.h"



void setup() {
    Wire.begin();
    initI2C(255);
    Serial.begin(9600);
    Serial.println("test du clavier");
}

void loop() {
  int val;
  
  Wire.beginTransmission(0x22);
  Wire.write(0x0F);
  Wire.endTransmission();
  Wire.requestFrom(0x22,1);
  val=Wire.read();
  Serial.print("La Valeur du clavier est: ");
  Serial.println(val,BIN);
  delay(500);
  
}
