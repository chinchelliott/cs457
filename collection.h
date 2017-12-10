#ifndef __COLLECTION__
#define __COLLECTION__
#include "rbt.h"
#include "document.h"
#include "queue.h"

typedef struct collection {
    rbt *documents;
    char *name;
} collection;

collection *newCollection(char *, void (*d)(FILE *,void *),int (*c)(void *,void *));
void collectionInsert(collection *, document *);
void displayCollection(FILE *,collection *);
void collectionStats(FILE *, collection *);
void updateComp(collection *, int (*c)(void *,void *));
void searchCollection(collection *c, void *, queue *q, int (*comp)(void *,void *));

#endif
