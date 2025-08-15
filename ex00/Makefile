NAME =	btc

SRCS =	main.cpp BitcoinExchange.cpp

CXX =	c++

INCLUDE = BitcoinExchange.hpp

FLAGS =	-Werror -Wall -Wextra -std=c++98

OBJS =	$(SRCS:.cpp=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

%.o		:	%.cpp $(INCLUDE)
	$(CXX) -c $(FLAGS) $< -o $@

clean	:
	@rm -f $(OBJS)

fclean	:	clean
	@rm -f $(NAME)

re		:	fclean all

.PHONY	:	clean