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
	while(grammaire.getregles().foreach()){
		cout << "recursivite : ";
		if(grammaire.getregles().get().isrecursive()) cout << "vrai";
		else cout << "faux";
		cout << endl;
	}
}



