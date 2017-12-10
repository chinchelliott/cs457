#ifndef __DB_DOC__
#define __DB_DOC__

#include "sll.h"
#include "field.h"

typedef struct document {

    sll *fields; //list of key pair values, possibly dll?
    int size;
    int sysid;
    int version;
    int latest;
    //int docID;


} document;

document *newDocument(int i, void (*d)(FILE *, void *));
void docInsert(document *, field *);
void displayDocument(FILE *,document *);
int getID(document *);
field *getField(document *doc, char *field);



#endif
