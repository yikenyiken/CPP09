NAME =	PmergeMe

SRCS =	main.cpp mergeInsertionSort_v.cpp mergeInsertionSort_d.cpp math.cpp utils_v.cpp utils_d.cpp PmergeMe.cpp

CXX =	c++

INCLUDE = mergeInsertionSort_v.h mergeInsertionSort_d.h mergeInsertionSort.hpp PmergeMe.hpp

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