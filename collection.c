#include "collection.h"
#include <stdio.h>
#include <stdlib.h>

collection *newCollection(char *n) {
    collection *items = malloc(sizeof(collection));
	if (items == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
    items->name = n;
    items->documents = newBST(void);
    return items;
}


void collectionInsert(void) {

    insertBST(doc->fields, myField);

}
