
#include "E04grammaire.h"

//fonctions.h
char* lirestr(FILE *file){
	char temp[100];
	fgets(temp,100,file);
	if(char *index = strchr(temp,'\n')) *index = 0;
	char *str = (char*)malloc(sizeof(char)*(strlen(temp)+1));
	strcpy(str,temp);
	return str;
}

ostream& operator<<(ostream &os, const Grammaire &grammaire){
	while(grammaire.regles.foreach()) os << grammaire.regles.get() << endl;
	return os;
}


Grammaire Grammaire::getgrammaire(){
	Grammaire grammaire;
	char *str;
	FILE *file = fopen("E04grammaire.txt","r");
	if(fgetc(file)!=EOF)
    {
		fseek(file,-1,SEEK_CUR);
		while(fgetc(file)!=EOF)
        {
			fseek(file,-1,SEEK_CUR);
			str = lirestr(file);
			grammaire.regles.add(str);
			free(str);
        }
		fclose(file);
    }
	else cout << "* Erreur : le fichier E04grammaire.txt est absent ou vide ! *" << endl;
	return grammaire;
}

const Liste<Regle>& Grammaire::getregles()const{
	return regles;
}

void Grammaire::derecursiver(){
	for(int i=0; i<regles.size(); i++){
		if(regles.at(i).isrecursive()){
			Liste<string> &valeur = regles.at(i).getvaleur();
			string nom = regles.at(i).getnom();
			string str;
			Liste<string> valeurprime;
			for(int j=0; j<valeur.size(); j++){
				if(strstr(valeur.at(j).c_str(),nom.c_str())){
					str = valeur.remove(j);
					j--;
					str = str.substr(nom.size(),str.size()-1)+nom+"'";
					valeurprime.add(str);}
				else valeur.at(j) = valeur.at(j)+nom+"'";}
			valeurprime.add("#");
			Regle regleprime(nom+"'",valeurprime);
			regles.insert(i+1,regleprime);
			i++;}}
}

template <typename Type>
int indexOf(const Liste<Type> &liste, string str){
	for(int i=0; i<liste.size(); i++){
		if(!strcmp(liste.at(i).getnom().c_str(),str.c_str())) return i;}
	return -1;}


template <typename Type>
bool contains(const Liste<Type> &liste, string str){
	for(int i=0; i<liste.size(); i++){
		if(!strcmp(liste.at(i).c_str(),str.c_str())) return true;}
	return false;}


Liste<string> Grammaire::getpremier(const Regle &regle){
	Liste<string> premier;
	const Liste<string> &valeur = regle.getvaleur();
	while(valeur.foreach()){
		string str;
		if(valeur.get().size()>1 && valeur.get().at(1)=='\'') str = valeur.get().substr(0,2);
		else str = valeur.get().at(0);
		int n = indexOf(regles,str);
		if(n>=0) premier += getpremier(regles.at(n));
		else premier.add(str);}
	return premier;}

template <typename Type>
void unique(Liste<Type> &liste){
	for(int i=0; i<liste.size(); i++){
		for(int j=i+1; j<liste.size(); j++){
			if(!strcmp(liste.at(i).c_str(),liste.at(j).c_str())){
				liste.remove(j);
				j--;}}}}

Liste<string> Grammaire::getsuivant(const Regle &regle){
	Liste<string> suivant;
	suivant.add("$");
	for(int i=0; i<regles.size(); i++){
		Liste<string> valeur = regles.at(i).getvaleur();
		for(int j=0; j<valeur.size(); j++){
			if(char *index = strstr(valeur.at(j).c_str(),regle.getnom().c_str())){
				index += regle.getnom().size();
				if(*index==0 && strcmp(regle.getnom().c_str(),regles.at(i).getnom().c_str())){
					suivant += getsuivant(regles.at(i));}
				if(*index!=0 && *index!='\''){
					string str;
					str += index[0];
					if(index[1]=='\'') str += index[1];
					int n = indexOf(regles,str);
					if(n>=0){
						suivant += getpremier(regles.at(n));
						bool test=false;
						for(int k=0; k<suivant.size(); k++){
							if(!strcmp(suivant.at(k).c_str(),"#")){
								suivant.remove(k);
								k--;
								test = true;}}
						if(test) suivant += getsuivant(regles.at(n));}
					else if(str.size()>0) suivant.add(str);}}}}
	unique(suivant);
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
				if(indexOf(regles,str)<0) terminaux.add(str);}}}
	unique(terminaux);
	return terminaux;
}

void Grammaire::print_table_analyseur(){
	Liste<string> terminaux = getterminaux();
	for(int i=0; i<terminaux.size(); i++){
		if(!strcmp(terminaux.at(i).c_str(),"#")){
			terminaux.remove(i);
			i--;}}
	terminaux.add("$");
	cout << "\t" << terminaux << endl;
	while(regles.foreach()){
		cout << regles.get().getnom() << "\t";
		Liste<string> premier = getpremier(regles.get());
		Liste<string> suivant = getsuivant(regles.get());
		while(terminaux.foreach()){
			if(contains(premier,terminaux.get())) cout << "pr ";
			else if(contains(suivant,terminaux.get())) cout << "su ";
			else cout << "   ";}
		cout << endl;}
}