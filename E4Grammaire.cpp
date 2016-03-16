#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4Grammaire.h"

//fonctions.h

char* lirestr(FILE *file){
    char temp[100];
    fgets(temp,100,file);
    if(char *index = strchr(temp,'\n')) *index = 0;
    char *str = (char*)malloc(sizeof(char)*(strlen(temp)+1));
    strcpy(str,temp);
    return str;}

E4Grammaire::E4Grammaire(char *str){
    char *substr = strtok(str,"=|");
    nom = substr;
    while(substr = strtok(NULL,"=|")) valeur.add(substr);
}

ostream& operator<<(ostream &os, const E4Grammaire &grammaire){
    os << "nom = " << grammaire.nom << endl;
   // os << "valeur = " << grammaire.valeur << endl;
    return os;}

void E4Grammaire::afficher()
{

    cout << "nom = " << nom << endl;

    //cout << "valeur = " << valeur << endl;


}

Liste<E4Grammaire> E4Grammaire::getgrammaires(){
    Liste<E4Grammaire> grammaires;
    char *str;
    FILE *file = fopen("E4grammaire.txt","r");
    if(fgetc(file)!=EOF){
        fseek(file,-1,SEEK_CUR);
        while(fgetc(file)!=EOF){
            fseek(file,-1,SEEK_CUR);
            str = lirestr(file);
            grammaires.add(str);
            free(str);}
        fclose(file);}
    else cout << "* Erreur : le fichier E4grammaire.txt est absent ou vide ! *" << endl;
    return grammaires;}

const string& E4Grammaire::getnom()const{
    return nom;
}

const Liste<string>& E4Grammaire::getvaleur()const{
    return valeur;
}
