#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../fonctions.h"
#include "grammaire.h"
#include "regle.h"

int main(){
	Grammaire grammaire = Grammaire::getgrammaire();
	cout << grammaire << endl;
	system("PAUSE");}
