#include "barriere.h"

void ouvrir (int& nbVehicule){
  int tempo=0;
  ouvertureBarriere();
    while(((Wire.read() & 0x60) == 64)&& tempo <= 120){
      delay(250);
      tempo++;
    }
    if ((Wire.read() & 0x60) != 64){
      if ((Wire.read() & 0x60) != 96){
        while (((Wire.read() & 0x20)==0) || ((Wire.read() & 0x40) == 0));
        nbVehicule++;
      }
      fermer();
    }
}

void fermer (){
  Wire.beginTransmission ( 0x20); // Initialisation de la transmission du bus I2C pour la barriere qui est a l'adresse 0x21
  Wire.write (0xFE);  // Ferme la barriere
  Wire.endTransmission();
}

void ouvertureBarriere(){
  Wire.beginTransmission(0x20);
  Wire.write(0xFD);
  Wire.endTransmission();
}

