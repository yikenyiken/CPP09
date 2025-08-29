#include "RPN.hpp"
#include <iostream>
#include <stack>
#define SPACE ' '

using namespace std;

static int	ctoi(int c)
{
	return (c - '0');
}

static int	isoperator(int c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

static int	compute(int a, int b, int op)
{
	switch (op) {
		case '+': 
			return (a + b);
		case '-': 
			return (a - b);
		case '*': 
			return (a * b);
	}

	return (a / b);
}

RPN::RPN()
{
}

RPN::RPN(std::string formula) : formula(formula)
{
	// cout << "RPN's Parametrized Constructor called\n";
}

RPN::RPN(const RPN &other)
{
	// std::cout << "RPN's Copy Constructor called\n";

	*this = other;
}

RPN::~RPN() 
{
}


RPN	&RPN::operator = (const RPN &rhs) 
{
	formula = rhs.formula;

	return (*this);
}

void	RPN::evaluate()
{
	std::string::iterator	it;
	int						a;
	int						b;
	int						c;

	for (it = formula.begin(); it != formula.end(); ++it)
	{
		c = *it;

		if (c == SPACE)	continue ;

		if (std::isdigit(c))
			operands.push(ctoi(c));

		else if (isoperator(c) && operands.size() > 1)
		{
			b = operands.top(); operands.pop();
			a = operands.top(); operands.pop();
			c = compute(a, b, c);
			operands.push(c);
		}

		else
			break ;
	}

	if (it != formula.end() || operands.size() != 1)
	{
		std::cerr << "Error" << endl;
		exit(1);
	}

	cout << operands.top() << endl;
}