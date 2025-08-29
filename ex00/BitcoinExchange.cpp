#include "BitcoinExchange.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#define DB "data.csv"
#define COMMA ','
#define PIPE '|'
#define SPACE ' '
#define HYPHEN '-'
#define DOT '.'
#define FST_HYPHEN 4
#define SEC_HYPHEN 7
#define DATELEN 10
#define BASE 10
#define DOTMAX 1
#define MONDAY 2
#define MONTHMAX 12
#define DAYMAX 31
#define TOIGNORE "date | value"

static std::string	fixedNoTrailingZeros(float val, int maxPrecision = 2)
{
	std::ostringstream	oss;
	std::string			str;

	oss << std::fixed << std::setprecision(maxPrecision) << val;

	str = oss.str();

	if (str.find('.') != std::string::npos)
	{
			str.erase(str.find_last_not_of('0') + 1);

			if (str[str.length()-1] == '.')
				str.erase(str.length()-1);
	}
	return (str);
}

void	BitcoinExchange::readFileIntoList()
{
	std::string	line;
	size_t	pos;

	while (!infile.eof())
	{
		strpair	pair;
		
		std::getline(infile, line);

		if (line == TOIGNORE)
			continue ;

		if (line.empty())
		{
			list.push_back(pair);
			continue ;
		}

		pos = line.find(PIPE);

		if (line.length() == 1)
		{
			pair.first = line;
			list.push_back(pair);
			continue ;
		}

		if (pos == std::string::npos)
			pos = 0;

		pair.first = line.substr(0, pos++);
		pair.second = line.substr(pos, line.length() - pos);

		list.push_back(pair);
	}
}

void	BitcoinExchange::readFileIntoMap()
{
	std::string	line;
	size_t	pos;

	while (!dbfile.eof())
	{
		strpair	pair;
		
		std::getline(dbfile, line);

		pos = line.find(COMMA);

		if (line.empty())
			continue ;

		if (pos == std::string::npos)
			pos = 0;

		pair.first = line.substr(0, pos++);
		pair.second = line.substr(pos, line.length() - pos);

		db.insert(pair);
	}
}

void	BitcoinExchange::parseDate(std::string date)
{
	// A valid date will always be in the following format: Year-Month-Day
	std::string	month;
	std::string	day;
	std::string	year;
	long	lyear;
	long	lmonth;
	long	lday;

	for (std::string::iterator it = date.begin(); it != date.end(); ++it)
	{
		if (!isdigit(*it) && *it != HYPHEN)
			throw ParseErrorException("Error: bad date");
		if ((std::distance(date.begin(), it) == FST_HYPHEN
			|| std::distance(date.begin(), it) == SEC_HYPHEN) && *it != HYPHEN)
			throw ParseErrorException("Error: wrong date format");
	}

	if (date.length() < DATELEN)
		throw ParseErrorException("Error: incomplete date");
	if (date.length() > DATELEN)
		throw ParseErrorException("Error: wrong date format");

	year = date.substr(0, FST_HYPHEN);
	month = date.substr(FST_HYPHEN + 1, MONDAY);
	day = date.substr(SEC_HYPHEN + 1, MONDAY);
	lyear = std::strtol(year.c_str(), NULL, BASE);
	lmonth = std::strtol(month.c_str(), NULL, BASE);
	lday = std::strtol(day.c_str(), NULL, BASE);

	if (lyear <= 0)
		throw ParseErrorException("Error: our of range year");

	if (lmonth > MONTHMAX || lmonth <= 0)
		throw ParseErrorException("Error: our of range month");

	if (lday > DAYMAX || lday <= 0)
		throw ParseErrorException("Error: out of range day");

	key = date;
}

void	BitcoinExchange::parseValue(std::string value)
{
	// A valid value must be either a float or a positive integer, between 0 and 1000
	int		dotCount = 0;

	for (std::string::iterator it = value.begin(); it != value.end(); ++it)
	{
		if (*it == DOT)
			++dotCount;

		if ((!isdigit(*it) && *it != DOT) || dotCount > DOTMAX)
			throw ParseErrorException("Error: invalid value");
	}

	if (value.at(value.length()-1) == DOT)
		throw ParseErrorException("Error: bad value");

	amount = static_cast<float>(std::atof(value.c_str()));

	if (amount <= 0 || amount > 1000)
		throw ParseErrorException("Error: out of range value");
}

void	BitcoinExchange::lineParse(l_iterator &it)
{
	// Each line in this file must use the following format: "date | value"

	std::string date = it->first;
	std::string	value = it->second;

	if (date.empty() && value.empty())
		throw ParseErrorException("Error: empty line");

	if (date.empty() || value.empty())
		throw ParseErrorException("Error: bad input");

	if (date[date.length()-1] != SPACE || value.at(0) != SPACE)
		throw ParseErrorException("Error: syntax error near pipe");

	date.erase(date.length()-1); value.erase(0, DOTMAX);

	parseDate(date);
	parseValue(value);
}

float	BitcoinExchange::retrieveExchangeRate()
{
	float		exchangeRate = 0;
	iterator	it = db.lower_bound(key);

	if (it->first != key && it == db.begin())
		return (exchangeRate);

	if (it->first != key)
		--it;

	exchangeRate = std::atof(it->second.c_str());

	return (exchangeRate);
}


BitcoinExchange::ParseErrorException::ParseErrorException(char const *msg) : message(msg)
{
}

const char	*BitcoinExchange::ParseErrorException::what() const throw()
{
	return (message);
}


BitcoinExchange::BitcoinExchange() : dbfile(DB), amount(0)
{
	// std::cout << "BitcoinExchange's Default Constructor called\n";

	readFileIntoMap();
}

BitcoinExchange::BitcoinExchange(std::string infilename) : dbfile(DB), infile(infilename)
{
	// std::cout << "BitcoinExchange's Parametrized Constructor called\n";

	std::string	failureMsg;
	std::string	dbfilename = DB;

	if (!dbfile.is_open() || !infile.is_open())
	{
		failureMsg = "Failed to open file (" + (!dbfile.is_open() ? dbfilename : infilename) + ") for reading";
		throw std::runtime_error(failureMsg);
	}

	readFileIntoMap();
	readFileIntoList();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	// std::cout << "BitcoinExchange's Copy Constructor called\n";

	*this = other;
}

BitcoinExchange::~BitcoinExchange() 
{
	// std::cout << "BitcoinExchange's Destructor called\n";
}


BitcoinExchange	&BitcoinExchange::operator = (const BitcoinExchange &rhs)
{
	db = rhs.db;
	list = rhs.list;

	return (*this);
}

void	BitcoinExchange::evaluate()
{
	float	amountVal;

	for (l_iterator it = list.begin(); it != list.end(); ++it)
	{
		try
		{
			lineParse(it);
			amountVal = retrieveExchangeRate() * amount;
			std::cout << key << " => " << amount << " = " << fixedNoTrailingZeros(amountVal) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}