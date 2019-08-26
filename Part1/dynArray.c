/* testDynArray.c
 * This file is used for testing the dynamicArray.c file. 
 * This test suite is by no means complete or thorough.
 * More testing is needed on your own.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


void assertTrue(int predicate, char *message) 
{
	printf("%s: ", message);
	if (predicate)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}

struct DynArr
{
	TYPE *data;    /* pointer to the data array */
	int size;        /* Number of elements in the array */
	int capacity;    /* capacity of the array */
};

void initDynArr(struct DynArr *v, int capacity)
{
	v->data = malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);

	v->size = 0;
	v->capacity = capacity;

}
void freeDynArr(DynArr *v)
{
	if (v->data != 0)
	{
		free(v->data);     /* free the space on the heap */
		v->data = 0;       /* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = malloc(sizeof(DynArr));
	assert(r != 0);
	initDynArr(r, cap);
	return r;
}

void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

int sizeDynArr(DynArr *v)
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
void addDynArr(DynArr *v, TYPE val)
{
	/* Check to see if a resize is necessary */
	if (v->size >= v->capacity) {
		/*int newCap = 2 * v->capacity;
		DynArr *tempArray = malloc(sizeof(DynArr));
		tempArray->data = malloc(sizeof(TYPE) * newCap);
		assert(tempArray->data != 0);
		int oldArraySize = sizeDynArr(v);
		for (int counter = 0; counter < oldArraySize; counter++) {
			tempArray->data[counter] = v->data[counter];
		}
		freeDynArr(v);
		v->data = tempArray->data;
		v->capacity = newCap;
		v->size = oldArraySize;*/
		_setCapacityDynArr(v, 2 * v->capacity);
	}
	v->data[v->size] = val;
	v->size++;


}

void _setCapacityDynArr(DynArr *v, int newCap)
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

TYPE getDynArr(DynArr * v, int position) {

	assert(v->data[position] != 0);
	return v->data[position];

}

void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(v->data[pos] != 0);
	v->data[pos] = val;
}

void swapDynArr(DynArr *v, int i, int  j)
{
	assert(v->data[i] != 0);
	assert(v->data[j] != 0);
	TYPE temp = v->data[i];
	v->data[i] = v->data[j];
	v->data[j] = temp;

}


void removeAtDynArr(DynArr *v, int idx)
{
	assert(v->data[idx != 0]);
	for (int i = idx; i < v->size - 1; i++) {
		v->data[i] = v->data[i + 1];
	}

	//after loop/if last index reduce size by one
	v->size--;

}

void pushDynArr(struct DynArr* v, TYPE e) {
	addDynArr(v, e);
}

int isEmptyDynArr(struct DynArr* v) {
	return sizeDynArr(v) > 0 ? 0 : 1;
}

TYPE topDynArr(struct DynArr* v) {
	assert(!isEmptyDynArr(v));
	return getDynArr(v, sizeDynArr(v) - 1);
}

void popDynArr(struct DynArr * v) {
	assert(!isEmptyDynArr(v));
	removeAtDynArr(v, sizeDynArr(v) - 1);
}

int containsDynArr(struct DynArr* v, TYPE e) {
	int i = 0;
	for (i = 0; i < v->size; i++) {
		if (EQ(e, v->data[i])) {
			return 1;
		}
	}
	return 0;
}

void removeDynArr(DynArr *v, TYPE val)
{
	assert(!isEmptyDynArr(v));
	int idx = -1;//initialize value of index to delete to -1
	for (int j = 0; j < v->size; j++)
	{
		if (v->data[j] == val) {
			idx = j;
			j = v->size;//exit loop
		}
	}
	if (idx != -1) {
		//remove value
		assert(v->data[idx != 0]);
		for (int i = idx; i < v->size - 1; i++) {
			v->data[i] = v->data[i + 1];
		}

		//after loop/if last index reduce size by one
		v->size--;
	}
	//not in
}

