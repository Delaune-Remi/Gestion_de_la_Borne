#include "barriere.h"

#define TAILLECODE 4


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
        nbVehicule++;
        Serial.print("Nb Voiture: ");
        Serial.println(nbVehicule);
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
        nbVoiture--; // decrementation du nombre de voiture
     }
    effacerAfficheur(0x3B);
    setEclairage(0x21,HIGH);
    envoyerMessage(0x3B,MESSAGE5,LIGNE1);
    fermerBarriere ();  // Fonction permettant de fermer la barriere
}

void detecterCarte (int& carte){
  Wire.beginTransmission(0x21);   // Initialisation de la transmission du bus I2C pour le capteur de carte a puce qui est a l'adresse 0x21
  Wire.requestFrom (0x21,2);
  carte=Wire.read();
}

void entrerVehicule (int& nbVoiture,int& boucleAmont, int& boucleAval){
   int toucheDetecter=0;  //  Initialisation d'une variable qui permet de detecter si une touche est appuyer
   int i=0,essaiCode;
   char* codeClavier(NULL);// Initialisation d'un pointeur du charactere a NULL qui permet de recuperer le code ecrit au clavier
   codeClavier = new char [TAILLECODE];
   char* code (NULL);    // Initialisation d'un pointeur sur caractere qui vas contenir le code a NULL
   code = new char [TAILLECODE+1];
   char* codeEEPROM (NULL);    // Initialisation d'un pointeur sur caractere qui vas contenir le code a NULL
   codeEEPROM = new char [TAILLECODE];
   getCodeEEPROM(codeEEPROM);
   int carte;        // Declaration d'une variable de type entier qui permettera de detecter si il y a une carte d'inserer
   delay(2000);
   effacerAfficheur(0x3B);
   envoyerMessage(0x3B,MESSAGE2,LIGNE1);
   envoyerMessage(0x3B,"ou une Carte",LIGNE2);
   for(int i=0; i<=2000 && toucheDetecter != 1 && ((carte & 0x01) == 1 || i<2 ) ; i++){
        toucheDetecter=detectionTouche();
        detecterCarte(carte);     // Appel d'une fonction qui detecte une carte
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
      }else{
        effacerAfficheur(0x3B);
        envoyerMessage(0x3B,MESSAGE5,LIGNE1);
        envoyerMessage(0x3B,MESSAGE6,LIGNE2);   
      } 
   }
  effacerAfficheur(0x3B);
}

int detectionTouche (void){
  int val=0,detect=0;
  
  Wire.beginTransmission(0x22);
  Wire.write(0x0F);
  Wire.endTransmission();
  Wire.requestFrom(0x22,1);
  val=Wire.read();
  if (val!=15){
    detect++;
  }
  return detect;
}

char conversionTouche(void){
  int valColonne=0,valLigne=0;
  char valeur=' ';
  
  while (valeur == ' '){
    Wire.beginTransmission(0x22);
    Wire.write(0x0F);
    Wire.endTransmission();
    Wire.requestFrom(0x22,1);
    valLigne=Wire.read();
    if (valLigne!=15){
      Wire.beginTransmission(0x22);
      Wire.write(0x70);
      Wire.endTransmission();
      Wire.requestFrom(0x22,1);
      valColonne=Wire.read();
    }
    switch (valLigne){
      case 15:
         break;
      case 14:
        switch(valColonne){
          case 96:
            valeur = '1';
            break;
          case 80:
            valeur = '2';
            break;
          case 48:
            valeur = '3';
        }
        break;
      case 13:
        switch(valColonne){
          case 96:
            valeur = '4';
            break;
          case 80:
            valeur = '5';
            break;
          case 48:
            valeur = '6';
        }
        break;
      case 11:
         switch(valColonne){
          case 96:
            valeur = '7';
            break;
          case 80:
            valeur = '8';
            break;
          case 48:
            valeur = '9';
            break;
          default:
            valeur = 'A';
        }
        break;
      case 7:
        switch(valColonne){
          case 96:
            valeur = '*';
            break;
          case 80:
            valeur = '0';
            break;
          case 48:
            valeur = '#';
        }
      }
  }
  return valeur;
}

void lectureClavier(char* code){  
  int touchedetecter=0;
  int i=0;
  while (i<TAILLECODE){
     touchedetecter=detectionTouche();
     if (touchedetecter==1){
      *(code+i)= conversionTouche();
      if (*(code+i)!='A'){
        i++;
      }
     }
     switch(i){
        case 1:
          envoyerMessage(0x3B,"       *",LIGNE2);
          break;
        case 2:
          envoyerMessage(0x3B,"      **",LIGNE2);
          break;
        case 3:
          envoyerMessage(0x3B,"      ***",LIGNE2);
          break;
        case 4:
          envoyerMessage(0x3B,"     ****",LIGNE2);
          break;
     }
     
     delay(200);
  }
}

