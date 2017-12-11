#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "field.h"
#include "document.h"
#include "collection.h"
#include "queue.h"
#include "bst.h"
#include "rbt.h"
#include "querybuilder.h"

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);
void displayValue(FILE *fp, void *s);
int valComp(void *v, void *w);
collection *createCollection(FILE *, FILE *);
int fieldComp(void *fld, void *doc);
void displayQueueValue(FILE *fp, void *s);
void parseQuery(FILE *q, FILE *output, collection *c);


int main(int argc,char **argv) {

    // if (argc == 1) {
	// 	fprintf(stdout,"Number of commands: %d command, exiting program\n",argc);
	// 	exit(-1);
	// }

    FILE *data, *queries, *output;
    //data = fopen(argv[1],"r");
    data = fopen("data.txt","r");

    //queries = fopen(argv[2],"r");
    output = fopen("result.txt", "w");

    Printer print;
    print = displayValue;

    Printer qprint;
    qprint = displayQueueValue;

    collection *db = createCollection(data, output);
    collectionStats(output, db);

    Comparator newComp;
    newComp = fieldComp;
    printf("how far do we get 0\n");

    char hello[8] = "DocID:50";
    field *myField = newField(hello);
    printf("how far do we get 1\n");

    queue *results = newQueue(qprint);
    searchCollection(db,myField,results,newComp);

    FILE *output2 = fopen("help.txt", "w");

    displayQueue(output2, results);

//    int s = sizeQueue(results);
    
    FILE *queues = fopen("queries.txt", "r");
    
    parseQuery(queues, output2, db);


return 0;
}


int valComp(void *v, void *w) {
	int val1 = getID(v);
	int val2 = getID(w);
	return (val1 - val2);
}


int fieldComp(void *fld, void *doc) {
    // printf("in comparing function\n");
    displayDocument(stdout,doc);
    printf("\n");
    char *myfield = getKey(fld);
    field *find = getField(doc, myfield);
    displayDocument(stdout,doc);
    printf("\n");
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

void displayQueueValue(FILE *fp, void *doc) {
    void *myDoc = getRBTValue(doc);
     displayDocument(fp,myDoc);
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


void parseQuery(FILE *q, FILE *output, collection *c) {
	
	Printer print;
	Comparator comp;
	print = displayValue;
	comp = valComp;
	
    char *token;
    char *op;
	char *rest;
    int ch = fgetc(q);
    while (ch !='\n') {
        while (ch !='.') {
            ch = fgetc(q);
        }
        token = readToken(q);
        op = strtok(token, "(");
		rest = strtok(NULL, "(");
		
        printf("rest of token is %s\n",rest);
        printf("operation is %s\n",op);
		query *myQ = newQuery(op, c, print, comp);
		createQuery(myQ, rest);
        return;
    }
}
