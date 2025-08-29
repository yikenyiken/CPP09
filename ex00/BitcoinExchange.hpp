#ifndef BitcoinExchange_HPP
# define BitcoinExchange_HPP

# include <exception>
# include <fstream>
# include <list>
# include <map>
# include <string>

class BitcoinExchange
{
	private:
		typedef 		std::map<std::string, std::string> strmap;
		typedef 		strmap::iterator iterator;
		typedef 		std::pair<std::string, std::string> strpair;
		typedef			std::list<strpair> pairlist;
		typedef			pairlist::iterator l_iterator;

		std::ifstream	dbfile;
		std::ifstream	infile;
		strmap			db;
		pairlist		list;
		float			amount; // value in input
		std::string		key;

		void			readFileIntoMap();
		void			readFileIntoList();

		void			lineParse(l_iterator &line);
		void			parseDate(std::string date);
		void			parseValue(std::string value);
		float			retrieveExchangeRate();

		class			ParseErrorException : public std::exception
		{
			private:
				char const	*message;

			public:
				ParseErrorException(char const *msg);

				char const	*what() const throw();
		};

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange	&operator = (const BitcoinExchange &rhs);
		BitcoinExchange(std::string infilename);
		~BitcoinExchange();

		void			evaluate();

};

#endif