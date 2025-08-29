#ifndef header_HPP
# define header_HPP
# define ISODD(n) (n % 2)
# include <deque>

typedef std::deque<int>::iterator iter;
typedef std::deque<iter>::iterator iterIters;

// mymath
int	j(unsigned int x);
int	ft_log2(int x);
int	ft_pow(int x, int y);

// utils
int					getLastCurrentPos(int total, int pair_size);
size_t				getEquivalentPos(iter needle, std::deque<iter> haystack);
std::deque<int>		js_seq_gen(size_t bound);
iterIters			getLastComp(iterIters insertBound, iter toinsert, int optlen);
void				pairMake(std::deque<int> &vec, std::deque<iter> &winners, int pair_size, int n);
void				mapStoVec(std::deque<iter> &S, std::deque<int> &vec, int pair_size);

#endif