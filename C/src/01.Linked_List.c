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



typedef void (*callback)(ElemType);
void LinkedList_Traverse(LinkedList L, callback func)
{
	if (L == NULL) return ERROR;
	Node* p = L->next;
	while (p) {
		func(p->data);
		p = p->next;
	}
	printf("\n");
}
void print(ElemType data) {
	printf("%d ", data);
}
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
	// 三指针法
	if (L == NULL) return ERROR;	// 链表未初始化
	if (L->next == NULL || L->next->next == NULL) return OK;	// 链表为空或者只有一个结点无需反转
	Node* p = L->next, * q = L->next->next, * r = L->next->next->next;
	p->next = NULL;	// 第一个结点的next置空
	while (r != NULL)	// 如果下一个结点不为空
	{
		q->next = p;	
		p = q; q = r; r = r->next;
	}
	q->next = p;
	L->next = q;
	return OK;
}

Node* LinkedList_Mid(LinkedList L)
{
	if (L == NULL) return NULL;
	Node* fast = L, * slow = L;
	while (fast != NULL && fast->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}
Node* LinkedList_KToEnd(LinkedList L, int k)
{
	if (L == NULL) return NULL;
	Node* fast = L, * slow = L;
	while (k-- && fast != NULL) {
		fast = fast->next;
	}
	while (fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}
Status LinkedList_BubbleSort(LinkedList L)
{
	if (L == NULL) return ERROR;
	Node * p = L, * q = L->next, *r = NULL;
	while (r != L->next) {
		while (q->next != NULL && q->next != r) {
			if (q->data < q->next->data) {	// 小于，指针后移
				p = q;
				q = q->next;
			}
			else {	// 大于，交换
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				p = p->next;
			}
		}
		r = q;
		p = L;
		q = L->next;
	}
	return OK;
}
void LinkedList_Merge(LinkedList L1, LinkedList L2)
{	
	// 将L2合并到L1上
	if (L1 == NULL || L2 == NULL) return ERROR;
	Node* pa = L1->next, * pb = L2->next, * p = L1;
	while (pa && pb)
	{
		if (pa->data < pb->data) {
			p->next = pa; p = pa; pa = pa->next;
		}
		else {
			p->next = pb; p = pb; pb = pb->next;
		}
	}
	p->next = pa ? pa : pb;
	free(L2);
}


int main(void) {
	int data1[] = { 4, 10, 8, 12, 19, 3, 15, 7, 16, 0 };
	int data2[] = { 2, 11, 1, 6, 5, 18, 17, 9, 14, 13 };
	LinkedList L1 = NULL, L2 = NULL;
	LinkedList_Init(&L1);
	LinkedList_Init(&L2);
	for (int i = 0; i < 10; ++i) {
		LinkedList_Push_back(L1, data1[i]);
		LinkedList_Push_back(L2, data2[i]);
	}
	LinkedList_Traverse(L1, print);
	LinkedList_Traverse(L2, print);
	LinkedList_BubbleSort(L1);
	LinkedList_BubbleSort(L2);
	LinkedList_Traverse(L1, print);
	LinkedList_Traverse(L2, print);
	LinkedList_Merge(L1, L2);
	LinkedList_Traverse(L1, print);
	return 0;
}
