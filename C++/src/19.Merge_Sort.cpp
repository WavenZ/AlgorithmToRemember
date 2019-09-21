#include <iostream>
#include <vector>

template<class T>
class MergeSort {
public:
	void sort(std::vector<T>& vec) {
		merge_sort(vec, 0, vec.size() - 1);
	}
private:
	void merge_sort(std::vector<T>& vec, int start, int end) {
		if (start >= end) return;
		int mid = start + (end - start) / 2;
		merge_sort(vec, start, mid);
		merge_sort(vec, mid + 1, end);
		merge(vec, start, end);
	}
	void merge(std::vector<T>& vec, int start, int end) {
		int mid = start + (end - start) / 2;
		std::vector<T> aux;	// 辅助数组
		int i = start, j = mid + 1;
		while (i <= mid && j <= end) {
			if (vec[i] <= vec[j])
				aux.push_back(vec[i++]);
			else aux.push_back(vec[j++]);
		}
		if (i <= mid) {
			while (i <= mid)
				aux.push_back(vec[i++]);
		}
		else {
			while (j <= end)
				aux.push_back(vec[j++]);
		}
		for (int i = 0; i < aux.size(); ++i)
			vec[start + i] = aux[i];
	}
};

int main(void) {
	std::vector<int> vec = { 3, 2, 5, 1, 6, 4, 6, 1, 6, 6, 4, 1, 5, 1, 3, 1, 6, 4, 1, 4, 4};
	MergeSort<int> M;
	M.sort(vec);
	return 0;
}
