#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E04regle.h"

Regle::Regle(char *str){
	char *substr = strtok(str,"=|");
	nom = substr;
	while(substr = strtok(NULL,"=|")) valeur.add(substr);}

Regle::Regle(const string &nom, const Liste<string> &valeur){
	this->nom = nom;
	this->valeur = valeur;}

ostream& operator<<(ostream &os, const Regle &regle){
	os << "Regle [nom = " << regle.nom << ", valeur = " << regle.valeur << "]";
	return os;}

const string& Regle::getnom()const{
	return nom;}

Liste<string>& Regle::getvaleur(){
	return valeur;}

const Liste<string>& Regle::getvaleur()const{
	return valeur;}

bool Regle::isrecursive()const{
	while(valeur.foreach()){
		if(!strncmp(valeur.get().c_str(),nom.c_str(),nom.size())){
			valeur.reset();
			return true;}}
	return false;}
