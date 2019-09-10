#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef char Status;

typedef struct Node {
	ElemType data;
	struct Node* next;
}Node, *Stack;


int Stack_Empty(Stack S) {
	return S->next == NULL;
}

Stack Create_Stack(void) {
	Stack p = (Node*)malloc(sizeof(Node));
	if (p == NULL) return NULL;
	else {
		p->next = NULL;
		return p;
	}
}
Status Stack_Push(Stack S, ElemType data) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL) return ERROR;
	else {
		p->data = data;
		p->next = S->next;
		S->next = p;
	}
}

Status Stack_Top(Stack S, ElemType* ret) {
	if (S->next == NULL) {
		printf("Stack Empty !\n");
		return ERROR;
	}
	else
	{
		*ret = S->next->data;
		return OK;
	}
}
Status Stack_Pop(Stack S) {
	if (S->next == NULL) {
		printf("Stack Empty !\n");
		return ERROR;
	}
	else {
		S->next = S->next->next;
		return OK;
	}
}

typedef void(*callback)(ElemType);
void Stack_Traverse(Stack S, callback visit) {
	Node* p = S->next;
	while (p) {
		visit(p->data);
		p = p->next;
	}
}
void print(ElemType data) {
	printf("%d ", data);
}
int main(void) {
	Stack S = Create_Stack();
	for(int i = 0; i < 10; ++i)
		Stack_Push(S, i);
	Stack_Traverse(S, print);
	printf("\n");
	ElemType top;
	Stack_Top(S, &top);
	printf("%d\n", top);
	for (int i = 0; i <= 10; ++i)
		Stack_Pop(S);
	Stack_Traverse(S, print);
	return 0;
}
