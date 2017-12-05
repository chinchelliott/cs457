#include <stdlib.h>
#include "field.h"

field *newField(char *k, char *v) {
    field *items = malloc(sizeof(field));
    items->key = k;
    items->value = v;
    return items;
}

char *getKey(field *f) {
    return f->key;
}
char *getValue(field *f) {
    return f->value;
}
