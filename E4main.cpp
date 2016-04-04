#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4grammaire.h"
#include "E4regle.h"

int main(){

	char z='e',e='r';
	string a="d"+z;
	// a=""+z+e;
	cout <<a<<endl;

	/*
	Grammaire grammaire = Grammaire::getgrammaire();
	cout << "Grammaire :" << endl;
	cout << grammaire << endl;
	Liste<Regle> regles = grammaire.getregles();
	cout << "r\202cursivit\202 :" << endl;
	while(regles.foreach()){
		cout << "r\212gle " << regles.get().getnom() << " = ";
		if(regles.get().isrecursive()) cout << "vrai";
		else cout << "faux";
		cout << endl;}
	cout << endl;
	grammaire.derecursiver();
	cout << "Grammaire d\202r\202cursiv\202e :" << endl;
	cout << grammaire << endl;
	regles = grammaire.getregles();
	cout << "Calcul des premiers :" << endl;
	while(regles.foreach()){
		cout << "premier(" << regles.get().getnom() << ") = ";
<<<<<<< HEAD
		cout << grammaire.getpremier(regles.get()) << endl;}
	cout << endl;
	cout << "Calcul des suivants :" << endl;
	while(regles.foreach()){
		cout << "suivant(" << regles.get().getnom() << ") = ";
		cout << grammaire.getsuivant(regles.get()) << endl;}
	system("PAUSE");
=======
		cout << grammaire.getpremier(regles.get()) << endl;}*/
>>>>>>> origin/master
}



