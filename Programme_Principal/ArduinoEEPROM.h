#ifndef _ARDUINOEEPROM_H
#define _ARDUINOEEPROM_H

#include <EEPROM.h> // inclusion de la library 

void ecritureVoitureEEPROM(int);

int lectureVoitureEEPROM(void);

void ecritureCodesEEPROM(char,int);

void lectureCodesEEPROM(char* const,int&);

int lectureCodeMaxEEPROM(void);

#endif
