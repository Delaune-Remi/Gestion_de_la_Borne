#include <EEPROM.h>

int adresse = 1;
int valeur;
int value,j=0,i=0;
char code = ' ';

void setup() {
  Serial.begin(9600);
  while (!Serial){
    
  }
}

void loop() {
  /*if (adresse == 1){
    EEPROM.write(adresse,0);
    adresse++;
  }
  if (adresse == 3){
    EEPROM.write(adresse,'1');
    adresse++;
    EEPROM.write(adresse,'2');
    adresse++;
    EEPROM.write(adresse,'3');
    adresse++;
    EEPROM.write(adresse,'4');
    adresse++;
    valeur=adresse;
    EEPROM.write(2,valeur);
  }*/
  if (adresse == 7){
    EEPROM.write(adresse,'3');
    adresse++;
    EEPROM.write(adresse,'4');
    adresse++;
    EEPROM.write(adresse,'5');
    adresse++;
    EEPROM.write(adresse,'6');
    adresse++;
    valeur=adresse;
    EEPROM.write(2,valeur);
  }
  if (adresse == 11){
    EEPROM.write(adresse,255);
    adresse++;
    EEPROM.write(adresse,255);
    adresse++;
    EEPROM.write(adresse,255);
    adresse++;
    EEPROM.write(adresse,255);
  }

adresse++;
for (int address = 1 ;address <15;address++){
   value = EEPROM.read(address); // lecture de la valeur a l'adresse renseignee

  Serial.print("L'adresse est :");
  Serial.println(address);
  Serial.print("La valeur est :");
  Serial.println(value);
  Serial.println();
}
delay(300);
}
