#include "barriere.h"

#define tailleCodeEEPROM (lectureCodeMaxEEPROM())-3


void ouvertureBarriereEntrer (int& nbVehicule){
  int tempo=0,boucleAmont,boucleAval;
  ouvrirBarriere();
  lireBoucleAval(boucleAval);
  lireBoucleAmont(boucleAmont);
  while( boucleAmont == 0 && boucleAval == 64 && tempo < 3000){
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
        nbVehicule+=1;
        ecritureVoitureEEPROM(nbVehicule);
        Serial.print("Nb Voiture: ");
        Serial.println(lectureVoitureEEPROM());
      }  
  }
  effacerAfficheur(0x3B);
  envoyerMessage(0x3B,MESSAGE8,LIGNE1);
  envoyerMessage(0x3B,MESSAGE6,LIGNE2);
  do{
    fermerBarriere();
    lireBoucleAmont(boucleAmont); //Appel d'une fonction qui detecte l'etat de la boucle Amont
  }while ( boucleAmont == 0);      // tant que la boucle amont detecte un vehicule  
  
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
        ecritureVoitureEEPROM(--nbVoiture); // decrementation du nombre de voiture
     }
    effacerAfficheur(0x3B);
    setEclairage(0x21,HIGH);
    envoyerMessage(0x3B,MESSAGE5,LIGNE1);
    fermerBarriere ();  // Fonction permettant de fermer la barriere
}

void entrerVehicule (int& nbVoiture,int& boucleAmont, int& boucleAval){
   int toucheDetecter=0;  //  Initialisation d'une variable qui permet de detecter si une touche est appuyer
   int i=0,essaiCode;
   char* codeClavier(NULL);// Initialisation d'un pointeur du charactere a NULL qui permet de recuperer le code ecrit au clavier
   codeClavier = new char [TAILLECODE];
   char* code (NULL);    // Initialisation d'un pointeur sur caractere qui vas contenir le code a NULL
   code = new char [TAILLECODE+1];
   char* codeEEPROM (NULL);    // Initialisation d'un pointeur sur caractere qui vas contenir le code a NULL
   codeEEPROM = new char [tailleCodeEEPROM];
   int carte;        // Declaration d'une variable de type entier qui permettera de detecter si il y a une carte d'inserer
   delay(2000);
   effacerAfficheur(0x3B);
   envoyerMessage(0x3B,MESSAGE2,LIGNE1);
   envoyerMessage(0x3B,"ou une Carte",LIGNE2);
   for(int i=0; i<=20000 && toucheDetecter != 1 && ((carte & 0x01) == 1 || i<2 ) && boucleAmont == 0 ; i++){
        toucheDetecter=detectionTouche();
        detecterCarte(carte);     // Appel d'une fonction qui detecte une carte
        lireBoucleAmont(boucleAmont);
    }
   if ((carte & 0x01) == 0){ // Condition permettant de verifier si il y a une carte a puce de detecter
      effacerAfficheur(0x3B);
      setEclairage(0x21,HIGH);
      envoyerMessage(0x3B,"Votre Code :",LIGNE1);
      lectureCodeCarte(code);
      if (validationCode(code,codeEEPROM)==1){  // Si le code est egal a 3456 alors on ouvre la barriere
         ouvertureBarriereEntrer (nbVoiture); // Fonction pour ouvrir la barriere quand un vehicule rentre, on donne le nombre de voiture actuel
         delete[] code;
      }else{
          Wire.beginTransmission (0x20);       // Initialisation de la transmission du bus I2C pour le capteur des boucle qui est a l'adresse 0x20
         do{
            effacerAfficheur(0x3B);
            setEclairage(0x21,HIGH);
            envoyerMessage(0x3B,MESSAGE8,LIGNE1);
            lireBoucleAmont(boucleAmont); //Appel d'une fonction qui detecte l'etat de la boucle Amont
         }while ( boucleAmont == 0);      // tant que la boucle amont detecte un vehicule
      }
   }else{
      if (toucheDetecter == 1){
        effacerAfficheur(0x3B);
        setEclairage(0x21,HIGH);
        envoyerMessage(0x3B,MESSAGE2,LIGNE1);
        essaiCode=0;
        do{
          effacerAfficheur(0x3B);
          envoyerMessage(0x3B,"Votre Code :",LIGNE1);
          lectureClavier(codeClavier);
          essaiCode++;
        }while ( validationCode(codeClavier,codeEEPROM) == 0 && (essaiCode<3));
        if (validationCode(codeClavier,codeEEPROM)== 1){
          effacerAfficheur(0x3B);
          envoyerMessage(0x3B,MESSAGE3,LIGNE1);
          ouvertureBarriereEntrer(nbVoiture);
        }else{
          effacerAfficheur(0x3B);
          envoyerMessage(0x3B,MESSAGE8,LIGNE1);
          envoyerMessage(0x3B,MESSAGE6,LIGNE2);
          do{
            lireBoucleAmont(boucleAmont); //Appel d'une fonction qui detecte l'etat de la boucle Amont
          }while ( boucleAmont == 0);      // tant que la boucle amont detecte un vehicule
        }
        delete [] codeClavier;
        delete [] codeEEPROM;
      }else{
        effacerAfficheur(0x3B);
        envoyerMessage(0x3B,MESSAGE5,LIGNE1);
        envoyerMessage(0x3B,MESSAGE6,LIGNE2);   
      } 
   }
  effacerAfficheur(0x3B);
}



int validationCode(const char* const code, char* const codeEEPROM){
  int maxCode,i=0;
  int j=0;
  lectureCodesEEPROM(codeEEPROM,maxCode);
  for (i = 0; *(code)!= *(codeEEPROM+i) && *(code+1) != *(codeEEPROM+1+i) && *(code+2) != *(codeEEPROM+2+i) && *(code+3) != *(codeEEPROM+3+i) && (i<(maxCode-3));i+=4){
 
  }
  if (*(code)== *(codeEEPROM+i) && *(code+1) == *(codeEEPROM+1+i) && *(code+2) == *(codeEEPROM+2+i) && *(code+3) == *(codeEEPROM+3+i) ){
     Serial.print("Code Clavier : ");
     do{
        Serial.print(*(code+j));
        j++;
     }while(j<i);
     Serial.println();
     Serial.print("Code EEPROM : ");
     j=0;
     do{
        Serial.print(*((codeEEPROM+i)-(5+j)));
        j++;
     }while(j<i);
     Serial.println();
     effacerAfficheur(0x3B);
     envoyerMessage(0x3B,MESSAGE3,LIGNE1);
     return 1;
  }else{
     Serial.print("Code Clavier : ");
     for (int i=0;i<5;i++){
        Serial.print(*(code+i));
     }
     Serial.println();
     Serial.print("Code EEPROM : ");
     for (int i=0;i<5;i++){
        Serial.print(*(codeEEPROM+i));
     }
     Serial.println();
     
     effacerAfficheur(0x3B);
     envoyerMessage(0x3B,MESSAGE9,LIGNE1);
     delay(2000);
     return 0;
  }
}

