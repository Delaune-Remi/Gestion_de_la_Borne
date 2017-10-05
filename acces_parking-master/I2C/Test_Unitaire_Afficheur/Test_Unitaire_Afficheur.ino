#include <affiche.h>
#include "I2C.h" //Librairie pour I2C


void setup() {
  initI2C(120); // Initialisation de la vitesse de transmission du bus I2C
  initAfficheur(0x3B); // Initialisation de l'afficheur a l'adresse '0x3B'
  activerAfficheur (0x3B); // Activation de l'afficheur pour afficher les message 
  blinkAfficheur(0x3B,6,60); // Fait clignoter l'afficheur
  desactiverAfficheur(0x3B);
}

void loop(){

}

