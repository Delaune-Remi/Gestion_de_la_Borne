#include <Wire.h> // Inclusion de la bibliotheque Wire.h
#include "I2C.h"  // Inclusion de la bibliotheque I2C.h qui permet d'initialise la vitesse du bus I2C

void setup() {
  initI2C(120); // initialisation de la vitesse du bus I2C (120)
}

void loop() {
  Wire.beginTransmission(0x20); // Permet l'initialisation de la communication avec l'adresse de la barriere 
  Wire.write(0xFD); // Permet d'ouvrir la barriere
  /* 
   *  0xFD: Ouvrir barriere
   *  0xFE: Fermer barriere
   */
  Wire.endTransmission(); // Permet de mettre fin a la communication
}
