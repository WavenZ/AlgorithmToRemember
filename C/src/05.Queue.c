#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int Status;

#define OK 1
#define ERROR 0

typedef struct Node {
	ElemType data;
	struct Node* next;
}Node;

typedef struct {
	Node* Front;
	Node* Back;
}*Queue;

Queue Create_Queue(void) {
	Node* Head = (Node*)malloc(sizeof(Node));
	if (Head == NULL) return NULL;
	else {
		Head->next = NULL;
		Queue q = (Queue)malloc(sizeof(Queue));
		if (q == NULL) return NULL;
		q->Back = q->Front = Head;
		return q;
	}
}

void Queue_Push(Queue Q, ElemType data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) return;
	newNode->data = data;
	newNode->next = NULL;
	Q->Back->next = newNode;
	Q->Back = Q->Back->next;
}
int Queue_Empty(Queue Q) {
	return Q->Back == Q->Front;
}

void Queue_Pop(Queue Q) {
	if (Queue_Empty(Q)) return;
	Node* p = Q->Front;
	Q->Front = Q->Front->next;
	free(p);
}


typedef void (*callback)(ElemType);
void Queue_Traverse(Queue Q, callback visit) {
	if (Queue_Empty(Q)) return;
	Node* p = Q->Front->next;
	while (p) {
		visit(p->data);
		p = p->next;
	}
}

ElemType Queue_Front(Queue Q) {
	return Q->Front->next->data;
}

ElemType Queue_Back(Queue Q) {
	return Q->Back->data;
}

void print(ElemType data) {
	printf("%d ", data);
}

int main(void) {
	Queue Q = Create_Queue();
	for (int i = 0; i < 10; ++i)
		Queue_Push(Q, i);
	Queue_Traverse(Q, print);
	printf("\n");
	Queue_Pop(Q);
	Queue_Traverse(Q, print);
	printf("\n");
	return 0;
}
