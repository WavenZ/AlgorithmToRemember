#include <iostream>
#include <vector>

template<class T>
void insert_sort(std::vector<T>& vec) {
	int len = vec.size();
	for (int pos = 1; pos < len; ++pos) {
		T key = vec[pos];
		int i = pos - 1;
		while (i >= 0 && vec[i] > key) {
			vec[i + 1] = vec[i];
			i--;
		}
		vec[i + 1] = key;
	}
}

int main(void) {
	std::vector<int> vec = { 3, 2, 1, 7, 8, 4, 9, 0, 5, 6 };
	insert_sort(vec);
	return 0;
}
