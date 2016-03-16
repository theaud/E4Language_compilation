#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../fonctions.h"
#include "grammaire.h"

int main(){
	Liste<Grammaire> grammaires = Grammaire::getgrammaires();
	cout << grammaires << endl;
	while(grammaires.foreach()) cout << grammaires.get().isrecursive() << endl;
	system("PAUSE");}
