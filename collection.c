#include "collection.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

collection *newCollection(char *n, void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    collection *items = malloc(sizeof(collection));
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
    items->name = n;
    items->documents = newRBT(d, c);
    return items;
}


void collectionInsert(collection *c, document *d) {
    insertRBT(c->documents, d);
}

void displayCollection(FILE *fp, collection *c) {
    displayRBT(fp, c->documents);
}

void collectionStats(FILE *fp, collection *c) {
    statisticsRBT(c->documents, fp);
}

void updateComp(collection *collect, int (*c)(void *,void *)) {
    updateRBTComp(collect->documents, c);
}

void searchCollection(collection *c, void *val, queue *q, int (*comp)(void *,void *)) {
    RBTinorder(c->documents, val, q, comp);
}
