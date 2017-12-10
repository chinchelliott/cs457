/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Adapted from Programming Assignment 0 for Assignment 2
*
* Header file of of the singly linked list class
*
*************************************************/

#include <stdio.h>
#include <string.h>

#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__

typedef struct sllnode {
	void *value;
	struct sllnode *next;
	} sllnode;

typedef struct sll {
	sllnode *head;
	sllnode *tail;
	int size;
	void (*display)(FILE *, void *);
	} sll;

sll *newSLL(void (*d)(FILE *, void *));	//constructor
void insertSLL(sll *items, void *value);	//stores a generic value
void addToFront(sll *items, sllnode *newNode);
void addToBack(sll *items, sllnode *newNode);
void addToMiddle(sll *items, int index, sllnode *newNode);
void *removeSLL(sll *items, int index);	//returns a generic value
void *removeFromBack(sll *items, int index);
void *removeFromFront(sll *items);
void *removeFromMiddle(sll *items, int index);
void unionSLL(sll *recipient, sll *donor);	//merge two SLLS into one
void *getSLL(sll *items, int index);	//get value at the index
int sizeSLL(sll *items);
void displaySLL(FILE *, sll *items);
void *findSLL(sll *items, void *comp);

#endif
