#include <stdio.h>
#include <limits.h>

typedef int ElemType;


#define PARENT(i)	(i/2)
#define LEFT(i)		(2 * i)
#define RIGHT(i)	(2 * i + 1)
#define SWAP(x,y)	(x) = (x)^(y); (y) = (x)^(y); (x) = (x)^(y);	


void MAX_HEAPIFY(ElemType* A, int length, int i) {
	int l = LEFT(i);
	int r = RIGHT(i);
	ElemType largest = i;
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

int main(void) {
	int A[11] = { INT_MAX, 1, 3, 7, 4, 9, 2, 8, 5, 0, 6 };
	BUILD_MAX_HEAP(A, 10);
	for (int i = 1; i <= 10; ++i) {
		printf("%d ", A[i]);
	}
	printf("\n");
	return 0;
}
