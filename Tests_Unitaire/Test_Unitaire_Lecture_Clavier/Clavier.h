#ifndef _CLAVIER_H
#define _CLAVIER_H

#include <Wire.h>
#include "I2C.h"

int detectionTouche (void);

char conversionTouche (void);

void afficherCode(const char* const,const int&);

#endif
