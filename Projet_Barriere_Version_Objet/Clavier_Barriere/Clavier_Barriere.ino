#include "Clavier_Barriere.h"

Clavier_Barriere::Clavier_Barriere(){
    this->code = new char [4];
    strcpy(this->code,NULL);
    this->toucheDetecter=0;
    this->valeurLigne=0;
    this->valeurColonne=0;
}

Clavier_Barriere::~Clavier_Barriere(){
    delete [] this->code;
}

int Clavier_Barriere::getValeurColonne(void){
  return this->valeurColonne;
}

int Clavier_Barriere::getValeurLigne(void){
  return this->valeurLigne;
}

void Clavier_Barriere::setCode(int position1,char valeur){
  if (position1<4){
    strcpy(this->code+position1,valeur);
  }
}

