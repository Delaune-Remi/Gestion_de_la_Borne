#ifndef _CLAVIER_H
#define _CLAVIER_H

#include <Wire.h>
#include "I2C.h"

int detectionTouche(void);
/*
 * Fonction permettant de detecter si il y a une touche d'appuyer
 * Elle retourne:
 *  0 : Aucune touche est appuyer
 *  1 : Une touche est appuyer
 */

#endif
