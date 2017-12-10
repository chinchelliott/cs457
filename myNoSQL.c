#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "field.h"
#include "document.h"
#include "collection.h"
#include "queue.h"

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);
void displayValue(FILE *fp, void *s);
int valComp(void *v, void *w);
collection *createCollection(FILE *, FILE *);
int fieldComp(void *fld, void *doc);
void displayQueueValue(FILE *fp, void *s);

int main(int argc,char **argv) {

    if (argc == 1) {
		fprintf(stdout,"Number of commands: %d command, exiting program\n",argc);
		exit(-1);
	}

    FILE *data, *queries, *output;
    data = fopen(argv[1],"r");
    queries = fopen(argv[2],"r");
    output = fopen("result.txt", "w");

    Printer print;
    print = displayValue;

    Printer qprint;
    qprint = displayQueueValue;

    collection *db = createCollection(data, output);
    collectionStats(output, db);

    //document *comparing = newDocument(0,print);
    //new field
    //insert field
    //somehow compare fields?

    Comparator newComp;
    newComp = fieldComp;
    //updateComp(db, newComp);
    printf("how far do we get 0\n");

    char hello[8] = "DocID:50";
    field *myField = newField(hello);
    printf("how far do we get 1\n");

    queue *results = newQueue(print);
    printf("how far do we get 2\n");
    //char *myFld = "Salary";
    searchCollection(db,myField,results,fieldComp);
    printf("how far do we get 3\n");

    FILE *output2 = fopen("help.txt", "w");
    printf("how far do we get 3.5\n");

    displayQueue(output2, results);
    printf("how far do we get 4\n");


return 0;
}


int valComp(void *v, void *w) {
	int val1 = getID(v);
	int val2 = getID(w);
	return (val1 - val2);
}


int fieldComp(void *fld, void *doc) {
    // printf("in comparing function\n");
    char *myfield = getKey(fld);
    field *find = getField(doc, myfield);
    if (find == NULL) return -1;
    else {
        int x = atoi(getValue(find));
        int y = atoi(getValue(fld));
        //switch statement here for operators
        // printf("first number is %s", x);
        // printf("second number is %d", y);
        return x-y;
    }
    // return x;
}

// //kept simple for now. will have to change obviously
void displayValue(FILE *fp, void *s) {
	fprintf(fp, "%s:%s", getKey(s), getValue(s));
}

void displayQueueValue(FILE *fp, void *s) {
    bstNode *n = s;
	displayDocument(fp,n->value);
}

collection *createCollection(FILE *data, FILE *output) {
    int docCount = 0;

    char *token;
    Printer print;
    Comparator comp;
    print = displayValue;
    comp = valComp;

    collection *collect = newCollection("final",print,comp);

    int ch = fgetc(data);

    //outer loop for collection
    while (!feof(data)) {
    document *myDoc = newDocument(docCount, print);
    //inner loop for document
    while (ch !='\n') {
        ungetc(ch,data);
        token = readToken(data);
        field *myField = newField(token);
        ch = fgetc(data);
        docInsert(myDoc,myField);
    }
    displayDocument(output,myDoc);
    collectionInsert(collect, myDoc);
    docCount++;
    fprintf(output,"\n");
    ch = fgetc(data);
    }

    return collect;
}
