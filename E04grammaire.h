
#ifndef GRAMMAIRE
#define GRAMMAIRE
#include "E04liste.h"
#include "E04regle.h"

class Grammaire{
private :
	Liste<Regle> regles;
public :
	Grammaire(){}
	~Grammaire(){}
	friend ostream& operator<<(ostream &os, const Grammaire &grammaire);
	static Grammaire getgrammaire();
	const Liste<Regle>& getregles()const;
	void derecursiver();
	Liste<string> getpremier(const Regle &regle);
	Liste<string> getsuivant(const Regle &regle);
    void table_analyseur_predictif();
};

#endif
