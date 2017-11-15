#ifndef _CLAVIER_BARRIERE_H
#define _CLAVIER_BARRIERE_H

#include <string.h>

class Clavier_Barriere {
    private:
        char* code;
        int toucheDetecter;
        int valeurColonne;
        int valeurLigne;
        int getValeurColonne(void);
        int getValeurLigne(void);
        void setCode (int =0,char =' ');
    public:
        Clavier_Barriere();
        ~Clavier_Barriere();
        void conversionTouche(void);
        void detectionTouche(void);
        char* getCode(void);
        int getToucheDetecter(void);
};

#endif
