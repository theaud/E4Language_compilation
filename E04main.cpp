#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E04grammaire.h"
#include "E04regle.h"

//fonctions.h
char* saisirstr(){
	char temp[100];
	fgets(temp,100,stdin);
	if(char *index = strchr(temp,'\n')) *index = 0;
	if(strlen(temp)>=99) while(getchar()!='\n');
	char *str = (char*)malloc(sizeof(char)*(strlen(temp)+1));
	strcpy(str,temp);
	return str;}

int main(){
	cout << "Saisissez le nom du fichier de la grammaire :" << endl;
	char *path = saisirstr();
	Grammaire grammaire = Grammaire::getgrammaire(path);
	free(path);
	cout << endl << "Grammaire :" << endl;
	cout << grammaire;
	Liste<Regle> regles = grammaire.getregles();
	cout << "r\202cursivit\202 :" << endl;
	while(regles.foreach()){
		cout << "r\212gle " << regles.get().getnom() << " = ";
		if(regles.get().isrecursive()) cout << "vrai";
		else cout << "faux";
		cout << endl;}
	grammaire.derecursiver();
	cout << endl << "Grammaire d\202r\202cursiv\202e :" << endl;
	cout << grammaire;
	regles = grammaire.getregles();
	cout << "Calcul des premiers :" << endl;
	while(regles.foreach()){
		cout << "premier(" << regles.get().getnom() << ") = ";
		cout << grammaire.getpremier(regles.get()) << endl;}
	cout << endl << "Calcul des suivants :" << endl;
	while(regles.foreach()){
		cout << "suivant(" << regles.get().getnom() << ") = ";
		cout << grammaire.getsuivant(regles.get()) << endl;}
	cout << endl << "Table d'analyse syntaxique :" << endl;
	grammaire.printanalysetab();
	system("PAUSE");}
