#include <Wire.h>
#include "I2C.h"

void setup() {
  initI2C(120);
  Wire.beginTransmission(0x22); //Initialisation et Connection a au capteur (clavier matriciel) relier au Bus I2C qui a l'adresse 0x22
  Serial.begin(9600);
}

void loop() {
  char c = Wire.read();
  Serial.write(c);
  Serial.end();
  Wire.endTransmission(); // Arret la transmission entre l'arduino et l'I2C
}
