//
//  querybuilder.h
//  457_final
//
//  Created by Elliott Miller on 12/11/17.
//  Copyright © 2017 Elliott Miller. All rights reserved.
//

#ifndef querybuilder_h
#define querybuilder_h

#include <stdio.h>
#include "collection.h"
#include "field.h"
#include "document.h"

typedef struct query {
    char operator;
    char *operation;
    char *condition;
    char *value;
    char **fields;
    int version;
	collection *collect;
	void (*display)(FILE *,void *);
	int (*compare)(void *,void *);
    
} query;

query *newQuery(char *, collection *col, void (*d)(FILE *, void *), int (*c)(void *,void *));
void createQuery(query *, char *);
void insertFields(int size);
void queryDisplay(void);
int queryCompare(void *,void *);

#endif /* querybuilder_h */
