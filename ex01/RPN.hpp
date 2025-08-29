#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>

class RPN
{
	private:
		std::stack<int>	operands;
		std::string		formula;

	public:
		RPN();
		RPN(std::string formula);
		RPN(const RPN &other);
		~RPN();

		RPN	&operator = (const RPN &rhs);

		void			evaluate();
};

#endif