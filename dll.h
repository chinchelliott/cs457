/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Adapted from Programming Assignment 0 for Assignment 2
*
* Header file of the doubly linked list class
*
*************************************************/

#include <stdio.h>

#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

typedef struct dllnode {
	void *value;
	struct dllnode *next;
	struct dllnode *prev;
	} dllnode;

typedef struct dll {
	dllnode *head;
	dllnode *tail;
	int size;
	void (*display)(FILE *, void *);
	} dll;

dll *newDLL(void (*d)(FILE *, void *));	//constructor
void insertDLL(dll *items, int index, void *value);	//stores a generic value
void addToFrontD(dll *items, dllnode *newNode);
void addToBackD(dll *items, dllnode *newNode);
void addToMiddleD(dll *items, int index, dllnode *newNode);
void *removeDLL(dll *items, int index);	//returns a generic value
void *removeFromBackD(dll *items);
void *removeFromFrontD(dll *items);
void *removeFromMiddleD(dll *items, int index);
void unionDLL(dll *recipient, dll *donor);	//merge two SLLS into one
void *getDLL(dll *items, int index);	//get value at the index
int sizeDLL(dll *items);
void displayDLL(FILE *, dll *items);

#endif
