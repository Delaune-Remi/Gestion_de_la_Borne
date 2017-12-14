#include <EEPROM.h>

int adresse = 1;
int valeur = 7;
int value;

void setup() {
  Serial.begin(9600);
  while (!Serial){
    
  }
}

void loop() {
  if (adresse == 1){
    EEPROM.write(adresse,0);
    adresse++;
  }/*
  if(adresse == 2){
    EEPROM.write(adresse,valeur);
    adresse++;
  }*/
  if (adresse == 3){
     EEPROM.write(adresse,'1');
     adresse++;
     EEPROM.write(adresse,'2');
     adresse++;
     EEPROM.write(adresse,'3');
     adresse++;
     EEPROM.write(adresse,'4');
  }
for (int address = 1 ;address <10;address++){
   value = EEPROM.read(address); // lecture de la valeur a l'adresse renseignee

  Serial.print("L'adresse est :");
  Serial.println(address);
  Serial.print("La valeur est :");
  Serial.println(value);
  Serial.println();
}
  
}
