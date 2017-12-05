#ifndef __DB_DOC__
#define __DB_DOC__

#include

typedef struct document {

    dll *fields; //list of key pair values, possibly dll?
    int size;
    int sysid;
    int version;
    int latest;
    //int docID;


} document;

document *newDocument(void);
void docInsert(document *, char *, char *);





#endif
