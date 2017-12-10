#ifndef __DOC_FIELD__
#define __DOC_FIELD__

typedef struct field {
    char *key;
    char *value;
    char op;
} field;

field *newField(char *);
char *getKey(field *);
char *getValue(field *);
void insertOperator(field *f, char op);

#endif
