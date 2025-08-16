#include <vector>
#include <iostream>
#define ISODD(n) (n % 2)

using namespace std;

int	get_last_current_winner(int total, int pair_size)
{
	int p = total / pair_size;
	int m = p - (ISODD(p) ? -2 : -1);
	int i = m * pair_size - 1;

	return (i);
}

void	mergeInsertionSort(std::vector<int> vec)
{

	cout << "vec before pair sort\n";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << ", ";
	} cout << endl;

	static int	level;
	int n = vec.size();
	int pair_size = 1 << level;
	int start_offset = pair_size - 1;
	int step = pair_size;
	std::vector<int>::iterator last_current_winner = vec.begin() + get_last_current_winner(n, pair_size);
	
	// logs
	cout << "size: " << n << endl;
	cout << "level: " << level << endl;
	cout << "pair_size: " << pair_size << endl;
	cout << "start_offset: " << start_offset << endl;
	cout << "step: " << step << endl;
	cout << "last_current_winner: " << *last_current_winner << endl; 
	// cout << "get_last_current_winner: " << get_last_current_winner(n, pair_size) << endl;
	//

	cout << endl;
	for (std::vector<int>::iterator it = vec.begin() + start_offset; it != vec.end(); it += step)
	{
		std::vector<int>::iterator next_winner = it + step;
		std::vector<int>::iterator current_winner = it;
		cout << "current_winner " << *(next_winner) << " - next_winner "  << *(current_winner) << endl;

		if (*(current_winner) > *(next_winner))
			std::swap_ranges(current_winner - (pair_size - 1), current_winner + 1, next_winner); // swap by pair size
	
		if (current_winner == last_current_winner)
			break ;

		it = next_winner;
	}

	cout << endl;
	cout << "vec after pair sort: " << endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << endl;
	}

	++level;

	if (n / (1 << level) > 1) // stop when a single pair is left
		mergeInsertionSort(vec);

	// insertion logic here
}