// this main function contains some
int main(int argc, char* argv[]){

	DynArr *dyn;
	dyn = newDynArr(2);
        
	
	printf("\n\nTesting addDynArr...\n");
	addDynArr(dyn, 3);
	addDynArr(dyn, 4);
	addDynArr(dyn, 10);
	addDynArr(dyn, 5);
	addDynArr(dyn, 6);
	
	printf("The array's content: [3,4,10,5,6]\n");
	assertTrue(EQ(getDynArr(dyn, 0), 3), "Test 1st element == 3");
	assertTrue(EQ(getDynArr(dyn, 1), 4), "Test 2nd element == 4");
	assertTrue(EQ(getDynArr(dyn, 2), 10), "Test 3rd element == 10");
	assertTrue(EQ(getDynArr(dyn, 3), 5), "Test 4th element == 5");
	assertTrue(EQ(getDynArr(dyn, 4), 6), "Test 5th element == 6");
	assertTrue(sizeDynArr(dyn) == 5, "Test size = 5");
	
	printf("\n\nTesting putDynArr...\nCalling putDynArr(dyn, 2, 7)\n");
	putDynArr(dyn, 2, 7); 
	printf("The array's content: [3,4,7,5,6]\n");
	assertTrue(EQ(getDynArr(dyn, 2), 7), "Test 3rd element == 7");
	assertTrue(sizeDynArr(dyn) == 5, "Test size = 5");
	
	printf("\n\nTesting swapDynArr...\nCalling swapDynArr(dyn, 2, 4)\n");
	swapDynArr(dyn, 2, 4);
	printf("The array's content: [3,4,6,5,7]\n");
	assertTrue(EQ(getDynArr(dyn, 2), 6), "Test 3rd element == 6");
	assertTrue(EQ(getDynArr(dyn, 4), 7), "Test 5th element == 7");
	
	printf("\n\nTesting removeAtDynArr...\nCalling removeAtDynArr(dyn, 1)\n");
	removeAtDynArr(dyn, 1);
	printf("The array's content: [3,6,5,7]\n");
	assertTrue(EQ(getDynArr(dyn, 0), 3), "Test 1st element == 3");
	assertTrue(EQ(getDynArr(dyn, 3), 7), "Test 4th element == 7");
	assertTrue(sizeDynArr(dyn) == 4, "Test size = 4");
	
	printf("\n\nTesting stack interface...\n");
	printf("The stack's content: [3,6,5,7] <- top\n");
	assertTrue(!isEmptyDynArr(dyn), "Testing isEmptyDynArr");
	assertTrue(EQ(topDynArr(dyn), 7), "Test topDynArr == 7");
	
	popDynArr(dyn);
	printf("Poping...\nThe stack's content: [3,6,5] <- top\n");
	assertTrue(EQ(topDynArr(dyn), 5), "Test topDynArr == 5");
	
	pushDynArr(dyn, 9);
	printf("Pushing 9...\nThe stack's content: [3,6,5,9] <- top\n");
	assertTrue(EQ(topDynArr(dyn), 9), "Test topDynArr == 9");
	
	printf("\n\nTesting bag interface...\n");
	printf("The bag's content: [3,6,5,9]\n");
	assertTrue(containsDynArr(dyn, 3), "Test containing 3");
	assertTrue(containsDynArr(dyn, 6), "Test containing 6");
	assertTrue(containsDynArr(dyn, 5), "Test containing 5");
	assertTrue(containsDynArr(dyn, 9), "Test containing 9");
	assertTrue(!containsDynArr(dyn, 7), "Test not containing 7");
	
	removeDynArr(dyn, 3);
	printf("Removing 3...\nThe stack's content: [6,5,9]\n");
 	assertTrue(!containsDynArr(dyn, 3), "Test not containing 3");
	
	
     deleteDynArr(dyn); 
	 getchar();
	return 0;
}
