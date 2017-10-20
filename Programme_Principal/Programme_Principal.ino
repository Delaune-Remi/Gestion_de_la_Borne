#include "barriere.h" // Inclussion de la bibliotheque barriere.h permettant de gerer la barriere

int boucleAmont;  // Declaration d'une variable pour la boucle Amont
int boucleAval;   // Declaration d'une variable pour la boucle Aval


void setup() {
  initI2C(250);   // initialisation de la vitesse du bus I2C
  Serial.begin(9600); // initialisation de la vitesse de la liaison serie a 9600 bauds
}

void loop() {

   static int nbVoiture=0;  // initialisation du nombre de voiture a 0
   Serial.print("Nb Voiture: ");  // Affiche sur le moniteur Serie le texte "Nb Voiture: "
   Serial.println(nbVoiture);     // Affiche le nombre de voiture
   Wire.beginTransmission(0x20);  // Initialisation de la transmission du bus I2C pour le capteur des boucles qui est a l'adresse 0x20
   lireBoucleAval(boucleAval);    // Appel d'une fonction qui lit l'etat de la boucle Aval
   lireBoucleAmont(boucleAmont);  // Appel d'une fonction qui lit l'etat de la boucle Amont
      if ( boucleAmont == 0 && boucleAval == 64){ // Si il y a une Voiture sur la boucle Amont et pas sur la boucle Aval
          entrerVehicule(nbVoiture,boucleAmont,boucleAval);
      }
      lireBoucleAval(boucleAval); // Appel d'une fonction qui lit l'etat de la boucle Aval
      lireBoucleAmont(boucleAmont); // Appel d'une fonction qui lit l'etat de la boucle Amont
      if (boucleAval == 0 && boucleAmont == 32 ){ // Si il y a une Voiture sur la boucle Aval et pas sur la boucle amont
          sortieVehicule(nbVoiture,boucleAmont,boucleAval);
      }
}

