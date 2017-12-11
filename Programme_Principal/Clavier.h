#ifndef _CLAVIER_H
#define _CLAVIER_H


char conversionTouche(void);

 /*
  * Fonction permettant de convertir la touche est appuyer en caractere.
  * 
  * La fonction n'a pas de parametre d'entrer.
  * 
  * Elle renvoie une variable de type caractere qui contient le caractere correspond a la touche appuyer.
  * 
  */

int detectionTouche(void);
 
 /*
  * Fonction permettant de detecter si une touche est appuyer.
  * 
  * La fonction n'a pas de parametre d'entrer.
  * 
  * Elle renvoie une variable de type entier:
  *   - 0 :  touche non detecter
  *   - 1 :  touche detecter
  * 
  */

void lectureClavier (char*);

/*
 * Fonction permettant de lire le code entrer sur le clavier.
 * 
 * La fonction a pour parametre d'entrer:
 *  - L'espace memoire reserve au code
 * 
 * Elle ne renvoie rien
 */


#endif
