#ifndef _BARRIERE_H
#define _BARRIERE_H

#include <Wire.h>
#include "I2C.h"

void ouvertureBarriereEntrer(int&);

void fermer(void);

void ouvrirBarriere(void);

void lireBoucleAval(int&);

void lireBoucleAmont(int&);

void sortieVehicule(int&,int&,int&);

void detecterCarte (int&);

#endif
