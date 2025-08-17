#include <iostream>
#include <array>
#include <vector>


using namespace std;

void	mergeInsertionSort(std::vector<int> &vec);

int main() {
	
	std::array<int, 7> arr = {0, 9, 8, 2, 3, 1, 6};
	std::vector<int> vec;

	for (std::array<int, 10>::iterator it = arr.begin(); it != arr.end(); ++it)
		vec.push_back(*it);
	
	mergeInsertionSort(vec);

	return 0;
}