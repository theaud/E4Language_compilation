//liste.h par Baptiste Thémine

#ifndef LISTE
#define LISTE

#include <iostream>
using namespace std;
#include <stdexcept>
#include <typeinfo>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __cplusplus >= 201103L
#include <initializer_list>
#define ALLOW_INITIALIZER_LIST
#endif

#define istypesimple(x) (typeid(x)==typeid(bool) \
					|| typeid(x)==typeid(char) || typeid(x)==typeid(signed char) || typeid(x)==typeid(unsigned char) || typeid(x)==typeid(wchar_t) \
					|| typeid(x)==typeid(int) || typeid(x)==typeid(short int) || typeid(x)==typeid(long int) || typeid(x)==typeid(long long int) \
					|| typeid(x)==typeid(unsigned int) || typeid(x)==typeid(unsigned short int) || typeid(x)==typeid(unsigned long int) || typeid(x)==typeid(unsigned long long int) \
					|| typeid(x)==typeid(float) || typeid(x)==typeid(double) || typeid(x)==typeid(long double) \
					|| typeid(x)==typeid(string))

/**
	Classe Liste
	Création de liste pour n'importe quel type de variable.
	Combine les avantages des objects std::vector, std::list, et std::map.
	Consultez listehelp.html pour des explications détaillés sur chaque fonction.
**/

template <typename Type>
class Liste{
private :
	//Liste chaînée
	typedef struct LinkedList{
		Type data;
		char *key;
		struct LinkedList *next;
	}LinkedList;
	LinkedList *liste;
	int listsize;
	//Variables foreach
	mutable LinkedList *iterator;
	mutable int index;
	
	//Fonction de copie de chaîne de caractères
	char* copier(const char *str){
		char *strbis;
		if(str){
			strbis = (char*)malloc(sizeof(char)*(strlen(str)+1));
			strcpy(strbis,str);}
		else strbis = NULL;
		return strbis;}
	
	//Fonctions de liste chaînée
	LinkedList* parcourir(LinkedList *maillon)const{
		if(maillon->next==NULL) return maillon;
		else return parcourir(maillon->next);}
	
	LinkedList* parcourir(LinkedList *maillon, int n)const{
		if(maillon->next==NULL || n<=0) return maillon;
		else return parcourir(maillon->next,n-1);}
	
	LinkedList* creer(const char *key, const Type &val){
		LinkedList *maillon = new LinkedList();
		maillon->data = val;
		maillon->key = copier(key);
		maillon->next = NULL;
		return maillon;}
	
	LinkedList* ajouter(LinkedList *&maillon1, LinkedList *maillon2){
		if(maillon1) parcourir(maillon1)->next = maillon2;
		else maillon1 = maillon2;
		return maillon2;}
	
	void inserer(LinkedList *&maillon1, LinkedList *maillon2){
		LinkedList *temp = maillon1;
		maillon1 = maillon2;
		maillon1->next = temp;}
	
	void liberer(LinkedList *maillon){
		if(maillon){
			liberer(maillon->next);
			free(maillon->key);
			delete maillon;}}

public :
	//Constructeurs & destructeur
	Liste():liste(NULL),listsize(0),iterator(NULL),index(0){}
	
	Liste(const Liste<Type> &liste){
		this->liste = NULL;
		listsize = 0;
		iterator = NULL;
		index = 0;
		concat(liste);}
	
	#ifdef ALLOW_INITIALIZER_LIST
	Liste(const initializer_list<Type> &args){
		liste = NULL;
		listsize = 0;
		iterator = NULL;
		index = 0;
		concat(args);}
	#endif
	
	~Liste(){
		liberer(liste);
		liste = NULL;
		listsize = 0;
		iterator = NULL;
		index = 0;}
	
	//Opérateurs
	Liste& operator=(const Liste<Type> &liste){
		this->~Liste();
		concat(liste);
		return *this;}
	
	#ifdef ALLOW_INITIALIZER_LIST
	Liste& operator=(const initializer_list<Type> &args){
		this->~Liste();
		concat(args);
		return *this;}
	#endif
	
	friend Liste operator+(const Liste<Type> &liste1, const Liste<Type> &liste2){
		Liste listebis = liste1;
		listebis.concat(liste2);
		return listebis;}
	
	Liste& operator+=(const Liste<Type> &liste){
		concat(liste);
		return *this;}
	
	#ifdef ALLOW_INITIALIZER_LIST
	Liste& operator+=(const initializer_list<Type> &args){
		concat(args);
		return *this;}
	#endif
	
