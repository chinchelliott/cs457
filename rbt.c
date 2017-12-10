/*************************************************
* Elliott Miller
* CS201 Spring 2017, Lusth
* Assignment 2
*
* Implementation file of the red-black tree
*
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rbt.h"

//0 is red, 1 is black

typedef struct rbtValue {
	int frequency;
	void *value;
	void (*display)(FILE *,void *);
	int (*compare)(void *,void *);
	int color;
} rbtValue;

void *newRBTValue(void *v,void (*d)(FILE *,void *),int (*c)(void *,void *));
//void *extractValue(rbtValue *v);
int getFreq(bstNode *v);
void increaseFrequency(bstNode *v);
void decreaseFrequency(bstNode *v);
void rbtFixup(bstNode *n,bst *t);
int compareRBTValue(void *a,void *b);
void displayRBTValue(FILE *fp,void *v);
bool isBlack(bstNode *n);
bool isRed(bstNode *n);
bool isLeftChild(bstNode *n);
bool isRightChild(bstNode *n);
bool treeRoot(bstNode *n);
bstNode *parent(bstNode *n);
bstNode *grandparent(bstNode *n);
bstNode *rightChild(bstNode *n);
bstNode *leftChild(bstNode *n);
bstNode *uncle(bstNode *n);
void colorRed(bstNode *n);
void colorBlack(bstNode *n);
bool isLinear(bstNode *n);
bstNode *lrRotate(bstNode *x);
bstNode *rlRotate(bstNode *x);
void llRotate(bstNode *x,bst *t);
void rrRotate(bstNode *x,bst *t);
bool hasUncle (bstNode *x);

rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
	rbt *t = malloc(sizeof(rbt));
	if (t == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	bst *newTree = newBST(displayRBTValue,compareRBTValue);
	t->tree = newTree;
	t->display = d;
	t->compare = c;
	t->words = 0;
	t->size = 0;
return t;
}

void insertRBT(rbt *t,void *v) {

		//printf("pls\n");
	rbtValue *temp = newRBTValue(v,t->display,t->compare);
			//printf("help\n");
	bstNode *n = findBSTNode(t->tree,temp);
			//printf("???\n");
	if (n == NULL) {
	//printf("prev insert\n");
	bstNode *newNode = insertBST(t->tree,temp);
	rbtFixup(newNode,t->tree);
	increaseFrequency(newNode);
		//printf("post insert\n");
	t->size++;
		//printf("prev display\n");
	//displayRBT(stdout,t);
			//printf("post display\n");
	}
	else {
		//printf("increase test");
		increaseFrequency(n);
	}
	t->words++;
}


int findRBT(rbt *t,void *v) {

	rbtValue *temp = newRBTValue(v,t->display,t->compare);
	bstNode *find = findBSTNode(t->tree,temp);
	if (find == NULL) {
		return -1;
		}
	else {
		return getFreq(find);
	}
}

void deleteRBT(rbt *t,void *v) {
	rbtValue *temp = newRBTValue(v,t->display,t->compare);
	bstNode *delete = findBSTNode(t->tree,temp);
	if (delete == NULL) {
		//printf("not found\n");
		fprintf(stderr,"The word does not exist in tree\n"); //fix this
		}
	else {
		int f = getFreq(delete);
		if (f == 1) {
			delete = swapToLeafBSTNode(delete);
			//printf("test 2\n");
			pruneBSTNode(t->tree,delete);
		}
		else {
			//printf("decreasing frequency\n");
			//printf("frequency before delete: %d\n",findRBT(t,temp));
			decreaseFrequency(delete);
			//printf("frequency after delete: %d\n",findRBT(t,temp));
		}
	}
}

void statisticsRBT(rbt *t,FILE *fp) {
	fprintf(fp,"Words/Phrases: %d",t->words);
	fprintf(fp,"\n");
	fprintf(fp,"Nodes: %d",t->size);
	fprintf(fp,"\n");
	statisticsBST(t->tree,fp);
	//fprintf(fp,"Minimum Depth: 0\n");
	//fprintf(fp,"Maximum Depth: 0\n");
}

void displayRBT(FILE *fp,rbt *t) {
	displayBST(fp,t->tree);
}

void checkRBT(rbt *);               //optional











//private functions

void rbtFixup(bstNode *x,bst *t) {

	//printf("testing statement 1\n");
	int i = 1;
	while (i==1) {
		if (x == t->root) {
			//printf("testing statement 2\n");
			i = 0;
			colorBlack(t->root);
			return;
		}
		if (isBlack(parent(x))) {
			//printf("testing statement 3\n");
			i = 0;
			return;
		}
		if (hasUncle(x) && isRed(uncle(x))) {
			//printf("testing statement 4\n");
			colorBlack(parent(x));
			//printf("testing statement 5\n");
			colorBlack(uncle(x));
				//printf("testing statement 6\n");
			colorRed(grandparent(x));
			//printf("testing statement 7\n");
			x = grandparent(x);
		}
		else {
			//uncle must be black
			//printf("testing statement 8\n");
			if (!isLinear(x)) {
			//printf("testing statement 9\n");
				if (isRightChild(x)) {
					//printf("left right rotate\n");
					x = lrRotate(x);
				}
				else {
					//printf("right left rotate\n");
					x = rlRotate(x);
					//printf("testing statement 11\n");
					//displayBST(stdout,t);
					//^^this works.... do not change, but RL and LR are different
				}
			}

			colorBlack(parent(x));
					//printf("idk\n");
			colorRed(grandparent(x));
			if (isLeftChild(x)) {
						//printf("why\n");
				llRotate(x->parent,t);
				//printf("test why\n");
				//displayBST(stdout,t);
			}
			else {
					//printf("hey\n");
				rrRotate(x->parent,t);
				//printf("test hey\n");
				//displayBST(stdout,t);
			}
			//rotate parent to grandparent
			i = 0;
			return;
		}
	}
	colorBlack(t->root);
}



void *newRBTValue(void *v,void (*d)(FILE *,void *),int (*c)(void *,void *)) {

	rbtValue *newVal = malloc(sizeof(rbtValue));
	if (newVal == 0) {
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	newVal->frequency = 0;
	newVal->value = v;
	newVal->display = d;
	newVal->compare = c;
	newVal->color = 0;
	return newVal;
}

void colorBlack(bstNode *n) {
	((rbtValue *)(n->value))->color = 1;
}

void colorRed(bstNode *n) {
	((rbtValue *)(n->value))->color = 0;
}

int getFreq(bstNode *v) {
	return ((rbtValue *)(v->value))->frequency;
}

void increaseFrequency(bstNode *v) {
	((rbtValue *)(v->value))->frequency++;
}

void decreaseFrequency(bstNode *v) {
	((rbtValue *)(v->value))->frequency--;
}

int compareRBTValue(void *a,void *b) {
	rbtValue *v1 = a;
	rbtValue *v2 = b;
	// printf("trying to compare RBT values");
	return v1->compare(v1->value,v2->value);
}

void displayRBTValue(FILE *fp,void *v) {

	//print frequency if > 1
	if (v == NULL) return;
	rbtValue *val = v;
	val->display(fp,val->value);
	// if (val->frequency > 1) {
	// 	fprintf(fp,"-%d",val->frequency);
	// }
	// if (val->color == 0) {
	// 	fprintf(fp,"-R");
	// }
	// else {
	// 	fprintf(fp,"-B");
	// }
}

bool isBlack(bstNode *n) {
	if (((rbtValue *)(n->value))->color == 1) {
		return true;
	}
	else {
		return false;
		}
}

bool isRed(bstNode *n) {
	if (((rbtValue *)(n->value))->color == 0) {
		return true;
	}
	else {
		return false;
		}
}

bstNode *uncle(bstNode *n) {
	if (isLeftChild(parent(n))) {
		return rightChild(grandparent(n));
	}
	else {
		return leftChild(grandparent(n));
	}
}

bstNode *grandparent(bstNode *n) {
	return parent(n->parent);
}

bstNode *leftChild(bstNode *n) {
	return n->left;
}

bstNode *rightChild(bstNode *n) {
	return n->right;
}

bool isLeftChild(bstNode *n) {
	if (n->parent->left == n) {
		return true;
	}
	else {
		return false;
	}
}

bool isRightChild(bstNode *n) {
	if (n->parent->right == n) {
		return true;
	}
	else {
		return false;
	}
}

bstNode *parent(bstNode *n) {
	return n->parent;
}

bool isLinear(bstNode *n) {
	if (isLeftChild(n) && isLeftChild(parent(n))) {
		return true;
	}
	else if (isRightChild(n) && isRightChild(parent(n))) {
		return true;
	}
	else {
		return false;
	}
}

bool treeRoot(bstNode *n) {
	if (n->parent == n) {
		return true;
	}
	else {
		return false;
	}
}

bstNode *lrRotate(bstNode *x) {

	//implementation 1
	/*if (x->left != NULL) {
		x->left->parent = x->parent;
	}
	x->parent->right = x->left;
	x->left = x->parent;
	x->parent = x->left->parent;
	x->left->parent = x;
	x->parent->left = x;
	return x->left;*/

	//implementation 2
	if (x->left != NULL) {
		x->left->parent = x->parent;
	}
	x->parent->right = x->left;
	x->left = x->parent;
	x->parent = x->parent->parent;
	x->left->parent = x;
	x->parent->left = x;
	return x->left;
}

