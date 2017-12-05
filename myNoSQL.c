#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "field.h"

typedef int (*Comparator)(void*,void*);
typedef void (*Printer)(FILE*,void*);


int main(int argc,char **argv) {

    if (argc == 1) {
		fprintf(stdout,"Number of commands: %d command, exiting program\n",argc);
		exit(-1);
	}

    FILE *data, *queries;
    data = fopen(argv[1],"r");
    queries = fopen(argv[2],"r");

    comp = stringComparator;
	display = displayValue;

    char *token;

// while (!eof(data)) {
    int ch = fgetc(data);


    //inner loop for document
    while (ch !='\n') {
        ungetc(ch,data);
        token = readToken(data);
        printf("token is %s\n", token);
        ch = fgetc(data);
        //line = readToken(data);
    }

    // String namepass[] = strLine.split(":");
    // String name = namepass[0];
    // String pass = namepass[1];

return 0;
}


int stringComparator(void *v, void *w) {
	char *val1 = getString(v);
	char *val2 = getString(w);
	return strcmp(val1,val2);
}

//kept simple for now. will have to change obviously
void displayValue(FILE *fp, void *s) {
    // char *key = getKey(s);
    // char *val = getValue(s);
	fprintf(fp, "%s: %s", getKey(s), getValue(s));
}
