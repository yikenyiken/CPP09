#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av) {

	if (ac != 2)
	{
		std::cerr << "Error: Bad Usage" << std::endl;
		std::cerr << "Usage: ./btc <filename>" << std::endl;

		return (1);
	}

	BitcoinExchange	b(av[1]);

	b.evaluate();

	return 0;
}