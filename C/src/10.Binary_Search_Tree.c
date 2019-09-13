#include <stdio.h>
#include <stdlib.h>


#define ElemType int

typedef struct Node {
	ElemType key;
	struct Node *parent, *lchild, *rchild;
}Node;

typedef struct {
	Node* root;
}BST;

void INSERT(BST* T, ElemType key) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->lchild = newNode->rchild = NULL;
	if (T->root == NULL) {
		T->root = newNode;
		newNode->parent = NULL;
		return;
	}
	Node* p = T->root, *q = NULL;
	while (p) {
		q = p;
		p = (key < p->key) ? p->lchild : p->rchild;
	}
	newNode->parent = q;
	if (key < q->key)
		q->lchild = newNode;
	else q->rchild = newNode;
}



typedef void(*callback)(ElemType);
void traverse(Node* T, callback visit) {
	Node* p = T;
	if (p == NULL) return;
	traverse(p->lchild, visit);
	visit(p->key);
	traverse(p->rchild, visit);
}
void TRAVERSE(BST T, callback visit) {
	traverse(T.root, visit);
}
int SEARCH(BST T, ElemType key) {
	Node* pNode = T.root;
	while (1) {
		if (pNode == NULL) return 0;
		if (key == pNode->key) return 1;
		else if (key < pNode->key)
			pNode = pNode->lchild;
		else pNode = pNode->rchild;
	}
}

void TRANSPLANT(BST* T, Node* u, Node* v) {
	if (u->parent == NULL) {
		T->root = v;
		if(v) v->parent = NULL;
	}
	else {
		if (u->key < u->parent->key)
			u->parent->lchild = v;
		else u->parent->rchild = v;
		if(v != NULL)	// v can be NULL
			v->parent = u->parent;
	}
}

void DELETE(BST* T, ElemType key) {
	Node* pNode = T->root;
	while (1) {
		if (pNode == NULL) return 0;
		if (key == pNode->key) break;
		else if (key < pNode->key)
			pNode = pNode->lchild;
		else pNode = pNode->rchild;
	}
	if (pNode->lchild == NULL)
		TRANSPLANT(T, pNode, pNode->rchild);
	else if (pNode->rchild == NULL)
		TRANSPLANT(T, pNode, pNode->lchild);
	else {
		Node* pSucceed = pNode->rchild;
		while (pSucceed->lchild) pSucceed = pSucceed->lchild;
		if (pSucceed != pNode->rchild) {
			TRANSPLANT(T, pSucceed, pSucceed->rchild);
			pSucceed->rchild = pNode->rchild;
			pSucceed->rchild->parent = pSucceed;
		}
		TRANSPLANT(T, pNode, pSucceed);
		pSucceed->lchild = pNode->lchild;
		pSucceed->lchild->parent = pSucceed;
	}
	free(pNode);
}


void print(ElemType key) {
	printf("%d ", key);
}

int main(void) {
	BST T = {
		.root = NULL
	};
	int data[10] = { 3, 1, 8, 5, 7, 2, 9, 4, 6, 0 };
	for (int i = 0; i < 10; ++i) {
		INSERT(&T, data[i]);
		printf("Insert %d : ", data[i]);
		TRAVERSE(T, print);
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < 10; ++i) {
		DELETE(&T, data[i]);
		printf("Delete %d : ", data[i]);
		TRAVERSE(T, print);
		printf("\n");
	}

	return 0;
}


