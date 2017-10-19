#include "barriere.h" // Inclussion de la bibliotheque barriere.h permettant de gerer la barriere

int code = 12;    // Initialisation du password a 12
int carte;        /* Declaration d'une variable de type entier 
                  qui permettera de detecter si il y a une carte d'inserer
                  */
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
   lireBoucleAval(boucleAval);    // Appel d'une fonction qui lit l'état de la boucle Aval
   lireBoucleAmont(boucleAmont);  // Appel d'une fonction qui lit l'état de la boucle Amont
      if ( boucleAmont == 0 && boucleAval == 64){ // Si il y a une Voiture sur la boucle Amont et pas sur la boucle Aval
        Serial.println("Boucle Amont"); // Affiche sur le moniteur Serie le texte "Boucle Amont: "
        detecterCarte(carte);     // Appel d'une fonction qui detecte une carte
        if ( carte == 0){  // Condition permettant de verifier si il y a une carte a puce de detecter ( detecter: 0 et non detecter: 1)
          if (code == 12){  // Si le code est egal a 12 alors on ouvre la barriere
            ouvertureBarriereEntrer (nbVoiture); // Fonction pour ouvrir la barriere quand un vehicule rentre, on donne le nombre de voiture actuel
          }else{
            Wire.beginTransmission (0x20);       // Initialisation de la transmission du bus I2C pour le capteur des boucle qui est a l'adresse 0x20
            do{
              Serial.println ("Veuillez quitter l'entrer"); // Affiche sur la liaison serie un message
              lireBoucleAval(boucleAval);
              lireBoucleAmont(boucleAmont);
            }while ( boucleAmont == 0);  // tant que la boucle amont detecte un vehicule ( detecter: 0 et non detecter: 1)
          }
        }
      }
      lireBoucleAval(boucleAval);
      lireBoucleAmont(boucleAmont);
      if (boucleAval == 0 && boucleAmont == 32 ){ // Si il y a une Voiture sur la boucle Aval et pas sur la boucle amont
          sortieVehicule(nbVoiture,boucleAmont,boucleAval);
      }
}

/*
 *          Valeur Donnee :
 *          
 * 32 : Voiture pas detecter sur Amont
 * 64 : Voiture pas detecter sur Aval
 * 
 * Si l'une des boucles detecte un voiture la boucle, se met a 0 
 * 
 */ 
