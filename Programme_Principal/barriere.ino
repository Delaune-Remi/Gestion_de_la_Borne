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
  if (boucleAmont == 0 && boucleAval == 0){
      lireBoucleAval(boucleAval);
      lireBoucleAmont(boucleAmont);
      Serial.print("Pass Boucle Amont1");
      if (boucleAmont == 0 || boucleAval == 0){
        Serial.print("Pass boucle Aval ou Boucle Amont1");
        lireBoucleAval(boucleAval);
        lireBoucleAmont(boucleAmont);
        while ( boucleAmont == 0 || boucleAval == 0){
          lireBoucleAval(boucleAval);
          lireBoucleAmont(boucleAmont);
          Serial.print("Pass boucle Aval ou Boucle Amont2");
        }
        nbVehicule++;
        Serial.print("Nb Voiture: ");
        Serial.println(nbVehicule);
      }  
  }  
  fermer();
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

void sortieVehicule (int& nbVoiture,int& boucleAmont,int& boucleAval){
    Serial.println("Boucle Aval");
    ouvrirBarriere();
    Wire.beginTransmission(0x20);// initialisation de la transmission du bus I2C pour le capteur des boucles qui est a l'adresse 0x20
    do{
      lireBoucleAval(boucleAval);
      lireBoucleAmont(boucleAmont);
     }while ( boucleAval == 0 && boucleAmont == 32);// tant qu'il y a un vehicule sur la boucle Aval et pas sur la boucle amont 
       
     lireBoucleAval(boucleAval);
     lireBoucleAmont(boucleAmont);
          
     if ( boucleAval == 0 || boucleAmont == 0 ){// si il y a un vehicule de detecter sur la boucle aval ou amont
        do{
          lireBoucleAval(boucleAval);
          lireBoucleAmont(boucleAmont);
        }while ( boucleAmont == 0 || boucleAval == 0);  //tant qu'il y a un vehicule sur la boucle amont ou sur la boucle aval on ne fait rien
        nbVoiture--; // decrementation du nombre de voiture
     }
    fermer ();  // Fonction permettant de fermer la barriere
}

void detecterCarte (int& carte){
  Wire.beginTransmission(0x21);   // Initialisation de la transmission du bus I2C pour le capteur de carte a puce qui est a l'adresse 0x21
  Wire.requestFrom (0x21,1);
  carte = Wire.read();
  carte &= 0x01;
}

