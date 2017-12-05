#include "collection.h"
#include <stdio.h>
#include <stdlib.h>

collection *newCollection(char *n, void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    collection *items = malloc(sizeof(collection));
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
    items->name = n;
    items->documents = newBST(d, c);
    return items;
}


void collectionInsert(collection *c, document *d) {
    insertBST(c->documents, d);
}

void displayCollection(FILE *fp, collection *c) {
    displayBST(fp, c->documents);
}
