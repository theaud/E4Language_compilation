#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammaire.h"
#include "regle.h"

//fonctions.h
char* lirestr(FILE*);

ostream& operator<<(ostream &os, const Grammaire &grammaire){
	os << grammaire.regles;
	return os;
}

Grammaire Grammaire::getgrammaire(){
	Grammaire grammaire;
	char *str;
	FILE *file = fopen("grammaire.txt","r");
	if(fgetc(file)!=EOF){
		fseek(file,-1,SEEK_CUR);
		while(fgetc(file)!=EOF){
			fseek(file,-1,SEEK_CUR);
			str = lirestr(file);
			grammaire.regles.add(str);
			free(str);}
		fclose(file);}
	else cout << "* Erreur : le fichier grammaire.txt est absent ou vide ! *" << endl;
	return grammaire;
}

const Liste<Regle>& Grammaire::getregles()const{
	return regles;
}

void Grammaire::derecursiver(){
	//A faire
}