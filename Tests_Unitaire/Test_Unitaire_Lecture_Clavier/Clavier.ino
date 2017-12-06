#include "Clavier.h"

int detectionTouche(void){
  int val=0;    //initialisation d'un variable "val" a 0
  int detect=0; //initialisation d'un variable "detect" a 0 qui permettra de savoir si la touche est detectee
                //Nous avons une touche detectee lorsque la valeur passe a 1
  
  Wire.beginTransmission(0x22); 
  Wire.write(0x0F);       // Ecriture sur le clavier de la valeur 0F en hexa pour permettre de savoir si elle change
  Wire.endTransmission(); 
  Wire.requestFrom(0x22,1); // Permet de dire au clavier que l'on va lire sa valeur
  val=Wire.read();          // Recuperer les informations du clavier 
  if (val!=15){   //Si la valeur recuperee est differente de 0x0F en decimal soit (15)10 
    detect++;     
  }
  return detect;  
}

char conversionTouche(void){ 
  int valColonne=0;
  int valLigne=0;
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

void affichageCode (const char* const code, const int& taille){
  Serial.print("Le Code entrer est : ");
  
  for (int i=0; i<taille;i++){
    Serial.print(*(code+i));
  }
  Serial.println("");
}

