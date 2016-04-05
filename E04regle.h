
#ifndef REGLE
#define REGLE
#include <string>
#include "E04liste.h"

class Regle{
private :
	string nom;
	Liste<string> valeur;
public :
	Regle(){}
	Regle(char *str);
	Regle(const string &nom, const Liste<string> &valeur);
	~Regle(){}
	friend ostream& operator<<(ostream &os, const Regle &regle);
	const string& getnom()const;
	Liste<string>& getvaleur();
	const Liste<string>& getvaleur()const;
	bool isrecursive()const;
};

#endif
