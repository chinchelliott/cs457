#include <stdlib.h>
#include <string.h>
#include "field.h"

field *newField(char *token) {
    field *items = malloc(sizeof(field));

    items->key = strtok(token, ":");
    items->value = strtok(NULL, ":");

    // items->key = k;
    // items->value = v;
    return items;
}

char *getKey(field *f) {
    return f->key;
}
char *getValue(field *f) {
    return f->value;
}
