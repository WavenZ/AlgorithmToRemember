#include <iostream>
#include <vector>

template<class T>
int lower_bound(const std::vector<T>& vec, const T& val) {
	int low = 0, high = vec.size();
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (vec[mid] < val)
			low = mid + 1;
		else high = mid;
	}
	return high;
}

template<class T>
int upper_bound(const std::vector<T>& vec, const T& val) {
	int low = 0, high = vec.size();
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (vec[mid] <= val)
			low = mid + 1;
		else high = mid;
	}
	return high;
}

template<class T>
bool binary_search(const std::vector<T>& vec, const T& val) {
	int pos = lower_bound(vec, val);
	return (pos != vec.size() && vec[pos] <= val);
}

int main() {
	std::vector<int> vec = { 1, 2, 3, 5, 6, 6, 6, 6, 6, 7, 8, 9 };
	for (int i = 0; i < 11; ++i) {
		std::cout << "search " << i << " : ";
		std::cout << lower_bound(vec, i) << " ";
		std::cout << upper_bound(vec, i) << " ";
		std::cout << binary_search(vec, i) << std::endl;
	}
	return 0;
}
