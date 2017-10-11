#include "barriere.h"

void ouvrir (void){
  
}

void fermer (void){
  Wire.beginTransmission ( 0x20); // Initialisation de la transmission du bus I2C pour la barriere qui est a l'adresse 0x20
  Wire.write (0xFE);  // Ferme la barriere
}

