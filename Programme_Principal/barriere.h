#ifndef _BARRIERE_H
#define _BARRIERE_H

#include <Wire.h>   // Inclusion de la librairie pour les Liaison Series
#include "I2C.h"    // Inclusion de la librairie permettant d'initialiser le bus I2C 

void ouvertureBarriereEntrer(int&);

/*
 * Fonction permettant d'ouvrir la barriere et d'attendre que le vehicule entre dans le parking.
 * 
 * La fonction a pour parametre d'entrer:
 *  - Le nombre de vehicule present dans le parking
 *  
 * La fonction ne renvoie rien. 
 */

void fermerBarriere(void);

/*
 * Fonction permettant de fermer la barriere.
 * 
 * La fonction a aucun parametre et ne renvoie rien.
 */

void ouvrirBarriere(void);
/*
 * Fonction permettant d'ouvrir la barriere.
 * 
 * La fonction a aucun parametre et ne renvoie rien.
 */

void lireBoucleAval(int&);

/*
 * Fonction permettant de lire l'etat de la boucle Aval.
 * 
 * La fonction a pour parametre d'entrer:
 *  - La variable de la boucle Aval 
 *  
 *  Elle ne renvoie rien.
 *  
 *          Valeur Donnee :
 *          
 * 64 : Voiture pas detecter sur Aval
 * 
 * Si la boucle detecte un voiture la boucle se met a 0 .
 * 
 */

void lireBoucleAmont(int&);

/*
 * Fonction permettant de lire l'etat de la boucle Amont.
 * 
 * La fonction a pour parametre d'entrer:
 *  - La variable de la boucle Amont 
 *  
 *  Elle ne renvoie rien.
 *  
 *     Valeur Donnee :
 *          
 * 32 : Voiture pas detecter sur Amont
 * 
 * Si la boucle detecte un voiture la boucle se met a 0 .
 * 
 */

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

void sortieVehicule(int&,int&,int&);

/*
 * Fonction permettant de faire sortir un vehicule du parking.
 * 
 * La fonction a pour parametre d'entrer:
 *  - Le nombre de vehicule
 *  - La variable pour la boucle Amont
 *  - La variable pour la boucle Aval
 *  
 * Elle ne renvoie rien.
 */

void entrerVehicule(int&,int&,int&); 

/*
 * Fonction permettant de faire entrer un vehicule du parking.
 * 
 * La fonction a pour parametre d'entrer:
 *  - Le nombre de vehicule
 *  - La variable pour la boucle Amont
 *  - La variable pour la boucle Aval
 *  
 * Elle ne renvoie rien.
 */

#endif
