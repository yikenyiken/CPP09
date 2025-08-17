#include <climits>
#include <exception>
#include <vector>
#include <iostream>
#define ISODD(n) (n % 2)

using namespace std;

int	get_last_current_winner(int total, int pair_size)
{
	int p = total / pair_size;
	int m = p - (ISODD(p) ? 2 : 1);
	int i = m * pair_size - 1;

	return (i);
}

int	j(unsigned int x)
{
	if (!x)
		return (0);

	if (x == 1)
		return (1);
	
	return (j(x - 1) + 2 * j(x - 2));
}

std::vector<int>	js_seq_gen(int bound)
{
	std::vector<int> seq;

	for (unsigned int i = 0; true; ++i)
	{
		unsigned int jn = j(i);

		if (jn != 0 && jn != 1)
			seq.push_back(jn);

		if (jn >= bound)
			break;
	}

	return (seq);
}

void	mergeInsertionSort(std::vector<int> &vec)
{
	std::vector<std::vector<int>::iterator> losers;

	cout << endl; cout << "vec before pair sort\n";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << ", ";
	} cout << endl;

	static int	level;
	int n = vec.size();
	int pair_size = 1 << level;
	int start_offset = pair_size - 1;
	int step = pair_size;
	int	loser_count = n / (pair_size << 1);
	bool is_pend_found = n % (pair_size << 1);
	std::vector<int>::iterator last_current_winner = vec.begin() + get_last_current_winner(n, pair_size);

	// logs
	cout << "size: " << n << endl;
	cout << "level: " << level << endl;
	cout << "pair_size: " << pair_size << endl;
	cout << "start_offset: " << start_offset << endl;
	cout << "step: " << step << endl;
	cout << "last_current_winner: " << *last_current_winner << endl;
	cout << "loser_count: " << loser_count << endl;
	cout << "is_pend_found: " << is_pend_found << endl;

	int smallest_winner = INT_MAX; // ff

	cout << endl;
	for (std::vector<int>::iterator it = vec.begin() + start_offset; it != vec.end(); it += step)
	{
		std::vector<int>::iterator current_winner = it;
		std::vector<int>::iterator next_winner = current_winner + step;
		cout << "current_winner " << *(current_winner) << " - next_winner "  << *(next_winner) << endl;

		if (*(current_winner) > *(next_winner))
			std::swap_ranges(current_winner - (pair_size - 1), current_winner + 1, next_winner - (pair_size - 1)); // swap by pair size
	
		if (smallest_winner > *next_winner)
			smallest_winner = *next_winner;

		if (current_winner == last_current_winner)
			break ;

		it = next_winner;
	}

	++level;

	cout << endl; cout << "losers: " << endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it += 1 << level)
	{
		cout << *it << ", ";
		losers.push_back(it);

		if (it == vec.begin() + (loser_count * (1 << level)) - (1 << level))
			break ;
	} cout << endl;

	// comparing implies the compared are forming a pair
	// the above is the equivalent of creating pairs of size pair_size * 2

	if (n / (1 << level) > 1) // stop when a single pair is left
		mergeInsertionSort(vec);

	cout << "## level with pair size " << pair_size << " ##" << endl;

	cout << "smallest winner " << smallest_winner << endl;

	cout << "vec after recursion: " << endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		cout << *it << endl;

	// insertion here

	cout << "loser_count: " << loser_count << endl;
	cout << "is_pend_found: " << is_pend_found << endl;

	if (loser_count != 1) // == 1 loser already in place
	{

		
	}

	if (is_pend_found)
		;// insert pend
}