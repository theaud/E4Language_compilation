
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
	FILE *file = fopen("E4grammaire.txt","r");
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
int indexOf(const Liste<Type> &liste, string nom){
	for(int i=0; i<liste.size(); i++){
		if(!strcmp(liste.at(i).getnom().c_str(),nom.c_str())){
			liste.reset();
			return i;}}
	return -1;}

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

Liste<string> Grammaire::getsuivant(const Regle &regle){
	Liste<string> suivant;
	suivant.add("$");
	while(regles.foreach()){
		Liste<string> valeur = regles.get().getvaleur();
		while(valeur.foreach()){
			string str;
			if(char *index = strstr(valeur.get().c_str(),regle.getnom().c_str())){
				index += regle.getnom().size();
				if(*index==0);
				else if(*index!='\''){
					str += index[0];
					if(index[1]=='\'') str += index[1];}}
			int n = indexOf(regles,str);
			if(n>=0){
				suivant += getpremier(regles.at(n));
				/* bool test=false; */
				for(int i=0; i<suivant.size(); i++){
					if(!strcmp(suivant.at(i).c_str(),"#")){
						suivant.remove(i);
						i--;
						/* test = true; */}}
				/* if(test) suivant += getsuivant(regles.at(n)); */}
			else if(str.size()>0) suivant.add(str);}
		/* if(suivant.size()==1) suivant += getsuivant(regles.get()); */}
	return suivant;}

void Grammaire::table_analyseur_predictif()
{
/*
 Donnée. Grammaire G
Sortie. Table d’analyse M


Pour tous A->α
    faire
        Pour tous terminal a dans PREMIER(α)
            faire
                 ajouter A α à M[A,a]
            fin

         Si ε est dans PREMIER(α)
            si ε est dans PREMIER(α) et $ est dans SUIVANT(A)
                ajouter A α à M[A,$]
            sinon
                ajouter A α à M[A,b] pour chaque terminal b dans SUIVANT(A)

            fin
         fin

         Si ε est dans PREMIER(α) et $ est dans SUIVANT(A),
            ajouter A α à M[A,$]
        fin
    fin
fin

 ####Faire de chaque entrée non définie de M une erreur.####

 */
    char z='e',e='r';
    string a=""+z+e;

}
