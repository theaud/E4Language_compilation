
#include "E4grammaire.h"


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
	for(int i=0; i<regles.size(); i++){
		if(regles.at(i).isrecursive()){
			Liste<string> &valeur = regles.at(i).getvaleur();
			string nom = regles.at(i).getnom();
			string str;
			Liste<string> valeurprime;
			for(int j=0; j<valeur.size(); j++){
				if(strstr(valeur.at(j).c_str(),nom.c_str())){
					str = valeur.remove(j);
					str = str.substr(nom.size(),str.size()-1);
					valeurprime.add(str+nom+"'");}
				else valeur.at(j) = valeur.at(j)+nom+"'";}
			Regle regleprime(nom+"'",valeurprime);
			regles.insert(i+1,regleprime);
			i++;}}
}