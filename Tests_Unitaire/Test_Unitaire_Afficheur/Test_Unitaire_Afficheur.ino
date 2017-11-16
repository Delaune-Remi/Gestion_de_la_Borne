#include "affiche.h"
#include "I2C.h" //Librairie pour I2C

void setup() {
  initI2C(250); // Initialisation de la vitesse de transmission du bus I2C
  initAfficheur(0x3B); // Initialisation de l'afficheur a l'adresse '0x3B'
  effacerAfficheur(0x3B);
  setEclairage(0x21,LOW);
  setEclairage(0x21,HIGH);
  envoyerMessage(0x3B,MESSAGE1,LIGNE1);
}

void loop(){ 

}

