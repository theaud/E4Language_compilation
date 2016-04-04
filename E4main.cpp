#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4grammaire.h"
#include "E4regle.h"

int main(){
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
		cout << grammaire.getpremier(regles.get()) << endl;}
}



