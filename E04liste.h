
/**
	Classe Liste par Baptiste Thémine
	
	Création de liste pour n'importe quel type de variable.
	Combine les avantages des objets std::vector, std::list, et std::map.
	Consultez listehelp.html pour des explications détaillés sur chaque fonction.
**/

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

template <typename Type>
class Liste{
private :
	//Liste chaînée
	typedef struct LinkedList{
		Type data;
		char *key;
		struct LinkedList *next;
	}LinkedList;
	LinkedList *head;
	int listsize;
	
	//Variables foreach
	typedef struct Iterator{
		LinkedList *ptr;
		int index;
		struct Iterator *next;
		Iterator():ptr(NULL),index(0),next(NULL){}
	}Iterator;
	mutable Iterator *iterator;
	
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
	
	void supprimer(LinkedList *&maillon){
		LinkedList *next = maillon->next;
		if(iterator->ptr==maillon){
			if(iterator->index<2){
				iterator->ptr = NULL;
				iterator->index = 0;}
			else{
				iterator->ptr = parcourir(head,iterator->index-2);
				iterator->index--;}}
		listsize--;
		free(maillon->key);
		delete maillon;
		maillon = next;}
	
	void liberer(LinkedList *maillon){
		if(maillon){
			liberer(maillon->next);
			free(maillon->key);
			delete maillon;}}
	
	//Fonctions callback
	static int comparer(const Type &val1, const Type &val2){
		if(val1<val2) return -1;
		else if(val2<val1) return 1;
		else return 0;}
	
	void trier(int (*callback)(const Type&,const Type&), int tri){
		if(head){
			LinkedList *next = head->next;
			LinkedList *sort = head;
			sort->next = NULL;
			head = next;
			while(head){
				next = head->next;
				bool test=true;
				if(tri*callback(head->data,sort->data)<0){
					inserer(sort,head);
					test = false;}
				for(LinkedList *maillon = sort; test; maillon = maillon->next){
					if(maillon->next==NULL || tri*callback(head->data,maillon->next->data)<0){
						inserer(maillon->next,head);
						test = false;}}
				head = next;}
			head = sort;}}
	
public :
	//Constructeurs & destructeur
	Liste():head(NULL),listsize(0),iterator(new Iterator()){}
	
	Liste(const Liste<Type> &liste){
		head = NULL;
		listsize = 0;
		iterator = new Iterator();
		concat(liste);}
	
	#ifdef ALLOW_INITIALIZER_LIST
	Liste(const initializer_list<Type> &args){
		head = NULL;
		listsize = 0;
		iterator = new Iterator();
		concat(args);}
	#endif
	
