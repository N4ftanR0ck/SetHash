#include <stdio.h>
#include <stdlib.h>
#include "setlib.h"

int main() {
	
	//TESTS
	int arr_i[] = {1, 1, 45, 32, 47, 11, -45, 201}; //init int
	set* s_i = initArgs(arr_i, 8, 'i');
	printSet(s_i);
	printf("\n");

	s_i = delElem(s_i, -45); //deleat
	printSet(s_i);
	printf("\n");

	int arr_ñ[] = { 'a', '!', 'b', '3', '-', '+', '+', 'q'}; //init int
	set* s_ñ = initArgs(arr_ñ, 8, 'c');
	printSet(s_ñ);
	printf("\n");

	float arr_f[] = { 1.1, 2,34, 45.0, 32.11, 47.5, 11.0, -45.2, 201.3 }; //init float
	set* s_f = initArgs(arr_f, 8, 'f');
	printSet(s_f);
	printf("\n");

	set* s = unification(s_i, s_f); //union of int and float
	printSet(s);
	printf("\n");

	int arr_i2[] = { 1, 1, 45, 32 }; //extra itn set
	set* s_i2 = initArgs(arr_i2, 4, 'i');
	printSet(s_i2);
	printf("\n");

	set* ss = intersection(s, s_i2); //intersection 
	printSet(ss);

	//set* ss = symdif(s, s_i2); //symdif 
	//printSet(ss);

	return 0;
}