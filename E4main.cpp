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
	cout << grammaire << endl;
	Liste<Regle> regles = grammaire.getregles();
	cout << "r\202cursivit\202 :" << endl;
	while(regles.foreach()){
		cout << "r\212gle " << regles.get().getnom() << " = ";
		if(regles.get().isrecursive()) cout << "vrai";
		else cout << "faux";
		cout << endl;}
}



