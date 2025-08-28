#include <cstddef>
#include "mergeInsertionSort_v.h"

void	insert(std::vector<iter> &dest, iterIters insertBound, iter toInsert, int len)
{
	iterIters	lastComp;
	bool		isBehindInsertion;
	int			optlen;

	optlen = ft_pow(2, ft_log2(len + 1)) - 1;
	lastComp = getLastComp(insertBound, toInsert, optlen);

	isBehindInsertion = *toInsert < *(*lastComp);
 
	// FULL RANGE INSERT FALLBACK
	if (optlen < len && insertBound - optlen == lastComp && isBehindInsertion)
	{
		while (true)
		{
			isBehindInsertion = *toInsert < *(*lastComp);

			if (lastComp == dest.begin() || !isBehindInsertion)
				break ;

			--lastComp;
		}
	}

	if (isBehindInsertion)
		dest.insert(lastComp, toInsert);
	else
		dest.insert(lastComp + 1, toInsert);
}

void	insertLosers(std::vector<iter> &dest, std::vector<iter> &winners, int pair_size)
{
	int					bound = winners.size() - 1;
	std::vector<int>	seq = js_seq_gen(bound);
	int					prev;

	// JS SEQUENCE ITERATE
	for (iter it = seq.begin(); it != seq.end(); ++it)
	{
		if (*it <= 1)
		{
			prev = *it;
			continue ;
		}

		*it = *it > bound ? bound : *it;

		// SEQUENCE FALLBACK UNTIL PERVIOUS J(N)
		for (int windex = *it; windex != prev; --windex)
		{
			iterIters	winsert = winners.begin() + windex;
			size_t		winPosInS = getEquivalentPos(*winsert, dest);
			iterIters	sinsert = dest.begin() + winPosInS;
			iter		toinsert = *winsert - pair_size;

			insert(dest, sinsert, toinsert, winPosInS);
		}

		prev = *it;
	}
}

void	insertPend(std::vector<iter> &dest, std::vector<int> &vec, int n, int pair_size)
{
	int		nextPairSize = pair_size << 1;
	size_t	pendPos = ((n / nextPairSize) * nextPairSize) - 1 + pair_size;
	iter	pend = vec.begin() + pendPos;
	
	insert(dest, dest.end(), pend, dest.size());
}

void	mergeInsertionSort(std::vector<int> &vec)
{
	std::vector<iter> winners; // stores level winners
	std::vector<iter> S; // stores sorted level elements

	static int	level;
	int			n = vec.size();
	int			pair_size = 1 << level;
	int			loser_count = n / (pair_size << 1);
	bool		is_pend_found = n % (pair_size << 1) >= pair_size;

	if (n < 2)
		return ;

	pairMake(vec, winners, pair_size, n);

	if (n / (1 << ++level) > 1) // stop when a single pair is next
		mergeInsertionSort(vec);

	/////////////////////////    INSERTION       ///////////////////

	// add pair of smallest in winners now that it is sorted
	winners.insert(winners.begin(), *winners.begin() - pair_size);

	// MAPPING WINNERS TO S
	for (iterIters it = winners.begin(); it != winners.end(); ++it)
		S.push_back(*it);

	if (loser_count > 1) // == 1 loser already in place
		insertLosers(S, winners, pair_size);

	if (is_pend_found)
		insertPend(S, vec, n, pair_size);

	mapStoVec(S, vec, pair_size);
}
