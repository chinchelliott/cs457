/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Adapted from Programming Assignment 0 for Assignment 2
*
* Implementation of the queue class
* Built upon singly linked list
*
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//constructs a new queue
queue *newQueue(void (*d)(FILE *,void *)) {
	queue *items = malloc(sizeof(queue));
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	sll *newList = newSLL(d);
	items->list = newList;
	items->length = 0;
	return items;
}

//enqueue items to back of list
void enqueue(queue *items,void *value) {
	insertSLL(items->list,value);
	items->length += 1;
}

//dequeues items from front of list, so that FIFO/LILO
void *dequeue(queue *items) {
	void *value;
	value = removeSLL(items->list,0);
	items->length = items->length-1;
	return value;
}

//returns first value from queue
void *peekQueue(queue *items) {
	void *value;
	value = getSLL(items->list,0);
	return value;
}

//returns size of queue
int sizeQueue(queue *items) {
	return items->length;
}

//displays the queue
void displayQueue(FILE *fp,queue *items) {
	displaySLL(fp,items->list);
}
