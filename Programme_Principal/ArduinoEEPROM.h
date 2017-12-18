#ifndef _ARDUINOEEPROM_H
#define _ARDUINOEEPROM_H

#include <EEPROM.h> // inclusion de la library 

void ecritureVoitureEEPROM(int);
/*
 * Fonction permettant d'ecrire le nombre de voiture dans l'EEPROM de l'arduino.
 * 
 * Elle prend pour parametre:
 * 
 * -  Le nombre de voitures
 * 
 * Elle ne renvoie rien
 */

int lectureVoitureEEPROM(void);
/*
 * Fonction permettant de lire le nombre de voiture dans l'EEPROM de l'arduino.
 * 
 * Elle prend aucun parametre:
 * 
 * Elle renvoie le nombre de voiture presente dans le parking
 */

void ecritureCodesEEPROM(char,int);
/*
 * Fonction permettant d'ecrire les codes valides dans l'EEPROM de l'arduino.
 * 
 * Elle prend pour parametre:
 * 
 * - le caractere a ecrire
 * - le chiffre du caractere par rapport au code
 * 
 * Elle ne renvoie rien.
 */
 
void lectureCodesEEPROM(char* const,int&);
/*
 * Fonction permettant de lire les codes valides dans l'EEPROM de l'arduino.
 * 
 * Elle prend pour parametre:
 * 
 * - l'espace memoire reserve pour le code de l'EEPROM
 * - l'adresse suivant le dernier code
 * 
 * Elle ne renvoie rien.
 */

int lectureCodeMaxEEPROM(void);
/*
 * Fonction permettant de lire dans l'EEPROM de l'arduino l'adresse suivant le dernier code,celle-ci est stocker dans l'EEPROM.
 * 
 * Elle prend aucun parametre:
 * 
 * Elle ne renvoie l'adresse qui suit le dernier code
 */
 
#endif
