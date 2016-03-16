
#ifndef GRAMMAIRE
#define GRAMMAIRE
#include "E4liste.h"
#include "E4Regle.h"

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