void lectureCodeCarte(char* code){
  byte* valCode(NULL);
  valCode = new byte [5];
  
  Wire.beginTransmission(0x21);
  Wire.requestFrom(0x21,2); // 0x21 adresse de la carte a puce
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.beginTransmission(0x50);
  Wire.requestFrom(0x50,5,true); // 0x50 adresse de l'EPROM I2C de la carte a puce
  setEclairage(0x21,HIGH);
  *valCode=Wire.read();
  *(valCode+1)=Wire.read();
  envoyerMessage(0x3B,"       *",LIGNE2);
  *(valCode+2)=Wire.read();
  envoyerMessage(0x3B,"      **",LIGNE2);
  *(valCode+3)=Wire.read();
  envoyerMessage(0x3B,"      ***",LIGNE2);
  *(valCode+4)=Wire.read();
  envoyerMessage(0x3B,"     ****",LIGNE2);
  effacerAfficheur(0x3B);
  Wire.endTransmission();
  Wire.beginTransmission(0x21);
  Wire.write(0x01);
   for (int i = 1;i<5;i++){
     Serial.print(*(valCode+i));
   }
  for (int i = 0;i<5;i++){
     *(code+i)=static_cast<char>(*(valCode+1+i));
   }
  
  delete [] valCode;
}

int validationCode(const char* const code,const char* const codeEEPROM){
 if ((*code == '6' && *(code+1) == '4' && *(code+2)== '5' && *(code+3)=='6' )|| (*code == '1' && *(code+1) == '2' && *(code+2)== '3' && *(code+3)=='4' )/*|| (*(code)== *(codeEEPROM) && *(code+1) == *(codeEEPROM+1) && *(code+2) == *(codeEEPROM+2)&& *(code+3) == *(codeEEPROM+3*/){
     return 1;
  }else{
     return 0;
  }
}

void setCodeEEPROM(void){
  Wire.beginTransmission(0x57);
  Wire.write(49);
  Wire.write(57);
  Wire.write(57);
  Wire.write(56);
  Wire.endTransmission();
}

void getCodeEEPROM(char* codeEEPROM){
  byte* valCode(NULL);
  valCode = new byte [4]; 
  Wire.beginTransmission(0x57);
  Wire.requestFrom(0x57,4,true); // 0x57 adresse de l'EEPROM I2C de la memoire
  *(valCode)=Wire.read();
  *(valCode+1)=Wire.read();
  *(valCode+2)=Wire.read();
  *(valCode+3)=Wire.read();
  Wire.endTransmission();
  Serial.println("Code EEPROM:");
  for (int i = 0;i<4;i++){
     Serial.print(*(valCode+i));
   }
  Serial.println(" ");
  Serial.println("Code EEPROM:");
  for (int i = 0;i<4;i++){
     *(codeEEPROM+i)=static_cast<char>(*(valCode+i));
     Serial.print(*(codeEEPROM+i));
   }
  Serial.println(" ");
  delete [] valCode;
}

void gardien(int nbVoiture){
  static int essai=0;
  if (nbVoiture == 0 && essai <= 6){
    char c;
    Serial.print("Voulez-vous entrer des codes valides (Y : yes) :");
    delay(300);
    while (Serial.available()) { // tant que des caractères sont en attente d'être lus
      c = Serial.read(); // on lit le charactère
      Serial.println(c);
      delay(10); // petit temps de pause
    }
    if (c == 'Y' || c == 'y'){
      //entrerCodeGardien(code);
      essai=7;
    }  
   essai++;  
   delay(2000);
  }
  Serial.print("Le nombre de Voiture presente dans le parking est:");
  Serial.println(nbVoiture);


}

 void entrerCodeGardien(char* const code){
  int i=0;
  Serial.println("Ecrire un code Valide");
  delay(300);
  while (Serial.available()|| i<TAILLECODE) { // tant que des caractères sont en attente d'être lus
    char c = Serial.read(); // on lit le charactère
    *(code+i)=c;
    delay(10); // petit temps de pause
    i++;
  }
  Serial.print("Le code est :");
  for (int i=0;i<TAILLECODE;i++){
    Serial.print(*(code+i));
  }
  Serial.println(" ");
  delay(2000);
 }
