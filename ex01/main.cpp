#include <iostream>

#define ADDOP '+'
#define SUBTROP '-'

using namespace std;

#include <stack>



int	calc(std::stack<int> &a, std::stack<int> &b)
{
	
}

int main() {
	
	std::stack<int> a;
	std::stack<char> b;

	// - +
	// 8 3 9
	// 9 3 + 8 -

	// (9 + 3) - 8
	// 12 - 8 = 4

	// going and pushing ...
	// 

	a.push(9);
	a.push(3);
	a.push(8);

	b.push(ADDOP);
	b.push(SUBTROP);
	return 0;
}