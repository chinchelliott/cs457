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

query *newQuery(char *op, collection *col, void (*d)(FILE *, void *), int (*c)(void *,void *)) {
	query *q = malloc(sizeof(query));
	
//	char operator;
	q->operation = op;
	q->collect = col;
	q->display = d;
	q->compare = c;
//	char *condition;
//	char *value;
//	char **fields;
//	int version;
	return q;
}

void createQuery(query *q, char *line) {
	
	int count = 100;
	if (strcmp(q->operation,"insert") == 0) {
		char *f = strtok(line, " ");
		while (f != NULL) {
			
			document *myDoc = newDocument(count, q->display);
			field *myField = newField(f);
			docInsert(myDoc,myField);
			displayDocument(stdout,myDoc);
			collectionInsert(q->collect, myDoc);
			f = strtok(NULL, " ");
			count += 1;
		}
	}
}




