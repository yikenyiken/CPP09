#include "mergeInsertionSort_v.h"

int	getLastCurrentPos(int total, int pair_size)
{
	int p = total / pair_size;
	int m = p - (ISODD(p) ? 2 : 1);
	int i = m * pair_size - 1;

	return (i);
}

// returns the position of needle in haystack
size_t	getEquivalentPos(iter needle, std::vector<iter> haystack)
{
	size_t pos = 0;

	for (iterIters it = haystack.begin(); it != haystack.end(); ++it)
	{
		if (*it == needle)
			break ;

		pos++;
	}

	return (pos);
}

std::vector<int>	js_seq_gen(unsigned int bound)
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

iterIters	getLastComp(iterIters insertBound, iter toinsert, int optlen)
{
	iterIters	comp;
	int			compStep;
	int			tries;

	tries = 0; // chopping optlen
	compStep = optlen / (2 << tries) + 1;
	comp = insertBound - compStep;

	while (compStep > 1)
	{
		compStep = optlen / (2 << ++tries) + 1;

		if (*(*comp) > *toinsert)
			comp -= compStep;
		else
			comp += compStep;
	}

	return (comp);
}

void	pairMake(std::vector<int> &vec, std::vector<iter> &winners, int pair_size, int n)
{
	int			start_offset = pair_size - 1;
	int			step = pair_size;
	int			lastCurrPos = getLastCurrentPos(n, pair_size);
	iter 		lastCurrent = vec.begin() + lastCurrPos;

	for (iter it = vec.begin() + start_offset; it != vec.end(); it += step)
	{
		iter current = it;
		iter next = current + step;

		if (*(current) > *(next))
			std::swap_ranges(current - (pair_size - 1), current + 1, next - (pair_size - 1)); // swap by size of pair so far

		winners.push_back(next);

		if (current == lastCurrent)
			break ;

		it = next;
	}

	// comparing implies the compared are forming a pair
}

void	mapStoVec(std::vector<iter> &S, std::vector<int> &vec, int pair_size)
{
	std::vector<int> temp; // acts as swap mediator

	for (std::vector<std::vector<int>::iterator>::iterator it = S.begin(); it != S.end(); ++it)
		temp.insert(temp.end(), *it - (pair_size - 1), *it + 1);

	for (std::vector<int>::iterator it = temp.begin(); it != temp.end(); ++it)
		*(vec.begin() + std::distance(temp.begin(), it)) = *it;
}