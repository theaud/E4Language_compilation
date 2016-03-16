
#ifndef GRAMMAIRE
#define GRAMMAIRE
#include <string>
#include "E4liste.h"

class E4Grammaire{
private :
    string nom;
    Liste<string> valeur;
public :
    E4Grammaire(){}
    E4Grammaire(char *str);
    ~E4Grammaire(){}
    friend ostream& operator<<(ostream &os, const E4Grammaire &grammaire);
    static Liste<E4Grammaire> getgrammaires();
    const string& getnom()const;
    const Liste<string>& getvaleur()const;
    void afficher();
};

#endif
