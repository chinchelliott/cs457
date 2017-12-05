/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Adapted from Programming Assignment 0 for Assignment 2
*
* Header file of the queue class
* Built upon singly linked list
*
*************************************************/

#include <stdio.h>
#include "sll.h"

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

typedef struct queue {
	
	struct sll *list;
	int length;
	
	} queue;
	
queue *newQueue(void (*d)(FILE *,void *));   //constructor
void enqueue(queue *items,void *value);      //stores a generic value
void *dequeue(queue *items);                 //returns a generic value
void *peekQueue(queue *items);               //returns a generic value
int sizeQueue(queue *items);
void displayQueue(FILE *fp,queue *items);

#endif