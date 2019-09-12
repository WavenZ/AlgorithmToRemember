#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void MAX_HEAPIFY(std::vector<T>& A, int i) {
	int length = A.size();
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int largest = i;
	if (r <= (length - 1) && A[r] > A[largest])
		largest = r;

	if (l <= (length - 1) && A[l] > A[largest])
		largest = l;
	if (largest != i) {
		std::swap(A[largest], A[i]);
		MAX_HEAPIFY(A, largest);
	}
}

template<typename T>
void BUILD_MAX_HEAP(std::vector<T>& A) {
	for (int i = (A.size() + 1) / 2 - 1; i >= 0; --i) {
		MAX_HEAPIFY(A, i);
	}
}

int main(void) {
	std::vector<int> V = { 1, 3, 7, 4, 9, 2, 8, 5, 0, 6 };
	std::vector<int> V2 = { 1, 3, 7, 4, 9, 2, 8, 5, 0, 6 };
	BUILD_MAX_HEAP(V);
	for (auto& v : V) {
		std::cout << v << " ";
	}
	std::cout << std::endl;
	std::make_heap(V2.begin(), V2.end());
	for (auto& v : V2) {
		std::cout << v << " ";
	}
	std::cout << std::endl;
	return 0;
}
