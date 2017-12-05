#ifndef __COLLECTION__
#define __COLLECTION__
#include "rbt.h"
#include "document.h"

typedef struct collection {
    rbt *documents;
    char *name;
} collection;

collection *newCollection(char *, void (*d)(FILE *,void *),int (*c)(void *,void *));
void collectionInsert(collection *, document *);
void displayCollection(FILE *,collection *);
void collectionStats(FILE *, collection *);

#endif
