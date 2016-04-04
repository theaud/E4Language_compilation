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
	cout << "Grammaire :" << endl<<grammaire << endl;

	Liste<Regle> regles = grammaire.getregles();
	cout << "r\202cursivit\202 :" << endl;
	while(regles.foreach())
	{
		cout << "r\212gle " << regles.get().getnom() << " = ";

		if(regles.get().isrecursive())
			cout << "vrai"<< endl;
		else
			cout << "faux"<< endl;
	}

	cout << endl;
	grammaire.derecursiver();
	cout << "Grammaire d\202r\202cursiv\202e :" << endl;
	cout << grammaire << endl;
}



