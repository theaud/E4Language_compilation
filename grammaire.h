
#ifndef GRAMMAIRE
#define GRAMMAIRE
#include "../liste.h"
#include "regle.h"

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
};

#endif
