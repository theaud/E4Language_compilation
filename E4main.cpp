#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4grammaire.h"
 void affichage(Liste<Grammaire> grammaires);


int main(int argc, char *argv[]){
    Liste<Grammaire> grammaires = Grammaire::getgrammaires();


    affichage(grammaires);


}

 void affichage(Liste<Grammaire> grammaires)
{

    while(grammaires.foreach())
    {cout << grammaires.get() << " "<<endl;}

}