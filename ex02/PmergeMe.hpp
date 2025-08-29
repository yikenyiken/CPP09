#ifndef PmergeMe_HPP
# define PmergeMe_HPP
# include <deque>
# include <vector>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		~PmergeMe();

		PmergeMe		&operator = (const PmergeMe &rhs);
		static void		mergeInsertionSort(std::vector<int> &);
		static void		mergeInsertionSort(std::deque<int> &);
};

#endif