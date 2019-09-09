#include <stdio.h>		// printf
#include <stdlib.h>		// malloc-free

#define OK 1
#define ERROR 0


typedef char Status;
typedef int ElemType;


typedef struct Node {
	ElemType data;
	struct Node* prev;
	struct Node* next;
}Node, * DoublyLinkedList;



typedef void (*callback)(ElemType);
void DoublyLinkedList_Traverse(DoublyLinkedList L, callback visit)
{
	if (L == NULL) return ERROR;
	Node* p = L->next;
	while (p) {
		visit(p->data);
		p = p->next;
	}
	printf("\n");
}

Status DoublyLinkedList_Init(DoublyLinkedList* L) {
	// 链表初始化
	*L = (DoublyLinkedList)malloc(sizeof(Node));
	if (!(*L)) return ERROR;
	else {
		(*L)->next = NULL;
	}
	return OK;
}
Status DoublyLinkedList_Push_back(DoublyLinkedList L, ElemType data) {
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
		newNode->prev = p;
		p->next = newNode;
	}
	return OK;
}
Status DoublyLinkedList_Push_front(DoublyLinkedList L, ElemType data) {
	// 在链表最前面插入一个结点
	if (L == NULL) return ERROR;
	Node* p = L;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) return ERROR;
	else {
		newNode->data = data;
		newNode->next = L->next;
		newNode->prev = L;
		L->next->prev = newNode;
		L->next = newNode;
	}
	return OK;
}
Status DoublyLinkedList_Insert(DoublyLinkedList L, int pos, ElemType data) {
	if (L == NULL || pos < 0) return ERROR;
	Node* p = L;
	while (pos-- && p->next != NULL) {
		p = p->next;
	}
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) return ERROR;
	else {
		newNode->data = data;
		newNode->next = p->next;
		newNode->prev = p;
		if (p->next) p->next->prev = newNode;
		p->next = newNode;
	}

}
Status DoublyLinkedList_Delete(DoublyLinkedList L, int pos) {
	if (L == NULL || pos < 0) return ERROR;
	Node* p = L->next;
	while (pos-- && p != NULL) {
		p = p->next;
	}
	if (p == NULL) return OK;
	else{
		if(p->prev)
			p->prev->next = p->next;
		if (p->next)
			p->next->prev = p->prev;
	}
}

void print(ElemType data) {
	printf("%d ", data);
}

int main(void) {
	DoublyLinkedList L;
	DoublyLinkedList_Init(&L);
	for (int i = 0; i < 10; ++i)
		DoublyLinkedList_Push_back(L, i);
	DoublyLinkedList_Insert(L, 0, 250);
	DoublyLinkedList_Insert(L, 11, 250);
	DoublyLinkedList_Traverse(L, print);
	
	DoublyLinkedList_Delete(L, 0);
	DoublyLinkedList_Traverse(L, print);
	
	DoublyLinkedList_Delete(L, 10);
	DoublyLinkedList_Traverse(L, print);
	return 0;
}
