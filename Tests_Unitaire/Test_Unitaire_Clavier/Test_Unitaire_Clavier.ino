#include "clavier.h"

void setup() {
  initI2C(120);
  Wire.begin(0x38); //Initialisation et Connection a au capteur (clavier matriciel) relier au Bus I2C qui a l'adresse 0x22
  Serial.begin(9600); // Initialisation de la liason serie relier au moniteur serie a 9600 bauds
}

void loop() {
  int detection=0;
  
  detection=detectionTouche();
  
  while (detection==1){
    
    detection=detectionTouche();
  }
}

/*
char c; // Declaration d'une variable de type caractere 
c = Wire.read(); // Affectation de la lecture du Bus I2C a la variable c
Serial.print(c); // Ecriture sur le moniteur serie du caractere 
Serial.end(); // Arret de la liaison serie 
Wire.endTransmission(); // Arret la transmission entre l'arduino et l'I2C
*/
