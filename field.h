#ifndef __DOC_FIELD__
#define __DOC_FIELD__

typedef struct field {
    char *key;
    char *value;
} field;

field *newField(char *,char *);
char *getKey(field *);
char *getValue(field *);

#endif
