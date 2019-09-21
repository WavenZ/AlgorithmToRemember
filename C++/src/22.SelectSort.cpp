#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
void select_sort(std::vector<T>& vec) {
	int len = vec.size();
	for (int i = 0; i < len; ++i) {
		int max_index = std::min_element(vec.begin() + i, vec.end()) - vec.begin();
		std::swap(vec[i], vec[max_index]);
	}
}


int main(void) {
	std::vector<int> vec = { 5, 2, 1, 4, 4, 3, 1, 5, 9, 7, 4, 6, 8, 9, 7, 4, 3 };
	select_sort(vec);
	return 0;
}
