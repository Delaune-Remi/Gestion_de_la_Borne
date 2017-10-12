#include <Wire.h>
#include "I2C.h"

int boucle;
int boucleAmont;
int boucleAval;
int nbVoiture=0;

void setup() {
  initI2C(120);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(0x20);
  Wire.requestFrom(0x20,2);
  boucle=Wire.read();
  boucle&=0x60;
  boucleAmont=Wire.read();
  boucleAmont&=0x20;
  boucleAval=Wire.read();
  boucleAval&=0x40;
  
  Serial.print("Nb Voiture: ");
  Serial.println(nbVoiture);
  
 if ( boucle == 32){ // Si il y a une Voiture sur la boucle Aval et pas sur la boucle amont
          Serial.println("Boucle Aval");
          ouvertureBarriere();
          Wire.beginTransmission(0x20);// Permet l'initialisation de la communication avec l'adresse de la barriere 
          Wire.requestFrom(0x20,2);
          boucle=Wire.read();
          boucle&=0x60;
          while ( boucle == 32){ // tant qu'il y a un vehicule sur la boucle Aval et pas sur la boucle amont
            Wire.requestFrom(0x20,2);
            boucle=Wire.read();
            boucle&=0x60;
          }
          Wire.requestFrom(0x20,2);
          boucle=Wire.read();
          boucle&=0x60;
          
          if ( boucle != 96){ // si il y a un vehicule de detecter sur la boucle aval ou amont
            do{
                boucleAmont=Wire.read();
                boucleAmont&=0x20;
                boucleAval=Wire.read();
                boucleAval&=0x40; 
            }while ( boucleAmont == 0 || boucleAval == 0);//tant qu'il y a un vehicule sur la boucle amont ou sur la boucle aval on ne fait rien
            nbVoiture--; // decrementation du nombre de voiture
          }
         fermer();
      }
}

void ouvertureBarriere(){
  Wire.beginTransmission(0x20);
  Wire.write(0xFD);
  Wire.endTransmission();
}

void fermer (){
   Wire.beginTransmission(0x20);
   Wire.write(0xFE);
   Wire.endTransmission();
}

