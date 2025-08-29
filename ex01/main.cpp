#include <iostream>
#include "RPN.hpp"

int main(int ac, char **av) {
	
	if (ac != 2)
	{
		std::cerr << "Usage: ./RPN <formula>" << std::endl;
		return (1);
	}

	RPN	rpn(av[1]);
	
	rpn.evaluate();

	return (0);
}