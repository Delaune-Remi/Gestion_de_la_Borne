#include "barriere.h"

void ouvertureBarriereEntrer (int& nbVehicule){
  int tempo=0,boucleAmont,boucleAval;
  ouvrirBarriere();
  lireBoucleAval(boucleAval);
  lireBoucleAmont(boucleAmont);
  while( boucleAmont == 0 && boucleAval == 64 && tempo < 30000){
    delay(1);
    tempo++;
    lireBoucleAval(boucleAval);
    lireBoucleAmont(boucleAmont);
  }
  lireBoucleAval(boucleAval);
  lireBoucleAmont(boucleAmont);
  if (boucleAmont == 0 && boucleAval == 0){
      lireBoucleAval(boucleAval);
      lireBoucleAmont(boucleAmont);
      if (boucleAmont == 0 || boucleAval == 0){
        lireBoucleAval(boucleAval);
        lireBoucleAmont(boucleAmont);
        while ( boucleAmont == 0 || boucleAval == 0){
          lireBoucleAval(boucleAval);
          lireBoucleAmont(boucleAmont);
        }
        nbVehicule++;
        Serial.print("Nb Voiture: ");
        Serial.println(nbVehicule);
      }  
  }  
  fermerBarriere();
}

void fermerBarriere (void){
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
    fermerBarriere ();  // Fonction permettant de fermer la barriere
}

void detecterCarte (int& carte){
  Wire.beginTransmission(0x21);   // Initialisation de la transmission du bus I2C pour le capteur de carte a puce qui est a l'adresse 0x21
  Wire.requestFrom (0x21,1);
  carte = Wire.read();
  carte &= 0x01;
}

void entrerVehicule (int& nbVoiture,int& boucleAmont, int& boucleAval){
   int code = 12;    // Initialisation du password a 12
   int carte;        // Declaration d'une variable de type entier qui permettera de detecter si il y a une carte d'inserer
   Serial.println("Boucle Amont"); // Affiche sur le moniteur Serie le texte "Boucle Amont: "
   detecterCarte(carte);     // Appel d'une fonction qui detecte une carte
   if ( carte == 0){  // Condition permettant de verifier si il y a une carte a puce de detecter
      if (code == 12){  // Si le code est egal a 12 alors on ouvre la barriere
         ouvertureBarriereEntrer (nbVoiture); // Fonction pour ouvrir la barriere quand un vehicule rentre, on donne le nombre de voiture actuel
      }else{
         Wire.beginTransmission (0x20);       // Initialisation de la transmission du bus I2C pour le capteur des boucle qui est a l'adresse 0x20
         do{
            Serial.println ("Veuillez quitter l'entrer"); // Affiche sur la liaison serie un message
            lireBoucleAval(boucleAval);   //Appel d'une fonction qui detecte l'etat de la boucle Aval
            lireBoucleAmont(boucleAmont); //Appel d'une fonction qui detecte l'etat de la boucle Amont
         }while ( boucleAmont == 0);      // tant que la boucle amont detecte un vehicule
      }
   }
}