bstNode *rlRotate(bstNode *x) {

	//implementation 1
	/*if (x->right != NULL) {
		x->right->parent = x->parent;
	}
	x->parent->left = x->right;
	x->right = x->parent;
	x->parent = x->right->parent;
	x->right->parent = x;
	x->parent->right = x;
	return x->right;*/


	//implementation 2
	if (x->right != NULL) {
		x->right->parent = x->parent;
	}
	x->parent->left = x->right;
	x->right = x->parent;
	x->parent = x->parent->parent;
	x->right->parent = x;
	x->parent->right = x;
	return x->right;
}

void llRotate(bstNode *x,bst *t) {


	 if (x->right != NULL) {
	 	 x->right->parent = x->parent;
	 }

	 if (x->parent == t->root) {
	 	x->parent->parent = x;
	 	t->root = x;
	 }
	 else if (isLeftChild(x->parent)) {
	 	x->parent->parent->left = x;
	 }
	 else {
	 	x->parent->parent->right = x;
	 }

	 x->parent->left = x->right;
	 x->right = x->parent;
	 x->parent = x->parent->parent;
	 x->right->parent = x;

}


void rrRotate(bstNode *x,bst *t) {


	   if (x->left != NULL) {
	 	 x->left->parent = x->parent;
	 }

	 if (x->parent == t->root) {
	 	x->parent->parent = x;
	 	t->root = x;
	 }

	 else if (isLeftChild(x->parent)) {
	 	x->parent->parent->left = x;
	 }
	 else {
	 	x->parent->parent->right = x;
	 }

	 x->parent->right = x->left;
	 x->left = x->parent;
	 x->parent = x->parent->parent;
	 x->left->parent = x;
	/*x = x->parent;
	bool left = isLeftChild(x->parent);

	 if (x->left != NULL) {
	 	 x->parent->right = x->left;
	 	 x->parent->right->parent = x->parent;
	 }


	 if (left) {
	 	x->left = x->parent;
	 	x->left->parent = x;
	 	x->parent = x->parent->parent;
	 	x->parent->left = x;
	 }
	 else {
	 	x->left = x->parent;
	 	x->left->parent = x;
	 	x->parent = x->parent->parent;
	 	x->parent->right = x;
	 }*/



	 /*bstNode *temp = malloc(sizeof(bstNode));
	 temp = x->parent->parent;
	 temp->left = x->parent->parent->left;
	 temp->right = x->parent->left;

	 x->parent->parent = x->parent->parent->parent;
	 if (isLeftChild(temp)) {
	 	x->parent->parent->left = x;
	 }
	 else {
	 	x->parent->parent->right = x;
	 }
	 x->parent->left = temp;
	 temp->parent = x->parent;*/


}


bool hasUncle (bstNode *x) {
	if ((x->parent != NULL) && (x->parent->parent != NULL)) {
		if (isLeftChild(x->parent) && (x->parent->parent->right != NULL)) {
			return true;
		}
		else if (isRightChild(x->parent) && (x->parent->parent->left != NULL)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}


void updateRBTComp(rbt *t, int (*c)(void *,void *)) {
	t->compare = c;
}

void RBTinorder(rbt *t, void *val, queue *q, int (*c)(void *,void *)) {
	rbtValue *temp = newRBTValue(val,t->display,c);

	//rbtValue *myValue = newRBTValue(val, t->)
	 inorder(t->tree, temp, getRoot(t->tree), q);
}
