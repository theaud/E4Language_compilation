
#ifndef GRAMMAIRE
#define GRAMMAIRE
#include "E4liste.h"
#include "E4regle.h"

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
    void table_analyseur_predictif();//meilleur nom a trouver

};

#endif
