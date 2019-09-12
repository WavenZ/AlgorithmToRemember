#include <stdio.h>
#include <limits.h>

typedef int ElemType;

#define MAX_LEN 100

#define PARENT(i)	((i+1)/2 - 1)
#define LEFT(i)		(2 * i + 1)
#define RIGHT(i)	(2 * i + 2)
#define SWAP(x,y)	(x) = (x)^(y); (y) = (x)^(y); (x) = (x)^(y);	



typedef struct{
	unsigned length;
	ElemType A[MAX_LEN];
}Priority_Queue;

void MAX_HEAPIFY(ElemType* A, int length, int i) {
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest = i;
	if (l <= length && A[l] > A[largest])
		largest = l;

	if (r <= length && A[r] > A[largest])
		largest = r;

	if (largest != i) {
		SWAP(A[i], A[largest]);
		MAX_HEAPIFY(A, length, largest);
	}
}

void BUILD_MAX_HEAP(A, length) {
	for (int i = length / 2; i > 0; --i) {
		MAX_HEAPIFY(A, length, i);
	}
}

void Priority_Queue_Push(Priority_Queue* PQ, ElemType data) {
	PQ->A[PQ->length] = data;
	PQ->length = PQ->length + 1;
	int i = PQ->length - 1;
	while (i > 0 && PQ->A[i] > PQ->A[PARENT(i)]) {
		SWAP(PQ->A[i], PQ->A[PARENT(i)]);
		i = PARENT(i);
	}
}
int Priority_Queue_Empty(Priority_Queue PQ) {
	return PQ.length == 0;
}
int Priority_Queue_Front(Priority_Queue PQ) {
	return PQ.A[0];
}
void Priority_Queue_Pop(Priority_Queue* PQ) {
	if (PQ->length == 0) return;
	PQ->A[0] = PQ->A[PQ->length - 1];
	MAX_HEAPIFY(PQ->A, PQ->length, 0);
	PQ->length = PQ->length - 1;
}

int main(void) {
	Priority_Queue PQ = {
		.length = 0,
	};
	int data[11] = {1, 3, 7, 4, 9, 2, 8, 5, 0, 6 };
	for (int i = 0; i < 10; ++i) {
		Priority_Queue_Push(&PQ, data[i]);
	}
	Priority_Queue_Pop(&PQ);
	return 0;
}
