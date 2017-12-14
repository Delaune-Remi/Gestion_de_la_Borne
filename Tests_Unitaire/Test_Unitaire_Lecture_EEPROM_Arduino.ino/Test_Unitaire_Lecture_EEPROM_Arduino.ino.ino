#include <EEPROM.h>

int address = 1; // adresse de l'EEPROM a 1
byte value; // valeur recue a l'adresse

void setup() {
  Serial.begin(9600);
  while (!Serial){
      // attente qu'on ouvre le moniteur serie
  }
}

void loop() {
  value = EEPROM.read(address); // lecture de la valeur a l'adresse renseignee

  Serial.print("L'adresse est :");
  Serial.println(address);
  Serial.print("La valeur est :");
  Serial.println(value);
  Serial.println();
  address += 1; //increment de l'adresse

  if (address == EEPROM.length()){  // si l'adresse est egal a la longueur de l'EEPROM
    address = 0; //affectation de l'adresse a 0
  }
  
  delay(500); // attente de 500 ms
}