	~Liste(){
		liberer(head);
		head = NULL;
		listsize = 0;
		iterator = new Iterator();}
	
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
		LinkedList *maillon1 = liste1.head;
		LinkedList *maillon2 = liste2.head;
		while(maillon1 && maillon2){
			if(!(maillon1->data==maillon2->data)){
				return false;}
			maillon1 = maillon1->next;
			maillon2 = maillon2->next;}
		return true;}
	
	friend bool operator!=(const Liste<Type> &liste1, const Liste<Type> &liste2){
		if(liste1.size()!=liste2.size()) return true;
		LinkedList *maillon1 = liste1.head;
		LinkedList *maillon2 = liste2.head;
		while(maillon1 && maillon2){
			if(!(maillon1->data==maillon2->data)){
				return true;}
			maillon1 = maillon1->next;
			maillon2 = maillon2->next;}
		return false;}
	
	friend ostream& operator<<(ostream &os, const Liste<Type> &liste){
		if(liste.size()>0){
			LinkedList *maillon;
			if(istypesimple(liste.front())){
				os << "[";
				for(maillon = liste.head; maillon; maillon = maillon->next){
					os << maillon->data;
					if(maillon->next) os << ", ";}
				os << "]";}
			else{
				for(maillon = liste.head; maillon; maillon = maillon->next) os << maillon->data << endl;}}
		return os;}
	
	Type& operator[](const char *key){
		if(key==NULL) throw runtime_error("Error in called funtion 'Type& Liste::operator[](const char *key)' : Parameter key is NULL.");
		LinkedList *maillon = head;
		while(maillon){
			if(maillon->key && !strcmp(maillon->key,key)) return maillon->data;
			maillon = maillon->next;}
		listsize++;
		return ajouter(head,creer(key,Type()))->data;}
	
	const Type& operator[](const char *key)const{
		if(key==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::operator[](const char *key) const' : Parameter key is NULL.");
		LinkedList *maillon = head;
		while(maillon){
			if(maillon->key && !strcmp(maillon->key,key)) return maillon->data;
			maillon = maillon->next;}
		throw out_of_range("Error in called funtion 'const Type& Liste::operator[](const char *key) const' : Unable to access element with the specified key. \
Try to use a non const list to create a new element with the specified key.");}
	
	//Accesseurs
	Type& front(){
		if(head==NULL) throw runtime_error("Error in called funtion 'Type& Liste::front()' : List is empty.");
		return head->data;}
	
	const Type& front()const{
		if(head==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::front() const' : List is empty.");
		return head->data;}
	
	Type& back(){
		if(head==NULL) throw runtime_error("Error in called funtion 'Type& Liste::back()' : List is empty.");
		return parcourir(head)->data;}
	
	const Type& back()const{
		if(head==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::back() const' : List is empty.");
		return parcourir(head)->data;}
	
	Type& at(int n){
		if(n<0 || n>=listsize) throw out_of_range("Error in called funtion 'Type& Liste::at(int n)' : Index out of range.");
		return parcourir(head,n)->data;}
	
	const Type& at(int n)const{
		if(n<0 || n>=listsize) throw out_of_range("Error in called funtion 'const Type& Liste::at(int n) const' : Index out of range.");
		return parcourir(head,n)->data;}
	
	//Modificateurs
	void add(const Type &val){
		ajouter(head,creer(NULL,val));
		listsize++;}
	
	void push_front(const Type &val){
		inserer(head,creer(NULL,val));
		listsize++;}
	
	void push_back(const Type &val){
		ajouter(head,creer(NULL,val));
		listsize++;}
	
	void insert(int n, const Type &val){
		if(n<0 || n>listsize) throw out_of_range("Error in called funtion 'void Liste::insert(int n,const Type &val)' : Index out of range.");
		LinkedList *maillon = creer(NULL,val);
		if(n==0 || head==NULL) inserer(head,maillon);
		else inserer(parcourir(head,n-1)->next,maillon);
		listsize++;}
	
	Type pop_front(){
		if(head==NULL) throw runtime_error("Error in called funtion 'Type Liste::pop_front()' : List is empty.");
		return remove(0);}
	
	Type pop_back(){
		if(head==NULL) throw runtime_error("Error in called funtion 'Type Liste::pop_back()' : List is empty.");
		return remove(listsize-1);}
	
	Type remove(int n){
		if(n<0 || n>=listsize) throw out_of_range("Error in called funtion 'Type Liste::remove(int n)' : Index out of range.");
		Type val;
		if(n==0){
			val = head->data;
			supprimer(head);}
		else{
			LinkedList *maillon = parcourir(head,n-1);
			val = maillon->next->data;
			supprimer(maillon->next);}
		return val;}
	
	Type remove(const char *key){
		if(head==NULL) throw runtime_error("Error in called funtion 'Type Liste::remove(const char *key)' : List is empty.");
		if(key==NULL) throw runtime_error("Error in called funtion 'Type Liste::remove(const char *key)' : Parameter key is NULL.");
		Type val;
		if(!strcmp(head->key,key)){
			val = head->data;
			supprimer(head);}
		else{
			LinkedList *maillon = head, *temp = NULL;
			while(maillon->next && temp==NULL){
				if(maillon->next->key && !strcmp(maillon->next->key,key)) temp = maillon->next;
				else maillon = maillon->next;}
			if(temp==NULL) throw out_of_range("Error in called funtion 'Type Liste::remove(const char *key)' : Unable to access element with the specified key.");
			val = maillon->next->data;
			supprimer(maillon->next);}
		return val;}
	
	template <typename Value>
	void removeAll(const Value &val){
		while(head && head->data==val) supprimer(head);
		if(head && head->next){
			LinkedList *maillon = head;
			while(maillon->next){
				if(maillon->next->data==val) supprimer(maillon->next);
				else maillon = maillon->next;}}}
	
	template <typename Value>
	void removeAll(const Value &val, bool (*callback)(const Type&,const Value&)){
		while(head && head->data==val) supprimer(head);
		if(head && callback(head->data,val)){
			LinkedList *maillon = head;
			while(maillon->next){
				if(callback(maillon->next->data,val)) supprimer(maillon->next);
				else maillon = maillon->next;}}}
	
	template <typename Value>
	void removeAll(const Value &val, int (*callback)(const Type&,const Value&)){
		while(head && head->data==val) supprimer(head);
		if(head && callback(head->data,val)==0){
			LinkedList *maillon = head;
			while(maillon->next){
				if(callback(maillon->next->data,val)==0) supprimer(maillon->next);
				else maillon = maillon->next;}}}
	
	void clear(){
		this->~Liste();}
	
	//Opérations sur les listes
	void concat(const Liste<Type> &liste){
		for(LinkedList *maillon = liste.head; maillon; maillon = maillon->next){
			if(maillon->key) (*this)[maillon->key] = maillon->data;
			else add(maillon->data);}}
	
	#ifdef ALLOW_INITIALIZER_LIST
	void concat(const initializer_list<Type> &args){
		for(auto it=args.begin(); it!=args.end(); it++) add(*it);}
	#endif
	
	void unique(){
		LinkedList *maillon1, *maillon2;
		for(maillon1 = head; maillon1; maillon1 = maillon1->next){
			maillon2 = maillon1;
			while(maillon2->next){
				if(maillon1->data==maillon2->next->data) supprimer(maillon2->next);
				else maillon2 = maillon2->next;}}}
	
	void unique(bool (*callback)(const Type&,const Type&)){
		LinkedList *maillon1, *maillon2;
		for(maillon1 = head; maillon1; maillon1 = maillon1->next){
			maillon2 = maillon1;
			while(maillon2->next){
				if(callback(maillon1->data,maillon2->next->data)) supprimer(maillon2->next);
				else maillon2 = maillon2->next;}}}
	
	void unique(int (*callback)(const Type&,const Type&)){
		LinkedList *maillon1, *maillon2;
		for(maillon1 = head; maillon1; maillon1 = maillon1->next){
			maillon2 = maillon1;
			while(maillon2->next){
				if(callback(maillon1->data,maillon2->next->data)==0) supprimer(maillon2->next);
				else maillon2 = maillon2->next;}}}
	
	void sort(){
		trier(comparer,1);}
	
	void sort(int (*callback)(const Type&,const Type&)){
		trier(callback,1);}
	
	void rsort(){
		trier(comparer,-1);}
	
	void rsort(int (*callback)(const Type&,const Type&)){
		trier(callback,-1);}
	
	//Fonctions de capacité & recherche
	bool isempty()const{
		return (head==NULL);}
	
	int size()const{
		return listsize;}
	
	template <typename Value>
	bool contains(const Value &val)const{
		for(LinkedList *maillon = head; maillon; maillon = maillon->next){
			if(maillon->data==val) return true;}
		return false;}
	
	template <typename Value>
	bool contains(const Value &val, bool (*callback)(const Type&,const Value&))const{
		for(LinkedList *maillon = head; maillon; maillon = maillon->next){
			if(callback(maillon->data,val)) return true;}
		return false;}
	
	template <typename Value>
	bool contains(const Value &val, int (*callback)(const Type&,const Value&))const{
		for(LinkedList *maillon = head; maillon; maillon = maillon->next){
			if(callback(maillon->data,val)==0) return true;}
		return false;}
	
	template <typename Value>
	int indexOf(const Value &val)const{
		LinkedList *maillon = head;
		for(int i=0; i<listsize; i++){
			if(maillon->data==val) return i;
			maillon = maillon->next;}
		return -1;}
	
	template <typename Value>
	int indexOf(const Value &val, bool (*callback)(const Type&,const Value&))const{
		LinkedList *maillon = head;
		for(int i=0; i<listsize; i++){
			if(callback(maillon->data,val)) return i;
			maillon = maillon->next;}
		return -1;}
	
	template <typename Value>
	int indexOf(const Value &val, int (*callback)(const Type&,const Value&))const{
		LinkedList *maillon = head;
		for(int i=0; i<listsize; i++){
			if(callback(maillon->data,val)==0) return i;
			maillon = maillon->next;}
		return -1;}
	
	bool keyexists(const char *key)const{
		if(key==NULL) return false;
		LinkedList *maillon = head;
		while(maillon){
			if(maillon->key && !strcmp(maillon->key,key)) return true;
			maillon = maillon->next;}
		return false;}
	
	//Fonctions foreach
	int foreach()const{
		if(iterator->ptr) iterator->ptr = iterator->ptr->next;
		else iterator->ptr = head;
		if(iterator->ptr) iterator->index++;
		else if(iterator->next){
			reset();
			return 0;}
		else iterator->index = 0;
		return iterator->index;}
	
	Type& get(){
		if(iterator->ptr==NULL) throw runtime_error("Error in called funtion 'Type& Liste::get()' : Trying to access element outside foreach() loop.");
		return iterator->ptr->data;}
	
	const Type& get()const{
		if(iterator->ptr==NULL) throw runtime_error("Error in called funtion 'const Type& Liste::get() const' : Trying to access element outside foreach() loop.");
		return iterator->ptr->data;}
	
	void start()const{
		Iterator *newit = new Iterator();
		newit->next = iterator;
		iterator = newit;}
	
	void reset()const{
		if(iterator && !iterator->ptr && iterator->next){
			Iterator *temp = iterator;
			iterator = iterator->next;
			delete temp;}
		else{
			iterator->ptr = NULL;
			iterator->index = 0;}}
};

#endif
