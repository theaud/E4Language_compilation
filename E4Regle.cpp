#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4Regle.h"

//fonctions.h
char* lirestr(FILE *file){
    char temp[100];
    fgets(temp,100,file);
    if(char *index = strchr(temp,'\n')) *index = 0;
    char *str = (char*)malloc(sizeof(char)*(strlen(temp)+1));
    strcpy(str,temp);
    return str;}


Regle::Regle(char *str){
    char *substr = strtok(str,"=|");
    nom = substr;
    while(substr = strtok(NULL,"=|")) valeur.add(substr);
}

ostream& operator<<(ostream &os, const Regle &regle){
    os << "nom : " << regle.nom<<"    " ;
    os << "valeur : " << regle.valeur ;
    return os;}



Liste<Regle> Regle::getgrammaires(){
    Liste<Regle> grammaires;
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

const string& Regle::getnom()const{
    return nom;
}

const Liste<string>& Regle::getvaleur()const{
    return valeur;
}

