#include <stdio.h>		// printf
#include <stdlib.h>		// malloc-free

#define OK 1
#define ERROR 0


typedef char Status;
typedef int ElemType;


typedef struct Node{
	ElemType data;
	struct Node* next;
}Node, *LinkedList;

Status LinkedList_Init(LinkedList* L) {
	// 链表初始化
	*L = (LinkedList)malloc(sizeof(Node));
	if (!(*L)) return ERROR;
	else {
		(*L)->next = NULL;
	}
	return OK;
}
Status LinkedList_Push_back(LinkedList L, ElemType data) {
	// 在链表最后面插入一个结点
	if (L == NULL) return ERROR;
	Node* p = L;
	while (p->next) 
		p = p->next;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) return ERROR;
	else {
		newNode->data = data;
		newNode->next = NULL;
		p->next = newNode;
	}
	return OK;
}
Status LinkedList_Push_front(LinkedList L, ElemType data) {
	// 在链表最前面插入一个结点
	if (L == NULL) return ERROR;
	Node* p = L;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) return ERROR;
	else {
		newNode->next = L->next;
		newNode->data = data;
		L->next = newNode;
	}
	return OK;
}
Status LinkedList_Insert(LinkedList L, int i, ElemType data) {
	// 在位置i处插入一个结点
	if (L == NULL) return ERROR;
	Node* p = L;
	if (i < 0) return ERROR;	// i < 0
	for (int j = 0; j < i; ++j) {
		if (p->next == NULL) return ERROR; // i > length
		else p = p->next;
	}
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) return ERROR;
	else {
		newNode->next = p->next;
		newNode->data = data;
		p->next = newNode;
	}
	return OK;
}
Status LinkedList_Delete(LinkedList L, int i) {
	if (L == NULL) return ERROR;
	Node* p = L;
	if (i < 0) return ERROR;
	for (int j = 0; j < i; ++j) {
		if (p->next == NULL) return ERROR;
		else p = p->next;
	}
	if (p->next == NULL) return ERROR;
	Node* q = p->next;
	p->next = p->next->next;
	free(q);
	p = NULL;
	return OK;
}
Status LinkedList_Reverse(LinkedList L) {

}


typedef void (*callback)(ElemType);
void LinkedList_Traverse(LinkedList L, callback func)
{
	if (L == NULL) return ERROR;
	Node* p = L->next;
	while (p) {
		func(p->data);
		p = p->next;
	}
}


void print(ElemType data) {
	printf("%d ", data);
}
int main(void) {
	LinkedList L = NULL;
	// LinkedList_Init(&L);
	for (int i = 0; i < 10; ++i) {
		LinkedList_Push_back(L, i);
	}
	LinkedList_Traverse(L, print);
	printf("\n");
	LinkedList_Delete(L, 9);
	LinkedList_Traverse(L, print);
	printf("\n");
	LinkedList_Insert(L, 0, 9);
	LinkedList_Traverse(L, print);
	printf("\n");
	return 0;
}
