#include "PmergeMe.hpp"
#include <_ctype.h>
#include <cerrno>
#include <climits>
#include <iostream>
#include <sys/_types/_timeval.h>
#include <sys/time.h>
#include <vector>
#include <deque>

// time in microseconds
size_t	getTime()
{
	size_t time;
	struct	timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		perror("gettimeofday");
		exit(1);
	}

	time = (tv.tv_sec * 1000000) + tv.tv_usec;

	return (time);
}

bool	isnumeric(std::string s)
{
	for (std::string::iterator it = s.begin(); it != s.end(); ++it)
	{
		int c = *it;

		if (!std::isdigit(c))
			return (false);
	}

	return (true);
}

void	parse(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Not Enough Arguments" << std::endl;
		exit(1);
	}

	for (int i = 1; i < ac; ++i)
	{
		if (!isnumeric(av[i]) || std::strtol(av[i], NULL, 10) > INT_MAX || errno == ERANGE)
		{
			std::cerr << "Error" << std::endl;
			exit(1);
		}
	}
}

int main(int ac, char **av) {

	PmergeMe			hero;
	std::vector<int>	vec;
	std::deque<int>		deq;
	size_t				timeBeforeSort;
	double				timeSpent;

	parse(ac, av);

	std::cout << "Before: ";
	for (int i = 1; i < ac; ++i)
		std::cout << av[i] << " ";
	std::cout << std::endl;

	//////// DEQUE ////////

	timeBeforeSort = getTime();

	for (int i = 1; i < ac; ++i)
		deq.push_back(std::atoi(av[i]));

	hero.mergeInsertionSort(deq);

	timeSpent = (getTime() - timeBeforeSort) / static_cast<double>(1000);

	std::cout << "After: ";
	for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << timeSpent << " ms" << std::endl;

	//////// VECTOR ////////

	timeBeforeSort = getTime();

	for (int i = 1; i < ac; ++i)
		vec.push_back(std::atoi(av[i])); // protect conversion ?

	hero.mergeInsertionSort(vec);

	timeSpent = (getTime() - timeBeforeSort) / static_cast<double>(1000);

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << timeSpent << " ms" << std::endl;
}