/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Adapted from Programming Assignment 0 for Assignment 2
*
* Implementation of the singly linked list class
*
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "field.h"

//constructor for SLL
sll *newSLL(void (*d)(FILE *, void *)){
	sll *items = malloc(sizeof(sll));
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

//inserts new node into SLL, 3 cases: front of the SLL, at end, or at index
void insertSLL(sll *items, void *value) {

	sllnode *newNode = malloc(sizeof(sllnode));
	newNode->value = value;
	newNode->next = NULL;

	// if (index == 0) {
	// 	addToFront(items, newNode);
	// }

	//else if (items->size == index) {
		addToBack(items, newNode);
	//}

	//else {
	//	addToMiddle(items, index, newNode);
//	}

	items->size += 1;
}

//case that node is added to front of SLL
void addToFront(sll *items, sllnode *newNode) {

	if (items->size == 0) {
		items->head = newNode;
		items->tail = newNode;
		newNode->next = NULL;
	}

	else {
		newNode->next = items->head;
		items->head = newNode;
	}
}

//case that node is added to the back of SLL
void addToBack(sll *items, sllnode *newNode) {
	if (items->size == 0) {
		items->head = newNode;
		items->tail = newNode;
		newNode->next = NULL;
	}
	else if (items->size == 1) {
		items->head->next = newNode;
		items->tail = items->head->next;
	}
	else {
		items->tail->next = newNode;
		items->tail->next->next = NULL;
		items->tail = newNode;
	}
}

//case that node is added to specified index of SLL
void addToMiddle(sll *items, int index, sllnode *newNode) {
	sllnode *temp = malloc(sizeof(sllnode));
	temp = items->head;
	for (int i = 0; i < index-1; i++) {
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
}

//removes node from SLL, 3 cases: remove from front, remove from index, or remove from back
void *removeSLL(sll *items, int index) {

 	void *value;

	if (index == 0) {
		value = removeFromFront(items);
	}

	else if (index == items->size-1) {
		value = removeFromBack(items, index);
	}

	else {
		value = removeFromMiddle(items, index);
	}

	items->size = items->size - 1;

	return value;
}

//removes front node of SLL
void *removeFromFront(sll *items) {
	void *value = 0;
	if (items->size == 1) {
		value = items->head->value;
		items->head = 0;
		items->tail = 0;
	}
	else {
		value = items->head->value;
		items->head = items->head->next;
		}
	return value;
}

//removes tail node from SLL
void *removeFromBack(sll *items, int index) {
	void *value = 0;
	if (index == items->size-1) {
			sllnode *temp = malloc(sizeof(sllnode));
			temp = items->head;
			for (int i = 0; i < (items->size-2); i++)
				temp = temp->next;
			value = items->tail->value;
			items->tail = temp;
			items->tail->next = NULL;
		}
	return value;
}

//removes middle node from SLL
void *removeFromMiddle(sll *items, int index) {
	void *value = 0;
	if (index <= items->size-1) {
		sllnode *temp = malloc(sizeof(sllnode));
		temp = items->head;
		for (int i = 0; i < (index-1); i++)
			temp = temp->next;
		value = temp->next->value;
		temp->next = temp->next->next;
	}
	return value;
}

//takes two SLL and links them together
void unionSLL(sll *recipient, sll *donor) {

//if donor is null, nothing to change
//covers case if both are empty, nothing changes
	if (donor->head == NULL) {
		return;
	}

//if recipient is empty but donor is not
	if (recipient->size == 0) {
		//add donor to empty recipient
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		recipient->size = donor->size;
		donor->head = NULL;
		donor->size = 0;
		donor->tail = NULL;
	}

//if recipient is not empty and donor is not empty
	else {
	recipient->tail->next = donor->head;
	recipient->tail = donor->tail;
	int x = recipient->size;
	recipient->size = donor->size + x;
	donor->head = NULL;
	donor->size = 0;
	donor->tail = NULL;
		}
}

//returns value at specified index
void *getSLL(sll *items, int index) {
	sllnode *temp = malloc(sizeof(sllnode));
	temp = items->head;
	void *val = 0;
	for (int i=0; i < index; i++) {
		temp = temp->next;
	}
	val = temp->value;
	return val;
}

//returns size of SLL
int sizeSLL(sll *items) {
	return items->size;
}

//displays SLL
void displaySLL(FILE *fp, sll *items) {
	printf("the size of this sll is %d", items->size);
	sllnode *temp = malloc(sizeof(sllnode));
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

void *findSLL(sll *items, void *com) {
	// printf("in find SLL\n");
	char *comp = com;
	sllnode *temp = malloc(sizeof(sllnode));
	temp = items->head;
	// void *val = 0;
	field *iField;
	while (temp->next) {
		iField = temp->value;
		if (strcmp(getKey(iField),comp) == 0) {
			// printf("value is %s\n", getValue(iField));
			return iField;
		}
		temp = temp->next;
	}
	return NULL;
	// val = temp->value;
}
