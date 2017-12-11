/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Assignment 2
*
* Header file for binary search tree
*
*
*************************************************/


	#include <stdio.h>
    #include "bst.h"
	#include "queue.h"

    #ifndef __RBT_INCLUDED__
    #define __RBT_INCLUDED__

typedef struct rbt
        {
        bst *tree;
        void (*display)(FILE *,void *);
        int (*compare)(void *,void *);
        int size;
        int words;
        } rbt;

    rbt *newRBT(void (*)(FILE *,void *),int (*)(void *,void *));
    void insertRBT(rbt *,void *);
    int findRBT(rbt *,void *);
    void deleteRBT(rbt *,void *);
    void statisticsRBT(rbt *,FILE *);
    void displayRBT(FILE *,rbt *);
    void checkRBT(rbt *);               //optional
	void updateRBTComp(rbt *t, int (*c)(void *,void *));
	void RBTinorder(rbt *t, void *, queue *q, int (*c)(void *,void *));
    void *getRBTValue(void *in);



    #endif
