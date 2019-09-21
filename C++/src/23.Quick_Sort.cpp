#include <iostream>
#include <vector>
#include <random>

template<class T>
class QuickSort {
public:
	void sort(std::vector<T>& vec) {
		quick_sort(vec, 0, vec.size() - 1);
	}
private:
	void quick_sort(std::vector<int>& vec, int start, int end) {
		if (start >= end) return;
		int pos = randomized_patition(vec, start, end);
		quick_sort(vec, start, pos - 1);
		quick_sort(vec, pos + 1, end);
	}
	int patition(std::vector<int>& vec, int start, int end) {
		int pivot = vec[end];
		int pos = start;
		for (int i = start; i < end; ++i) {
			if (vec[i] < pivot) {
				std::swap(vec[pos++], vec[i]);
			}
		}
		std::swap(vec[pos], vec[end]);
		return pos;
	}
	int randomized_patition(std::vector<int>& vec, int start, int end) {
		std::default_random_engine rand_engine;
		std::uniform_int_distribution<unsigned> uniform_rand(start, end);
		std::swap(vec[end], vec[uniform_rand(rand_engine)]);
		int pivot = vec[end];
		int pos = start;
		for (int i = start; i < end; ++i) {
			if (vec[i] < pivot) {
				std::swap(vec[pos++], vec[i]);
			}
		}
		std::swap(vec[pos], vec[end]);
		return pos;
	}
};



int main(void) {
	std::vector<int> vec = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 8 };
	QuickSort<int> Q;
	Q.sort(vec);
	return 0;
}
