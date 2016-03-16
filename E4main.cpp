#include <iostream>
#include "E4Regle.h"
#include "E4grammaire.h"

using namespace std;



int main(int argc, char *argv[]){
    Grammaire grammaire = Grammaire::getgrammaire();
    cout << "test" << endl;
    cout << grammaire;
}
