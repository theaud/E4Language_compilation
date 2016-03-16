#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E4grammaire.h"
#include "E4regle.h"

//fonctions.h
char* lirestr(FILE *file){
	char temp[100];
	fgets(temp,100,file);
	if(char *index = strchr(temp,'\n')) *index = 0;
	char *str = (char*)malloc(sizeof(char)*(strlen(temp)+1));
	strcpy(str,temp);
	return str;}

ostream& operator<<(ostream &os, const Grammaire &grammaire){
	os << grammaire.regles;
	return os;
}

Grammaire Grammaire::getgrammaire(){
	Grammaire grammaire;
	char *str;
	FILE *file = fopen("E4grammaire.txt","r");
	if(fgetc(file)!=EOF){
		fseek(file,-1,SEEK_CUR);
		while(fgetc(file)!=EOF){
			fseek(file,-1,SEEK_CUR);
			str = lirestr(file);
			grammaire.regles.add(str);
			free(str);}
		fclose(file);}
	else cout << "* Erreur : le fichier E4grammaire.txt est absent ou vide ! *" << endl;
	return grammaire;
}

const Liste<Regle>& Grammaire::getregles()const{
	return regles;
}

void Grammaire::derecursiver(){
	//A faire
}