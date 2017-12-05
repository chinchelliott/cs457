/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Adapted from Programming Assignment 0 for Assignment 2
*
* Implementation of the doubly linked list class
*
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"

//constructor for DLL
dll *newDLL(void (*d)(FILE *, void *)){
	dll *items = malloc(sizeof(dll));
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	items->head = 0;
	items->tail = 0;
	items->size = 0;
	items->display = d;
	return items;
}

//inserts new node into SLL, 3 cases: front of the DLL, at end, or at index
void insertDLL(dll *items, int index, void *value) {

	dllnode *newNode = malloc(sizeof(dllnode));
	newNode->value = value;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (index == 0) {
		addToFrontD(items, newNode);
	}

	else if (items->size == index) {
		addToBackD(items, newNode);
	}

	else {
		addToMiddleD(items, index, newNode);
	}

	items->size += 1;
}

//case that node is added to front of DLL
void addToFrontD(dll *items, dllnode *newNode) {

	if (items->size == 0) {
		items->head = newNode;
		items->head->next = NULL;
		items->head->prev = NULL;
		items->tail = items->head;
	}
	else {
		newNode->next = items->head;
		items->head->prev = newNode;
		items->head = newNode;
	}
}

//case that node is added to the back of DLL
void addToBackD(dll *items, dllnode *newNode) {

	items->tail->next = newNode;
	newNode->prev = items->tail;
	newNode->next = 0;
	items->tail = newNode;
}

//case that node is added to specified index of DLL
void addToMiddleD(dll *items, int index, dllnode *newNode) {
	dllnode *temp = malloc(sizeof(dllnode));
	if (index <= items->size/2) {
		temp = items->head;
		for (int i = 0; i < (index-1); i++) {
			temp = temp->next;
		}
		//temp points to prev value
		newNode->prev = temp;
		newNode->next = temp->next;
		temp->next->prev = newNode;
		temp->next = newNode;
		}
	else {
		temp = items->tail;
		for (int i = items->size-1; i > index; i--) {
			temp = temp->prev;
		}
		//temp points to index at which node is inserted
		newNode->next = temp;
		newNode->prev = temp->prev;
		temp->prev->next = newNode;
		temp->prev = newNode;
	}
}

//removes node from DLL, 3 cases: remove from front, remove from index, or remove from back
void *removeDLL(dll *items, int index) {

	void *value = 0;

	if (items->size == 0) {
		return value;
		exit(-1);
	}

	if (index == 0) {
		value = removeFromFrontD(items);
	}

	else if (index == items->size-1) {
		value = removeFromBackD(items);
	}

	else if (index >= items->size) {
		return value;
		exit(-1);
	}

	else {
		value = removeFromMiddleD(items, index);
	}

	items->size = items->size - 1;

	return value;

}

//removes tail node from DLL, if there is only 1 node in list, redirects to remove from front function
void *removeFromBackD(dll *items) {

	assert(items->size > 1);
	void *value = 0;


		value = items->tail->value;
		items->tail = items->tail->prev;
		items->tail->next = NULL;

	return value;
}

//removes front node of DLL
void *removeFromFrontD(dll *items) {

	void *value = 0;
	if (items->size == 1) {
		value = items->head->value;
		items->head = NULL;
		items->tail = NULL;
		}
	else {
		value = items->head->value;
		items->head = items->head->next;
		items->head->prev = NULL;
		}
	return value;

}

//removes middle node from DLL
void *removeFromMiddleD(dll *items, int index) {

	void *value = 0;
	if (index <= items->size-1) {
		dllnode *temp = malloc(sizeof(dllnode));
		if (index <= items->size/2) {
			temp = items->head;
			for (int i = 0; i < (index-1); i++) {
				temp = temp->next;
			}
			//temp points to previous value
			value = temp->next->value;
			temp->next->next->prev = temp;
			temp->next = temp->next->next;
		}
		else {
			temp = items->tail;
			for (int i = items->size-1; i > (index+1); i--) {
				temp = temp->prev;
			}
			//temp points to next value
			value = temp->prev->value;
			temp->prev->prev->next = temp;
			temp->prev = temp->prev->prev;
		}

	}
	return value;
}

//takes two DLL and links them together
void unionDLL(dll *recipient, dll *donor) {

//if donor is empty
	if (donor->head == NULL) {
		return;
		//do nothing, no change to recipient.
	}

//if recipient is not empty and donor is not empty
	else if (recipient->head != NULL) {
	recipient->tail->next = donor->head;
	donor->head->prev = recipient->tail;
	recipient->tail = donor->tail;
	int x = recipient->size;
	recipient->size = donor->size + x;
	donor->head = 0;
	donor->size = 0;
	donor->tail = 0;
	}

//if recipient is empty, but donor is not
	else if (donor->head != NULL) {
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = donor->size;
		donor->head = 0;
		donor->size = 0;
		donor->tail = 0;
	}

	else {
		//both are empty, do nothing.
	}
}


//returns value at specified index
void *getDLL(dll *items, int index) {

	dllnode *temp = malloc(sizeof(dllnode));
	void *val = 0;

	if (index <= items->size/2) {
		temp = items->head;
		for (int i=0; i < index; i++) {
			temp = temp->next;
		}
		val = temp->value;
	}
	else {
		temp = items->tail;
		for (int i= items->size-1; i > index; i--) {
			temp = temp->prev;
		}
		val = temp->value;
	}
	return val;
}

//returns size of DLL
int sizeDLL(dll *items) {
	return items->size;
}

//displays DLL
void displayDLL(FILE *fp, dll *items) {

	dllnode *temp = malloc(sizeof(dllnode));
	fprintf(fp,"[");
	if (items->head == NULL) {
		fprintf(fp,"]");
		return;
	}
	else {
		temp = items->head;
		while (temp != NULL) {
			items->display(fp,temp->value);
			temp = temp->next;
			if (temp!= NULL) {
				fprintf(fp,",");
			}
		}
	}
	fprintf(fp,"]");

}
