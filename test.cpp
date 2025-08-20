#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>

#define SIZE  6

int	ft_log2(int x)
{
	int count = 0;

	while (x > 1)
	{
		x = x / 2;
		++count;
	}

	return (count);
}

using namespace std;

int main() {
  cout << ft_log2(32) << endl;

  std
}