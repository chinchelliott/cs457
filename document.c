#include <stdlib.h>
#include "document.h"


document *newDocument(int i, void (*d)(FILE *, void *)) {
    document *items = malloc(sizeof(document));
    items->sysid = i;
    items->version = 0;
    items->latest = 0;
    items->fields = newSLL(d);
    return items;
}


void docInsert(document *doc, field *f) {
    insertSLL(doc->fields, f);
}

void displayDocument(FILE *fp,document *doc) {
    displaySLL(fp, doc->fields);
}
