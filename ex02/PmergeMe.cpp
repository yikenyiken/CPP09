#include "PmergeMe.hpp"
#include "mergeInsertionSort.hpp"
#include <vector>

PmergeMe::PmergeMe()
{
	// std::cout << "PmergeMe's Default Constructor called\n";
}

PmergeMe::PmergeMe(const PmergeMe &other) 
{
	// std::cout << "PmergeMe's Copy Constructor called\n";

	*this = other;
}

PmergeMe::~PmergeMe() 
{
	// std::cout << "PmergeMe's Destructor called\n";
}


PmergeMe	&PmergeMe::operator = (const PmergeMe &rhs) 
{
	static_cast<void>(rhs);

	return (*this);
}

void	PmergeMe::mergeInsertionSort(std::vector<int> &vec)
{
	::mergeInsertionSort(vec);
}

void	PmergeMe::mergeInsertionSort(std::deque<int> &deq)
{
	::mergeInsertionSort(deq);
}