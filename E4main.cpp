#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4Regle.h"
 void affichage(Liste<Regle> grammaires);


int main(int argc, char *argv[]){
    Liste<Regle> grammaires = Regle::getgrammaires();


    affichage(grammaires);
cout<<"z";
return 0;
}

 void affichage(Liste<Regle> grammaires)
{
    cout << "--------------- La grammmaire -----------------------------------"<<endl;
    while(grammaires.foreach())
    {cout << grammaires.get() << " "<<endl;}
    cout << "-----------------------------------------------------------------"<<endl;
}