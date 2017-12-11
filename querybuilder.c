//
//  querybuilder.c
//  457_final
//
//  Created by Elliott Miller on 12/11/17.
//  Copyright © 2017 Elliott Miller. All rights reserved.
//
#include "querybuilder.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

query *newQuery(char *op, collection *col, void (*d)(FILE *, void *), int (*c)(void *,void *), void (*qd)(FILE *, void *), FILE *o) {
	query *q = malloc(sizeof(query));
	
//	char operator;
	q->operation = op;
	q->collect = col;
	q->display = d;
	q->compare = c;
	q->qdisplay = qd;
	q->output = o;
//	char *condition;
//	char *value;
//	char **fields;
//	int version;
	return q;
}

void createQuery(query *q, char *line) {

	int count = 100;
	document *myDoc = newDocument(count, q->display);
	
	if (strcmp(q->operation,"insert") == 0) {
		
		char *f = strtok(line, " ");
		char *rest = strtok(NULL, " ");
		
		field *myField = newField(f);
		docInsert(myDoc,myField);
		
		while (rest != NULL) {
			int size = strlen(rest);
			
			if (rest[size-1] == ')') {
				rest[size-1] = '\0';
			}
			field *myField = newField(rest);
			docInsert(myDoc,myField);
			count += 1;
			rest = strtok(NULL, " ");
		}
		//displayDocument(stdout,myDoc);
		collectionInsert(q->collect, myDoc);
	}
	
	//final.count([field], [version])
	if (strcmp(q->operation,"count") == 0) {
		char *fld = strtok(line, "([");
		char *rem = strtok(NULL, ",");
		//printf("fld is %s, remainder is %s\n",fld,rem);
		int l = strlen(fld);
		if (rem == NULL) {
			fld[l-2] = '\0';
		}
		else {
			fld[l-3] = '\0';
		}
		field *myField = newField(fld);
		queue *results = newQueue(q->qdisplay);
		q->compare = countComp;
		searchCollection(q->collect,myField,results,q->compare);
		
		int s = sizeQueue(results);
		fprintf(q->output,"count_%s: %d\n", fld, s);
	}

	
}


int countComp(void *fld, void*doc) {
	char *myfield = getKey(fld);
	field *find = getField(doc, myfield);
	if (find != NULL) return 0;
	else return -1;
}

void displayQValue(FILE *fp, void *doc) {
	void *myDoc = getRBTValue(doc);
	displayDocument(fp,myDoc);
}


