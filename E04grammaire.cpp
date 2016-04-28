
#include "E04grammaire.h"

//fonctions.h
char* lirestr(FILE *file){
	char temp[100];
	fgets(temp,100,file);
	if(char *index = strchr(temp,'\n')) *index = 0;
	char *str = (char*)malloc(sizeof(char)*(strlen(temp)+1));
	strcpy(str,temp);
	return str;}

int comparernom(const Regle &regle, const string &nom){
	return regle.getnom().compare(nom);}

ostream& operator<<(ostream &os, const Grammaire &grammaire){
	os << grammaire.regles << endl;
	return os;}

Grammaire Grammaire::getgrammaire(const char *path){
	Grammaire grammaire;
	char *str;
	FILE *file = fopen(path,"r");
	if(fgetc(file)!=EOF){
		fseek(file,-1,SEEK_CUR);
		while(fgetc(file)!=EOF){
			fseek(file,-1,SEEK_CUR);
			str = lirestr(file);
			grammaire.regles.add(str);
			free(str);}
		fclose(file);}
	else cout << "* Erreur : le fichier " << path << " est absent ou vide ! *" << endl;
	return grammaire;}

const Liste<Regle>& Grammaire::getregles()const{
	return regles;}

void Grammaire::derecursiver(){
	while(int i = regles.foreach()){
		if(regles.get().isrecursive()){
			Liste<string> &valeur = regles.get().getvaleur();
			string nom = regles.get().getnom();
			Liste<string> valeurprime;
			while(int j = valeur.foreach()){
				if(!strncmp(valeur.get().c_str(),nom.c_str(),nom.size())){
					string str = valeur.remove(j-1);
					str = str.substr(nom.size(),str.size()-1)+nom+"'";
					valeurprime.add(str);}
				else valeur.get() = valeur.get()+nom+"'";}
			valeurprime.add("#");
			Regle regleprime(nom+"'",valeurprime);
			regles.insert(i,regleprime);}}}

Liste<string> Grammaire::getpremier(const Regle &regle){
	Liste<string> premier;
	const Liste<string> &valeur = regle.getvaleur();
	valeur.start();
	while(valeur.foreach()){
		string str;
		if(valeur.get().size()>1 && valeur.get().at(1)=='\'') str = valeur.get().substr(0,2);
		else str = valeur.get().at(0);
		int n = regles.indexOf(str,comparernom);
		if(n>=0) premier += getpremier(regles.at(n));
		else premier.add(str);}
	return premier;}

Liste<string> Grammaire::getsuivant(const Regle &regle){
	Liste<string> suivant;
	suivant.add("$");
	regles.start();
	while(regles.foreach()){
		const Liste<string> &valeur = regles.get().getvaleur();
		valeur.start();
		while(valeur.foreach()){
			if(char *index = strstr(valeur.get().c_str(),regle.getnom().c_str())){
				index += regle.getnom().size();
				if(*index==0 && regle.getnom()!=regles.get().getnom()){
					suivant += getsuivant(regles.get());}
				if(*index!=0 && *index!='\''){
					string str;
					str += index[0];
					if(index[1]=='\'') str += index[1];
					int n = regles.indexOf(str,comparernom);
					if(n>=0){
						suivant += getpremier(regles.at(n));
						if(suivant.contains("#")){
							suivant.removeAll("#");
							suivant += getsuivant(regles.at(n));}}
					else if(str.size()>0) suivant.add(str);}}}}
	suivant.unique();
	return suivant;}

Liste<string> Grammaire::getterminaux(){
	Liste<string> terminaux;
	while(regles.foreach()){
		const Liste<string> &valeur = regles.get().getvaleur();
		while(valeur.foreach()){
			for(int i=0; i<valeur.get().size(); i++){
				string str;
				str += valeur.get().at(i);
				if(i<valeur.get().size()-1 && valeur.get().at(i+1)=='\''){
					str += valeur.get().at(i+1);
					i++;}
				if(!regles.contains(str,comparernom)) terminaux.add(str);}}}
	terminaux.unique();
	return terminaux;}

void Grammaire::printanalysetab(){
	Liste<string> terminaux = getterminaux();
	terminaux.removeAll("#");
	terminaux.add("$");
	cout << "\t" << terminaux << endl;
	while(regles.foreach()){
		cout << regles.get().getnom() << "\t";
		Liste<string> premier = getpremier(regles.get());
		Liste<string> suivant = getsuivant(regles.get());
		while(terminaux.foreach()){
			if(premier.contains(terminaux.get())) cout << "pr ";
			else if(suivant.contains(terminaux.get())) cout << "su ";
			else cout << "   ";}
		cout << endl;}}
