/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Assignment 2
*
* Implementation for binary search tree class
*
*
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"
#include "queue.h"
#include "document.h"

static bstNode *newBSTNode(void *v);
bool predecessorExists(bstNode *n);
bstNode *findPredecessor(bstNode *n);
bool successorExists(bstNode *n);
bool isLeaf(bstNode *x);
bstNode *findSuccessor(bstNode *n);
bstNode *swapNodes(bstNode *a, bstNode *b);
void helpDisplay(FILE *fp,bst *t, bstNode *x);
bool isLeft(bstNode *x);
bool isRight(bstNode *x);
bool isRoot(bstNode *x);
int maxHeight(bstNode *x);
int minHeight(bstNode *x);

bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {

	bst *tree = malloc(sizeof(bst));
	if (tree == 0) {
		fprintf(stderr, "out of memory");
	}
	tree->root = NULL;
	tree->compare = c;
	tree->display = d;
	tree->size = 0;
	return tree;
}

bstNode *insertBST(bst *t,void *val) {
    bstNode *y = malloc(sizeof(bstNode));
    bstNode *x = malloc(sizeof(bstNode));
    bstNode *newNode = newBSTNode(val);

    if (t->root == NULL) {
    	t->root = newNode;
    	t->root->parent = newNode;
    	return newNode;
    }

    y = NULL;
    x = t->root;
    while (x != NULL) {
    	y = x;
    	if (t->compare(val,x->value) < 0) {	//needs compare function
    		x = x->left;
    	}
    	else {
    		x = x->right;
    	}
    }
    newNode->parent = y;
    if (y == NULL) {
    	t->root = newNode;
    	t->root->parent = newNode;
    }
    else if (t->compare(val,y->value) < 0) {	//needs compare function
    	y->left = newNode;
    	}
    else {
    	y->right = newNode;
    	}
    t->size++;
	return newNode;
}


