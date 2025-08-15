#ifndef mergeInsertSort_HPP
# define mergeInsertSort_HPP
# include <cstddef>
# include <vector>

# define ISODD(n) (n % 2)

template <typename T>
void	dump_pairs(std::vector<T> &pairs)
{
	for (typename std::vector<T>::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		std::cout << it->first << " - " << it->second << std::endl;
	}
}

void	dump_elements(std::vector <int> &arr)
{
	std::cout << "vector <int> elements:\n";
	for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
		std::cout << *it << std::endl;
}

template <typename T>
void	mergeInsertSort(std::vector<T> &arr)
{
	std::vector< std::pair<T&, T&> > pairs;

	for (typename std::vector<T>::iterator it = arr.begin(); it != (ISODD(arr.size()) ? --arr.end() : arr.end()); ++it)
	{
		std::pair<T&, T&> pair(*(it + 1), *(it++));;

		if (pair.first < pair.second)
			std::swap(pair.first, pair.second);

		pairs.push_back(pair);
	}

	if (ISODD(arr.size()))
	{
		std::pair<T&, T&> pair(arr.back(), arr.back());
		pairs.push_back(pair);
	}

	// static int counter;
	// if (counter)
	// 	dump_pairs(pairs);

	// ++counter;
	if (pairs.size() > 1)
		mergeInsertSort(pairs);

}

#endif