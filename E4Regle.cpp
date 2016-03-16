#include <iostream>
using namespace std;
#include <string.h>
#include "E4Regle.h"

Regle::Regle(char *str){
    char *substr = strtok(str,"=|");
    nom = substr;
    while(substr = strtok(NULL,"=|")) valeur.add(substr);
}

ostream& operator<<(ostream &os, const Regle &regle){
    os << "nom : " << regle.nom<<"    " ;
    os << "valeur : " << regle.valeur ;
    return os;
}







const string& Regle::getnom()const{  return nom;}
const Liste<string>& Regle::getvaleur()const{return valeur;}

