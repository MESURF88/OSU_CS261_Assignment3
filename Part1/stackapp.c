/* CS261- Assignment 2 - stack app*/
/*Name: Kevin Hill
 * Date: 07/18/2019
 * Solution description: prints if expression is balanced or not. Assumes that null is balanced
 Input: User inputs sequence of characters
 Output: Determines whether input is balanced or not.
 */
/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArrA(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v != 0);
	v->data = (TYPE *)malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.
*/
DynArr* newDynArrA(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof(DynArr));
	assert(r != 0);
	initDynArrA(r, cap);
	return r;
}

/* Deallocate data array in dynamic array.

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArrA(DynArr *v)
{
	if (v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure.

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArrA(DynArr *v)
{
	freeDynArrA(v);
	free(v);
}



/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArrA(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	pre:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArrA(DynArr *v, TYPE val)
{
	/* Check to see if a resize is necessary */
	if (v->size >= v->capacity) {
		_setCapacityDynArrA(v, 2 * v->capacity);
	}
	v->data[v->size] = val;
	v->size++;


}

//resizes array
void _setCapacityDynArrA(DynArr *v, int newCap)
{

	TYPE *temp = malloc(sizeof(TYPE)* newCap);
	assert(temp != 0);

	int i;
	for (i = 0; i < v->size; i++) {
		temp[i] = v->data[i];
	}

	free(v->data);
	v->data = temp;
	temp = 0;
	v->capacity = newCap;


}

/*	Get an element from the dynamic array from a specified position

	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArrA(DynArr *v, int pos)
{
	assert(v->data[pos] != 0);
	return v->data[pos];
}

/*	Returns the element at the top of the stack

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArrA(DynArr *v)
{
	assert(!isEmptyDynArrA(v));
	return getDynArrA(v, sizeDynArrA(v) - 1);
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArrA(DynArr *v, int idx)
{
	assert(v->data[idx != 0]);
	for (int i = idx; i < v->size - 1; i++) {
		v->data[i] = v->data[i + 1];
	}

	//after loop/if last index reduce size by one
	v->size--;
}



/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArrA(DynArr *v)
{
	return sizeDynArrA(v) > 0 ? 0 : 1;
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArrA(DynArr *v, TYPE val)
{
	addDynArrA(v, val);
}

/* Removes the element on top of the stack

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArrA(DynArr *v)
{
	assert(!isEmptyDynArrA(v));
	removeAtDynArrA(v, sizeDynArrA(v) - 1);
}

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	setup char variable to hold user input
	post:	stack has no dangling pointers and returns a value
*/
int isBalanced(char* s)
{
	int i = 0;
	int balance_pair = 0;

	/* Declare a stack of 10 characters initially */
	DynArr *v;
	v = newDynArrA(10);

	//request user for input
	printf("Enter a string of characters with parentheses, press enter afterwards: ");
	scanf("%[^\n]s", s);


	//loop through expression using nextChar
	while (nextChar(s)!='\0')
	{
		
		//If starting parentheses push
		if (s[i] == '{' || s[i] == '(' || s[i] == '[')
			pushDynArrA(v, s[i]);

		//If ending parentheses then check with pop
		if (s[i] == '}' || s[i] == ')' || s[i] == ']')
		{

			//If ending parentheses with no pair, false and unbalanced
			if (v->size == 0) {
				return 0;
			}
			//Else check for pair by popping off opening parantheses and chacking with current character in stack
			else {
				balance_pair = 0;
				if (topDynArrA(v) == '(' && s[i] == ')') {
					balance_pair = 1;
				}
				else if (topDynArrA(v) == '{' && s[i] == '}') {
					balance_pair = 1;
				}
				else if (topDynArrA(v) == '[' && s[i] == ']') {
					balance_pair = 1;
				}
				else {
					return 0;
				}
				if (balance_pair = 1) {
					popDynArrA(v);
				}
			}
		}
		i++;
	}
	
	//If no opening parantheses elements left in stack true
	if (v->size == 0) {
		deleteDynArrA(v);
		//free stack
		return 1;
	}
	else {
		deleteDynArrA(v);
		//free stack
		return 0;

	}
}

int main(int argc, char* argv[]){

	
	//char* s=argv[1];	
	int res;

	char s[100];
	
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res) {
		printf("The string %s is balanced\n", s);
	}
	else {
		printf("The string %s is not balanced\n", s);
	}
	
	return 0;
}

