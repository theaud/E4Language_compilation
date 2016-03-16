
#ifndef REGLE
#define REGLE
#include <string>
#include "E4liste.h"

class Regle{
private :
	string nom;
	Liste<string> valeur;
public :
	Regle(){}
	Regle(char *str);
	~Regle(){}
	friend ostream& operator<<(ostream &os, const Regle &regle);
	const string& getnom()const;
	const Liste<string>& getvaleur()const;
	bool isrecursive()const;
};

#endif
