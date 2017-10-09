#include <Wire.h> // Inclusion de la bibliotheque Wire.h
#include "I2C.h"  // Inclusion de la bibliotheque I2C.h qui permet d'initialise la vitesse du bus I2C

void setup() {
  initI2C(120); // initialisation de la vitesse du bus I2C
  Serial.begin(9600); // Initialisation de la vitesse du moniteur serie
}

void loop() {
  int val;
  Wire.beginTransmission(0x20); // Permet l'initialisation de la communication avec l'adresse de la barriere 
  Wire.requestFrom(0x20,1); // Permet de faire une requete pour lire les 1 premier octet a l'adresse 0x20 
  val=Wire.read();
  val&= 0x60;
  Serial.print(val);  // Permet d'afficher sur le moniteur serie
  Serial.end();  // Fin de la communication avec le moniteur serie
  Wire.endTransmission(); // Permet de mettre fin a la communication
}

/*
 *          Valeur Donnee :
 * 96 : Aucune Voiture detecter
 * 32 : Voiture detecter sur Aval
 * 64 : Voiture detecter sur Amont
 */
