#ifndef __COLLECTION__
#define __COLLECTION__
#include "bst.h"
#include "document.h"

typedef struct collection {
    bst *documents;
    char *name;
} collection;

collection *newCollection(char *, void (*d)(FILE *,void *),int (*c)(void *,void *));
void collectionInsert(collection *, document *);
void displayCollection(FILE *,collection *);

#endif
