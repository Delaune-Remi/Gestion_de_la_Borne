#include <Wire.h>
#include "I2C.h"

void setup() { 
}

void loop() {
  initI2C(120);
  Serial.begin(1200);
  int val;
  Wire.beginTransmission(0x57);
  Wire.requestFrom(0x57,4);
  val=Wire.read();
  Serial.print("La valeur :");
  Serial.println(val);
  Wire.endTransmission();
}
