#include <iostream>
#include "mergeInsertSort.hpp"

int main() {
	
	std::vector<int> intvec;
	int arr[] = {9, 7, 8, 6, 2};
	// int arr[] = {9, 7, 8, 6, 2, 3, 11, 18, 10};

	for(size_t i = 0; i < sizeof(arr) / sizeof(*arr); ++i)
		intvec.push_back(arr[i]);

	mergeInsertSort(intvec);

	dump_elements(intvec);

	return 0;
}