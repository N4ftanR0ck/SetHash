#ifndef SETLIB_H
#define SETLIB_H

typedef struct item {
	int num;
	char type; // 'i' - int; 'c' - char; 'f' - float;
} item;

typedef struct set {
	int size;
	//int count;
	item* args;
} set;


int hash(void* elem, int size);
set* initEmpty();
set* initArgs(void* elems, int size, char type);
set* addElem(set* s, void* elem, char type);
int getElem(set* s, void* elem);
set* delElem(set* s, int elem);
void printSet(set* s);
set* unification(set* s1, set* s2);
set* intersection(set* s1, set* s2);
set* symdif(set* s1, set* s2);

//every item in set must be unique, also keep in your mind that difficulty of \
algorithms of finding and adding must be doing by constant time.

#endif