#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class HeapSort {
public:
	HeapSort() = default;
	HeapSort(const HeapSort& other) = delete;
	HeapSort& operator=(const HeapSort& other) = delete;
	void sort(std::vector<int>& vec) {
		length = vec.size();
		build_max_heap(vec);
		for (int i = vec.size() - 1; i > 0; --i) {
			std::swap(vec[0], vec[i]);
			length--;
			max_heapify(vec, 0);
		}
	}
private:
	int length;
	void max_heapify(std::vector<T>& A, int i) {
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int largest = i;
		if (r <= (length - 1) && A[r] > A[largest])
			largest = r;
		if (l <= (length - 1) && A[l] > A[largest])
			largest = l;

		if (largest != i) {
			std::swap(A[largest], A[i]);
			max_heapify(A, largest);
		}
	}
	void build_max_heap(std::vector<T>& A) {
		for (int i = (A.size() + 1) / 2 - 1; i >= 0; --i) {
			max_heapify(A, i);
		}
	}
};


int main(void) {
	std::vector<int> V = { 1, 3, 7, 4, 9, 2, 8, 5, 0, 6 };
	HeapSort<int> H;
	H.sort(V);
	return 0;
}
