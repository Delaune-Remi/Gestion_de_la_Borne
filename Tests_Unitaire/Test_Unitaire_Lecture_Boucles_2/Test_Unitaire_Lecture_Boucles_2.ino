#include <Wire.h> // Inclusion de la bibliotheque Wire.h
#include "I2C.h"  // Inclusion de la bibliotheque I2C.h qui permet d'initialise la vitesse du bus I2C

void setup() {
  initI2C(120); // initialisation de la vitesse du bus I2C
  Serial.begin(9600); // Initialisation de la vitesse du moniteur serie
}

void loop() {
  int boucleAmont,boucleAval;
  Serial.begin(9600); // Initialisation de la vitesse du moniteur serie
  Wire.beginTransmission(0x20); // Permet l'initialisation de la communication avec l'adresse de la barriere 
  Wire.requestFrom(0x20,1); // Permet de faire une requete pour lire les 1 premier octet a l'adresse 0x20 
  boucleAmont=Wire.read();
  boucleAval=boucleAmont;
  boucleAval&=0x40;
  boucleAmont&= 0x20;
  Serial.print("Boucle Amont: ");  // Permet d'afficher sur le moniteur serie
  Serial.println(boucleAmont);
  Serial.print("Boucle Aval: ");
  Serial.println(boucleAval);
  
  while ( boucleAmont == 0 || boucleAval == 0 ){
    
      Wire.beginTransmission(0x20); // Permet l'initialisation de la communication avec l'adresse de la barriere 
      Wire.write(0xFD); // Permet d'ouvrir la barriere
      /* 
       *  0xFD: Ouvrir barriere
       *  0xFE: Fermer barriere
       */
       Wire.endTransmission();
       Wire.beginTransmission(0x20); // Permet l'initialisation de la communication avec l'adresse de la barriere 
       Wire.requestFrom(0x20,1); // Permet de faire une requete pour lire les 1 premier octet a l'adresse 0x20 
       boucleAmont=Wire.read();
       boucleAval=boucleAmont;
       boucleAval&= 0x40;
       boucleAmont&= 0x20;
  }
  Wire.beginTransmission(0x20); // Permet l'initialisation de la communication avec l'adresse de la barriere 
  Wire.write(0xFE); // Permet d'ouvrir la barriere
      /* 
       *  0xFD: Ouvrir barriere
       *  0xFE: Fermer barriere
       */
  Wire.endTransmission();
  Serial.end();  // Fin de la communication avec le moniteur serie
  Wire.endTransmission(); // Permet de mettre fin a la communication
}

/*
 *          Valeur Donnee :
 * 96 : Aucune Voiture detecter
 * 32 : Voiture detecter sur Aval et pas sur Amont
 * 64 : Voiture detecter sur Amont et pas sur Aval
 * 00 : Voiture detecter sur Aval et Amont
 */ 
