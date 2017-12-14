#ifndef _CARTEPUCE_H
#define _CARTEPUCE_H

void detecterCarte (int&);

/*
 * Fonction permettant de detecter la presence d'une carte a puce.
 * 
 * La fonction a pour parametre d'entrer: 
 *  - La variable pour la carte a puce
 * 
 * Elle ne renvoie rien.
 * 
 *     Valeur Donnee :
 * 
 * - 0 => La carte est detecter
 * - 1 => La carte n'est pas detecter
 * 
 */

 void lectureCodeCarte(char*);

/*
 * Fonction permettant de lire le code de la carte a puce.
 * 
 * La fonction a pour parametre d'entrer:
 *  - L'espace memoire reserve au code
 * 
 * Elle ne renvoie rien
 */
 
#endif
