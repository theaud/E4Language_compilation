#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4grammaire.h"

int main(int argc, char *argv[]){
    Liste<Grammaire> grammaires = Grammaire::getgrammaires();
    cout << grammaires << endl;
    system("PAUSE");}
