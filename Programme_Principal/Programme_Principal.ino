#include "barriere.h" // Inclussion de la bibliotheque barriere.h permettant de gerer la barriere


int code = 12;    // initialisation du password a 12
int carte;
int boucleAmont;
int boucleAval;

void setup() {
  initI2C(250);   // initialisation de la vitesse du bus I2C
  Serial.begin(9600); // initialisation de la vitesse de la liaison serie a 9600 bauds
}

void loop() {
  static int nbVoiture=0;  // initialisation du nombre de voiture a 0
   Serial.print("Nb Voiture: ");
   Serial.println(nbVoiture);
   Wire.beginTransmission(0x20);// initialisation de la transmission du bus I2C pour le capteur des boucles qui est a l'adresse 0x20
   lireBoucleAval(boucleAval);
   lireBoucleAmont(boucleAmont);
      if ( boucleAmont == 0 && boucleAval == 64){ // Si il y a une Voiture sur la boucle Amont et pas sur la boucle Aval
        Serial.println("Boucle Amont");
        Wire.beginTransmission(0x21); // initialisation de la transmission du bus I2C pour le capteur de carte a puce qui est a l'adresse 0x50
        Wire.requestFrom (0x21,1);
        carte=Wire.read();
        carte &= 0x01;
        if ( carte == 0){  // Condition permettant de verifier si il y a une carte a puce de detecter ( detecter: 0 et non detecter: 1)
          if (code == 12){  // Si le code est egal a 12 alors on ouvre la barriere
            ouvertureBarriereEntrer (nbVoiture); // Fonction pour ouvrir la barriere, on donne le nombre de voiture actuel
          }else{
            Wire.beginTransmission (0x20);
            do{
              Serial.println ("Veuillez quitter l'entrer"); // affiche sur la liaison serie un message
              lireBoucleAval(boucleAval);
              lireBoucleAmont(boucleAmont);
            }while ( boucleAmont == 0);  // tant que la boucle amont detecte un vehicule ( detecter: 0 et non detecter: 1)
          }
        }
      }
      lireBoucleAval(boucleAval);
      lireBoucleAmont(boucleAmont);
      if (boucleAval == 0 && boucleAmont == 32 ){ // Si il y a une Voiture sur la boucle Aval et pas sur la boucle amont
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
