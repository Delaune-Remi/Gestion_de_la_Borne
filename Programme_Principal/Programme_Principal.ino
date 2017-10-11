#include "barriere.h" // Inclussion de la bibliotheque barriere.h permettant de gerer la barriere

int nbVoiture=0;  // initialisation du nombre de voiture a 0
int code = 12;    // initialisation du password a 12

void setup() {
  initI2C(120);   // initialisation de la vitesse du bus I2C
  Serial.begin(9600); // initialisation de la vitesse de la liaison serie a 9600 bauds
}

void loop() {
   Wire.beginTransmission(0x21);  // initialisation de la transmission du bus I2C pour le capteur des boucles qui est a l'adresse 0x21
      if ( (Wire.read() & 0x60) == 64){ // Si il y a une Voiture sur la boucle Amont
        Wire.beginTransmission(0x50); // initialisation de la transmission du bus I2C pour le capteur de carte a puce qui est a l'adresse 0x50
        if ( (Wire.read() & 0x01) == 0){  // Condition permettant de verifier si il y a une carte a puce de detecter ( detecter: 0 et non detecter: 1)
          if (code == 12){  // Si le code est egal a 12 alors on ouvre la barriere
            ouvrir (); // Fonction pour ouvrir la barriere
            Wire.beginTransmission(0x21);
          }else{
            Wire.beginTransmission (0x21);
            do{
              Serial.println ("Veuillez quitter l'entrer"); // affiche sur la liaison serie un message
            }while ( (Wire.read() & 0x20) == 0);  // tant que la boucle amont detecte un vehicule ( detecter: 0 et non detecter: 1)
          }
        }
      }
      if ( (Wire.read() & 0x60) == 32){     // Si il y a une Voiture sur la boucle Aval et pas sur la boucle amont
          ouvrir ();
          while ( (Wire.read() & 0x60) == 32);  // tant qu'il y a un vehicule sur la boucle Aval et pas sur la boucle amont
          if ( (Wire.read() & 0x60) != 96){ // si il y a un vehicule de detecter sur la boucle aval ou amont
            while ( (Wire.read() & 0x40) == 0 || (Wire.read() & 0x20) == 0);  //tant qu'il y a un vehicule sur la boucle amont ou sur la boucle aval on ne fait rien
            nbVoiture--; // decrementation du nombre de voiture
          }
          fermer ();  // Fonction permettant de fermer la barriere
      }
}