	friend bool operator==(const Liste<Type> &liste1, const Liste<Type> &liste2){
		if(liste1.size()!=liste2.size()) return false;
		while(liste1.foreach() && liste2.foreach()){
			if(!(liste1.get()==liste2.get())){
				liste1.reset();
				liste2.reset();
				return false;}}
		liste1.reset();
		liste2.reset();
		return true;}
	
	friend bool operator!=(const Liste<Type> &liste1, const Liste<Type> &liste2){
		if(liste1.size()!=liste2.size()) return true;
		while(liste1.foreach() && liste2.foreach()){
			if(!(liste1.get()==liste2.get())){
				liste1.reset();
				liste2.reset();
				return true;}}
		liste1.reset();
		liste2.reset();
		return false;}
	
	friend ostream& operator<<(ostream &os, const Liste<Type> &liste){
		if(liste.size()>0){
			if(istypesimple(liste.front())){
				os << "[";
				while(int i = liste.foreach()){
					os << liste.get();
					if(i<liste.size()) os << ", ";}
				os << "]";}
			else{
				os << "----------------------------------------" << endl << endl;
				while(liste.foreach()){
					os << liste.get() << endl;
					os << "----------------------------------------" << endl << endl;}}}
		return os;}
	
	Type& operator[](const char *key){
		if(key==NULL) throw runtime_error("Error in called funtion 'Type& Liste::operator[](const char *key)' : Parameter key is NULL.");
		LinkedList *maillon = liste;
		while(maillon){
			if(maillon->key && !strcmp(maillon->key,key)) return maillon->data;
			maillon = maillon->next;}
		listsize++;
		return ajouter(liste,creer(key,Type()))->data;}
	
