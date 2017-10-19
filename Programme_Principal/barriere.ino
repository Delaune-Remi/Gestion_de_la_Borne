#include "barriere.h"

void ouvertureBarriereEntrer (int& nbVehicule){
  int tempo=0,boucleAmont,boucleAval;
  ouvrirBarriere();
  lireBoucleAval(boucleAval);
  lireBoucleAmont(boucleAmont);
    while( boucleAmont == 0 && tempo <= 120){
      delay(250);
      tempo++;
      Serial.print("Pass tempo");
    }
    lireBoucleAval(boucleAval);
    lireBoucleAmont(boucleAmont);
    if (boucleAmont == 0 && boucleAval == 64){
      lireBoucleAval(boucleAval);
      lireBoucleAmont(boucleAmont);
      Serial.print("Pass Boucle Amont1");
      if (boucleAmont == 0 || boucleAval == 0){
        Serial.print("Pass boucle Aval ou Boucle Amont1");
        while ( boucleAmont == 0 || boucleAval == 0){
          lireBoucleAval(boucleAval);
          lireBoucleAmont(boucleAmont);
          Serial.print("Pass boucle Aval ou Boucle Amont2");
        }
        nbVehicule++;
        Serial.print("Nb Voiture: ");
        Serial.println(nbVehicule);
      } 
      fermer();
    } 
}

void fermer (void){
  Wire.beginTransmission ( 0x20); // Initialisation de la transmission du bus I2C pour la barriere qui est a l'adresse 0x21
  Wire.write (0xFE);  // Ferme la barriere
  Wire.endTransmission();
}

void ouvrirBarriere(void){
  Wire.beginTransmission(0x20);
  Wire.write(0xFD);
  Wire.endTransmission();
}

void lireBoucleAval (int& boucle){
    Wire.requestFrom (0x20,1);
    boucle =Wire.read();
    boucle &= 0x40;
}

void lireBoucleAmont (int& boucle){
    Wire.requestFrom (0x20,1);
    boucle =Wire.read();
    boucle &= 0x20;
}

