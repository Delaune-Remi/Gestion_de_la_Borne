#include "I2C.h"
#include <Wire.h>
#include <Keypad.h> // Librairie pour lire le clavier matricielle

void setup() {
    initI2C(120);
    Serial.begin(9600);
    Wire.beginTransmission(0x22);
}

void loop() {
  int val;
  Wire.requestFrom(0x22,2);
  val=Wire.read();
  Serial.print("La Valeur du clavier est: ");
  Serial.println(val,BIN);
  
}
