#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stl_list.h>

#include "E4Grammaire.h"

list<E4Grammaire> getgrammaires();

int main(int argc, char *argv[]){
    Liste<E4Grammaire> grammaires = E4Grammaire::getgrammaires();
   // cout << grammaires << endl;
	system("PAUSE");}

