#include "clavier.h"

int detectionTouche(void){
 char c; // Declaration d'une variable de type caractere 
c = Wire.read(); // Affectation de la lecture du Bus I2C a la variable c
Serial.print(c); // Ecriture sur le moniteur serie du caractere 
Serial.end(); // Arret de la liaison serie 
Wire.endTransmission(); // Arret la transmission entre l'arduino et l'I2C
}

