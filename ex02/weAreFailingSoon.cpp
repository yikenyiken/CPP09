#include <algorithm>
#include <climits>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <vector>
#include <iostream>
#define ISODD(n) (n % 2)

using namespace std;

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

int	ft_pow(int x, int y)
{
	int res = x;

	while (y - 1)
	{
		res *= x;
		--y;
	}

	return (res);
}

int	getLastCurrent(int total, int pair_size)
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

		seq.push_back(jn);

		if (jn >= bound)
			break;
	}

	return (seq);
}

void	mergeInsertionSort(std::vector<int> &vec)
{
	std::vector<std::vector<int>::iterator> winners; // stores level winners

	cout << endl;

	static int	level;
	int n = vec.size();
	int pair_size = 1 << level;
	int start_offset = pair_size - 1;
	int step = pair_size;
	int	loser_count = n / (pair_size << 1);
	bool is_pend_found = n % (pair_size << 1);
	std::vector<int>::iterator lastCurrent = vec.begin() + getLastCurrent(n, pair_size);

	// logs
	cout << "pair_size: " << pair_size << endl;
	cout << "step: " << step << endl;
	cout << "loser_count: " << loser_count << endl;
	cout << "is_pend_found: " << is_pend_found << endl;

	for (std::vector<int>::iterator it = vec.begin() + start_offset; it != vec.end(); it += step)
	{
		std::vector<int>::iterator current = it;
		std::vector<int>::iterator next = current + step;
		
		if (*(current) > *(next))
			std::swap_ranges(current - (pair_size - 1), current + 1, next - (pair_size - 1)); // swap by size of pair so far

		winners.push_back(next);

		if (current == lastCurrent)
			break ;

		it = next;
	}

	cout << "vec after pair sort: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		cout << *it << ", ";
	cout << endl;
	// comparing implies the compared are forming a pair

	++level;


	if (n / (1 << level) > 1) // stop when a single pair is next
		mergeInsertionSort(vec);




	/////////////////////////    INSERTION       ///////////////////





	cout << endl; cout << "## insertion for pair_size " << pair_size << endl;

	// add pair of smallest in winners now that it is sorted
	winners.insert(winners.begin(), *winners.begin() - pair_size);

	if (loser_count != 1) // == 1 loser already in place
	{
		cout << "winners before insertion: ";
		for (std::vector<std::vector<int>::iterator>::iterator it = winners.begin(); it != winners.end(); ++it)
			cout << *(*it) << ", ";
		cout << endl;

		size_t				bound = winners.size() - 1;
		int					insertCount = 0;
		std::vector<int>	seq = js_seq_gen(bound);
		int					prev;

		// SEQUENCE ITERATE
		for (std::vector<int>::iterator it = seq.begin(); it != seq.end(); ++it)
		{
			if (*it <= 1)
			{
				prev = *it;
				continue ;
			}

			// SEQUENCE FALLBACK UNTIL PERVIOUS J(N)
			for (int windex = *it + insertCount; windex != prev;)
			{
				int													optLen = ft_pow(2, ft_log2(windex + insertCount + 1)) - 1; // requirement: fallback if toInsert < first at optLen of winners
				int													tries;
				int													compStep;
				bool												isBehindInsertion;
				std::vector<std::vector<int>::iterator>::iterator	winsert = winners.begin() + windex;
				std::vector<int>::iterator							toinsert = *(winsert) - pair_size;
				std::vector<std::vector<int>::iterator>::iterator	comp;

				windex = windex > bound ? bound : windex;

				cout << "starting at j(n): " << *it << endl;
				cout << "inserting pair of winners' member at index: " << windex << endl;
				cout << "inserting: " << *toinsert << endl;		
				cout << "optimal length: " << optLen  << endl;




				tries = 0; // chopping optLen
				compStep = optLen / (2 << tries) + 1;
				comp = winsert - compStep;

				while (compStep > 1)
				{
					cout << "comapring " << *toinsert << " to " << *(*(comp)) << endl; // comp out of bounds

					compStep = optLen / (2 << ++tries) + 1;

					if (*(*comp) > *toinsert)
						comp -= compStep;
					else
						comp += compStep;
				}

				cout << "last compared to: " << *(*comp) << endl;
				// FOUND THE LAST TO COMPARE TO

				isBehindInsertion = *toinsert < *(*comp);

				if (isBehindInsertion)
				{
					cout << "inserting range " << *(toinsert - (pair_size - 1)) << "-" << *(toinsert + 1) << " behind " << *(*comp) << endl;

					std::rotate(*comp, toinsert - (pair_size - 1), toinsert + 1);
				}
				else
				{
					cout << "inserting range " << *(toinsert - (pair_size - 1)) << "-" << *(toinsert + 1) << " after " << *(*comp) << endl;
				
					std::rotate(*comp + 1, toinsert - (pair_size - 1), toinsert + 1);
				}

				cout << "winners before re-arrange: ";
				for (std::vector<std::vector<int>::iterator>::iterator it = winners.begin(); it != winners.end(); ++it)
					cout << *(*it) << ", ";
				cout << endl;

				for (std::vector<std::vector<int>::iterator>::iterator it = isBehindInsertion ? comp : comp + 1; it != winsert; ++it) // re-arrange winners
				{
					cout << "started shifting from: " << *(*it) << endl;
					*it = *it + pair_size;
				}

				cout << "winners after re-arrange: ";
				for (std::vector<std::vector<int>::iterator>::iterator it = winners.begin(); it != winners.end(); ++it)
					cout << *(*it) << ", ";
				cout << endl;

				if (isBehindInsertion)
					winners.insert(comp, *comp - pair_size);
				else
					winners.insert(comp + 1, *comp + pair_size);


				cout << "winners after insertion: ";
				for (std::vector<std::vector<int>::iterator>::iterator it = winners.begin(); it != winners.end(); ++it)
					cout << *(*it) << ", ";
				cout << endl;

				++insertCount;
				++prev;
			}
			prev += insertCount; // not sure about this
		}
	}


	if (is_pend_found)
		;// insert pend
}
