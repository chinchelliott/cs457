#include "document.h"


document *newDocument(int i) {
    document *items = malloc(sizeof(document));
    items->sysid = i;
    items->version = 0;
    items->latest = 0;
    items->fields = newDLL(void, void);
}


void docInsert(document *doc, char *k, char *val) {


    field *myField = newField(k,v);
    insertBST(doc->fields, myField);

}
