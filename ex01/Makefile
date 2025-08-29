NAME =	RPN

SRCS =	main.cpp RPN.cpp

CXX =	c++

INCLUDE = RPN.hpp

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