int findBST(bst *t,void *v) {
	if (findBSTNode(t,v) != NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

bstNode *findBSTNode(bst *t,void *val) {

	bstNode *x = malloc(sizeof(bstNode));
	if (t->root == NULL) {
		return NULL;
	}
	x = t->root;
	while (x != NULL) {
		if (t->compare(val,x->value) < 0) {
			x = x->left;
		}
		else if (t->compare(val,x->value) > 0) {
			x = x->right;
		}
		else {
			if (x == NULL) {
				return 0;
			}
			else {
			return x;
			}
		}
	}
	return x;
}


bstNode *swapToLeafBSTNode(bstNode *n) {

	bstNode *temp = malloc(sizeof(bstNode));
	temp = n;

	if (!predecessorExists(temp) && !successorExists(temp)) {
			return temp;
		}

	if (predecessorExists(temp)) {
		temp = findPredecessor(temp->left);
	}
	else if (successorExists(temp)) {
		temp = findSuccessor(temp->right);
	}
	n->value = temp->value;
	temp = swapToLeafBSTNode(temp);

return temp;
}


void pruneBSTNode(bst *t,bstNode *n) {

	if (t->size == 1) {
		t->root = 0;
		return;
	}
	//t->display(stdout,n->value);
	bstNode *p = n->parent;
	//t->display(stdout,p->value);
	if (predecessorExists(p) && (t->compare(p->left->value,n->value) == 0)) {
		p->left = NULL;
	}
	else {
		p->right = NULL;
	}
	t->size--;
}

void statisticsBST(bst *t,FILE *fp) {

	int max = maxHeight(t->root);
	int min = minHeight(t->root);
	fprintf(fp,"Minimum depth: %d\n",min);
	fprintf(fp,"Maximum depth: %d",max);
	fprintf(fp,"\n");
}

void displayBST(FILE *fp,bst *t) {

	fprintf(fp,"0:");
	queue *q = newQueue(t->display);
	bstNode *x = malloc(sizeof(bstNode));
	if (t->root == 0) {
		fprintf(fp,"\n");
		return;
	}
	enqueue(q,t->root);
	enqueue(q,NULL);
	int height = maxHeight(t->root);
	int i = 1;
	x = dequeue(q);
	while (sizeQueue(q) > 0) {

		if ((x == NULL) && (sizeQueue(q)>0)) {
			fprintf(fp,"\n");
			enqueue(q,NULL);
			if (i <= height) {
				fprintf(fp,"%d:",i);
				i++;
			}
		}
		else {
			helpDisplay(fp,t,x);
			//t->display(fp,x->value);
			if (x->left != NULL) {
				//printf("left child is not null\n");
				enqueue(q,x->left);
				//printf("left child has been enqueued\n");
			}
			if (x->right != NULL) {
				//printf("right child is not null\n");
				enqueue(q,x->right);
				//printf("right child has been enqueued\n");
			}
		}
		x = dequeue(q);
	}
	fprintf(fp,"\n");
}


//void checkBST(bst *);                //optional


//Private functions

bool predecessorExists(bstNode *n) {
	if (n->left != NULL) {
		return true;
	}
	else {
		return false;
	}
}

//must pass in left child initially
bstNode *findPredecessor(bstNode *n) {

	bstNode *x = n->right;
	if (x!= NULL) {
		n = findPredecessor(x);
	}
	return n;
}

bool successorExists(bstNode *n) {
	if (n->right != NULL) {
		return true;
	}
	else {
		return false;
	}
}

//must pass in right child initially
bstNode *findSuccessor(bstNode *n) {

	bstNode *x = n->left;
	if (x!= NULL) {
		n = findSuccessor(x);
	}
	return n;
}




bstNode *newBSTNode(void *v) {
	bstNode *newNode = malloc(sizeof(bstNode));
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->value = v;
	return newNode;
}

bstNode *swapNodes(bstNode *a, bstNode *b) {

	a->value = b->value;
	//a = b;
	return a;
}

void helpDisplay(FILE *fp,bst *t, bstNode *x) {

	fprintf(fp," ");
	if (isLeaf(x)) {
		fprintf(fp,"=");
	}
	t->display(fp,x->value);
	fprintf(fp,"(");
	t->display(fp,x->parent->value);
	fprintf(fp,")");
	if (isLeft(x)) fprintf(fp,"-l");
	else if (isRight(x)) fprintf(fp,"-r");
	else if (isRoot(x)) fprintf(fp,"-");

}


int maxHeight(bstNode *x) {

	if (x == NULL) {
		return 0;
	}
	//printf("max height test 1\n");
	int lDepth = maxHeight(x->left);
		//printf("max height test 2\n");
	int rDepth = maxHeight(x->right);
		//printf("max height test 3\n");

	if (lDepth > rDepth) return (lDepth+1);
	else return (rDepth+1);

}

int minHeight(bstNode *x) {

	if (x->right == NULL || x->left == NULL) {
		return 1;
	}

	int lDepth = minHeight(x->left);
	int rDepth = minHeight(x->right);

	if (lDepth < rDepth) return (lDepth+1);
	else return (rDepth+1);

}



bool isLeaf(bstNode *x) {
	if (x->left == NULL && x->right == NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool isLeft(bstNode *x) {
	if (x->parent->left == x) {
		return true;
	}
	else {
		return false;
	}
}

bool isRight(bstNode *x) {
	if (x->parent->right == x) {
		return true;
	}
	else {
		return false;
	}
}

bool isRoot(bstNode *x) {
	if (x->parent == x) {
		return true;
	}
	else {
		return false;
	}
}

queue *findAllBSTNodes(bst *t,void *val) {

	queue *q = newQueue(t->display);
    inorder(t,val,t->root,q);
    return q;
}


void inorder(bst *t, void *val, bstNode *n, queue *q) {
   if(n != NULL) {
      inorder(t, val, n->left, q);
      if (t->compare(val, n->value) == 0) {
		  // enqueue(q,n->value); enquing a bst node that holds a document
		  //document *temp = n;
		  //displayDocument(stdout,n->value);
		  //void *temp = n->value;
		  enqueue(q,n->value);
		}
      // printf("%d ",root->data);
      inorder(t, val, n->right, q);
   }
}

bstNode *getRoot(bst *t) {
	return t->root;
}
