#include <iostream>
#include <vector>
using namespace std;

int main() {
	
	std::vector <int> vec;

	vec.push_back(1);
	vec.push_back(2);

	std::vector<int>::iterator it = vec.begin();

	std::swap_ranges(it, --vec.end(), --vec.end());

	cout << "bgein after swap " << *it;

	return 0;
}