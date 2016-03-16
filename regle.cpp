#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regle.h"

Regle::Regle(char *str){
	char *substr = strtok(str,"=|");
	nom = substr;
	while(substr = strtok(NULL,"=|")) valeur.add(substr);
}

ostream& operator<<(ostream &os, const Regle &regle){
	os << "nom = " << regle.nom << endl;
	os << "valeur = " << regle.valeur << endl;
	return os;
}

const string& Regle::getnom()const{
	return nom;
}

const Liste<string>& Regle::getvaleur()const{
	return valeur;
}

bool Regle::isrecursive()const{
	while(valeur.foreach()){
		if(strstr(valeur.get().c_str(),nom.c_str())) return true;}
	return false;
}
