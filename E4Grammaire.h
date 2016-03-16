
#ifndef GRAMMAIRE
#define GRAMMAIRE
#include <string>
#include "E4liste.h"

class Grammaire{
private :
    string nom;
    Liste<string> valeur;
public :
    Grammaire(){}
    Grammaire(char *str);
    ~Grammaire(){}
    friend ostream& operator<<(ostream &os, const Grammaire &grammaire);
    static Liste<Grammaire> getgrammaires();
    const string& getnom()const;
    const Liste<string>& getvaleur()const;




};

#endif
