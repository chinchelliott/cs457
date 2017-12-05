#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "field.h"
#include "document.h"
#include "collection.h"

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);
void displayValue(FILE *fp, void *s);
int valComp(void *v, void *w);

int main(int argc,char **argv) {

    if (argc == 1) {
		fprintf(stdout,"Number of commands: %d command, exiting program\n",argc);
		exit(-1);
	}

    FILE *data, *queries, *output;
    data = fopen(argv[1],"r");
    queries = fopen(argv[2],"r");
    output = fopen("result.txt", "w");

    int docCount = 0;

    char *token;
    Printer print;
    Comparator comp;
    print = displayValue;
    comp = valComp;

    collection *collect = newCollection("final",print,comp);

// while (!eof(data)) {
int ch = fgetc(data);

while (!feof(data)) {
    //inner loop for document
    document *myDoc = newDocument(docCount, print);
    while (ch !='\n') {
        ungetc(ch,data);
        token = readToken(data);
        field *myField = newField(token);
        ch = fgetc(data);
        //line = readToken(data);
        //displayValue(output,myField);
        docInsert(myDoc,myField);
    }
    displayDocument(output,myDoc);
    docCount++;
    fprintf(output,"\n");
    ch = fgetc(data);
}

displayCollection(output, collect);

return 0;
}


int valComp(void *v, void *w) {
	int val1 = getID(v);
	int val2 = getID(w);
	return (val1 - val2);
}

// //kept simple for now. will have to change obviously
void displayValue(FILE *fp, void *s) {
	fprintf(fp, "%s:%s", getKey(s), getValue(s));
}
