#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "field.h"
#include "document.h"

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);
void displayValue(FILE *fp, void *s);

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
    print = displayValue;

// while (!eof(data)) {
    int ch = fgetc(data);


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


return 0;
}


// int stringComparator(void *v, void *w) {
// 	char *val1 = getString(v);
// 	char *val2 = getString(w);
// 	return strcmp(val1,val2);
// }

// //kept simple for now. will have to change obviously
void displayValue(FILE *fp, void *s) {
	fprintf(fp, "%s:%s", getKey(s), getValue(s));
}
