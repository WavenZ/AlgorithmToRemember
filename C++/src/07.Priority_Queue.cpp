#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Priority_Queue {
private:
	std::vector<T> A;
private:
	void max_heapify(int i) {
		unsigned l = 2 * i + 1;
		unsigned r = 2 * i + 2;
		int largest = i;
		if (l < A.size() && A[l] > A[largest])
			largest = l;
		if (r < A.size() && A[r] > A[largest])
			largest = r;
		if (largest != i) {
			std::swap(A[i], A[largest]);
			max_heapify(largest);
		}
	}
	void build_max_heapify() {
		for (int i = A.size() / 2 - 1; i >= 0; --i) {
			max_heapify(i);
		}
	}
	int parent(int i) {
		return (i + 1) / 2 - 1;
	}
public:
	Priority_Queue(std::vector<T> V) : A(V) {
		build_max_heapify();
	}
	void push(T data) {
		A.push_back(data);
		int i = A.size() - 1;
		while (i > 0 && A[i] > A[parent(i)]) {
			std::swap(A[i], A[parent(i)]);
			i = parent(i);
		}
	}
	bool empty() {
		return A.size() == 0;
	}
	void pop() {
		if (A.size() == 0) return;
		A[0] = A[A.size() - 1];
		max_heapify(0);
		A.pop_back();
	}
	T front() {
		return A[0];
	}
};

int main(void) {
	std::vector<int> V = { 1, 3, 7, 4, 9, 2, 8, 5, 0, 6 };
	Priority_Queue<int> PQ(V);
	PQ.push(10);
	std::cout << PQ.front() << std::endl;
	PQ.pop();
	std::cout << PQ.front() << std::endl;
	std::make_heap(V.begin(), V.end());
	return 0;
}