	const Type& operator[](const char *key)const{
		if(key==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::operator[](const char *key) const' : Parameter key is NULL.");
		LinkedList *maillon = liste;
		while(maillon){
			if(maillon->key && !strcmp(maillon->key,key)) return maillon->data;
			maillon = maillon->next;}
		throw out_of_range("Error in called funtion 'const Type& Liste::operator[](const char *key) const' : Unable to access element with the specified key. \
Try to use a non const list to create a new element with the specified key.");}
	
	//Accesseurs
	Type& front(){
		if(liste==NULL) throw runtime_error("Error in called funtion 'Type& Liste::front()' : List is empty.");
		return liste->data;}
	
	const Type& front()const{
		if(liste==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::front() const' : List is empty.");
		return liste->data;}
	
	Type& back(){
		if(liste==NULL) throw runtime_error("Error in called funtion 'Type& Liste::back()' : List is empty.");
		return parcourir(liste)->data;}
	
	const Type& back()const{
		if(liste==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::back() const' : List is empty.");
		return parcourir(liste)->data;}
	
	Type& at(int n){
		if(n<0 || n>=listsize) throw out_of_range("Error in called funtion 'Type& Liste::at(int n)' : Index out of range.");
		return parcourir(liste,n)->data;}
	
	const Type& at(int n)const{
		if(n<0 || n>=listsize) throw out_of_range("Error in called funtion 'const Type& Liste::at(int n) const' : Index out of range.");
		return parcourir(liste,n)->data;}
	
	//Modificateurs
	void add(const Type &val){
		ajouter(liste,creer(NULL,val));
		listsize++;}
	
	void push_front(const Type &val){
		inserer(liste,creer(NULL,val));
		listsize++;}
	
	void push_back(const Type &val){
		ajouter(liste,creer(NULL,val));
		listsize++;}
	
	void insert(int n, const Type &val){
		if(n<0 || n>listsize) throw out_of_range("Error in called funtion 'void Liste::insert(int n,const Type &val)' : Index out of range.");
		LinkedList *maillon = creer(NULL,val);
		if(n==0 || liste==NULL) inserer(liste,maillon);
		else inserer(parcourir(liste,n-1)->next,maillon);
		listsize++;}
	
	Type pop_front(){
		if(liste==NULL) throw runtime_error("Error in called funtion 'Type Liste::pop_front()' : List is empty.");
		return remove(0);}
	
	Type pop_back(){
		if(liste==NULL) throw runtime_error("Error in called funtion 'Type Liste::pop_back()' : List is empty.");
		return remove(listsize-1);}
	
	Type remove(int n){
		if(n<0 || n>=listsize) throw out_of_range("Error in called funtion 'Type Liste::remove(int n)' : Index out of range.");
		LinkedList *temp;
		if(n==0 || liste->next==NULL){
			temp = liste;
			liste = liste->next;}
		else{
			LinkedList *maillon = parcourir(liste,n-1);
			temp = maillon->next;
			maillon->next = maillon->next->next;}
		if(iterator==temp) iterator = iterator->next;
		listsize--;
		Type val = temp->data;
		free(temp->key);
		delete temp;
		return val;}
	
	Type remove(const char *key){
		if(liste==NULL) throw runtime_error("Error in called funtion 'Type Liste::remove(const char *key)' : List is empty.");
		if(key==NULL) throw runtime_error("Error in called funtion 'Type Liste::remove(const char *key)' : Parameter key is NULL.");
		LinkedList *maillon = liste, *temp = NULL;
		if(liste->next==NULL || !strcmp(liste->key,key)){
			temp = liste;
			liste = liste->next;}
		else{
			while(maillon->next && temp==NULL){
				if(maillon->next->key && !strcmp(maillon->next->key,key)) temp = maillon->next;
				else maillon = maillon->next;}
			if(temp==NULL) throw out_of_range("Error in called funtion 'Type Liste::remove(const char *key)' : Unable to access element with the specified key.");
			maillon->next = maillon->next->next;}
		if(iterator==temp) iterator = iterator->next;
		listsize--;
		Type val = temp->data;
		free(temp->key);
		delete temp;
		return val;}
	
	void clear(){
		this->~Liste();}
	
	//Opérations sur les listes
	void concat(const Liste<Type> &liste){
		while(liste.foreach()){
			if(liste.iterator->key) (*this)[liste.iterator->key] = liste.get();
			else add(liste.get());}}
	
	#ifdef ALLOW_INITIALIZER_LIST
	void concat(const initializer_list<Type> &args){
		for(auto it=args.begin(); it!=args.end(); it++) add(*it);}
	#endif
	
	void unique(){
		for(int i=0; i<listsize; i++){
			for(int j=i+1; j<listsize; j++){
				if(at(i)==at(j)){
					remove(j);
					j--;}}}}
	
	void sort(){
		if(liste){
			LinkedList *next = liste->next;
			LinkedList *sort = liste;
			sort->next = NULL;
			liste = next;
			while(liste){
				next = liste->next;
				bool test=true;
				if(liste->data<sort->data){
					inserer(sort,liste);
					test = false;}
				for(LinkedList *maillon = sort; test; maillon = maillon->next){
					if(maillon->next==NULL || !(liste->data<maillon->data) && liste->data<maillon->next->data){
						inserer(maillon->next,liste);
						test = false;}}
				liste = next;}
			liste = sort;}}
	
	void rsort(){
		if(liste){
			LinkedList *next = liste->next;
			LinkedList *sort = liste;
			sort->next = NULL;
			liste = next;
			while(liste){
				next = liste->next;
				bool test=true;
				if(!(liste->data<sort->data)){
					inserer(sort,liste);
					test = false;}
				for(LinkedList *maillon = sort; test; maillon = maillon->next){
					if(maillon->next==NULL || liste->data<maillon->data && !(liste->data<maillon->next->data)){
						inserer(maillon->next,liste);
						test = false;}}
				liste = next;}
			liste = sort;}}
	
	//Fonctions de capacité & recherche
	bool isempty()const{
		return (liste==NULL);}
	
	int size()const{
		return listsize;}
	
	bool contains(const Type &val)const{
		while(foreach()){
			if(get()==val){
				reset();
				return true;}}
		reset();
		return false;}
	
	bool keyexists(const char *key)const{
		if(key==NULL) return false;
		LinkedList *maillon = liste;
		while(maillon){
			if(maillon->key && !strcmp(maillon->key,key)) return true;
			maillon = maillon->next;}
		return false;}
		
	//Fonctions foreach
	int foreach()const{
		if(iterator) iterator = iterator->next;
		else iterator = liste;
		if(iterator) index++;
		else index = 0;
		return index;}
	
	Type& get(){
		if(iterator==NULL) throw runtime_error("Error in called funtion 'Type& Liste::get()' : Trying to access element outside foreach() loop.");
		return iterator->data;}
	
	const Type& get()const{
		if(iterator==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::get() const' : Trying to access element outside foreach() loop.");
		return iterator->data;}
	
	void reset()const{
		iterator = NULL;
		index = 0;}
};

#endif
