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
#include "queue.h"

    #ifndef __BST_INCLUDED__
    #define __BST_INCLUDED__

    typedef struct bstNode
        {
        struct bstNode *left;
        struct bstNode *right;
        struct bstNode *parent;
        void *value;
        } bstNode;

    typedef struct bst
        {
        bstNode *root;
        int size;
        void (*display)(FILE *,void *);
        int (*compare)(void *,void *);
        } bst;

    extern bst *newBST(void (*)(FILE *,void *),int (*)(void *,void *));
    extern bstNode *insertBST(bst *,void *);
    extern int findBST(bst *,void *);
    extern bstNode *findBSTNode(bst *,void *);
    extern bstNode *swapToLeafBSTNode(bstNode *);
    extern void pruneBSTNode(bst *,bstNode *);
    extern int sizeBST(bst *);
    extern void statisticsBST(bst *,FILE *);
    extern void displayBST(FILE *,bst *);
    extern void checkBST(bst *);                //optional


    //new functions! woo!
    queue *findAllBSTNodes(bst *t,void *val);
    void inorder(bst *t, void *val, bstNode *n, queue *q);

    #endif
