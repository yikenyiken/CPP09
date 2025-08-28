#ifndef header_HPP
# define header_HPP
# define ISODD(n) (n % 2)
# include <vector>

typedef std::vector<int>::iterator iter;
typedef std::vector<iter>::iterator iterIters;

// mymath
int	j(unsigned int x);
int	ft_log2(int x);
int	ft_pow(int x, int y);

// utils
int					getLastCurrentPos(int total, int pair_size);
size_t				getEquivalentPos(iter needle, std::vector<iter> haystack);
std::vector<int>	js_seq_gen(unsigned int bound);
iterIters			getLastComp(iterIters insertBound, iter toinsert, int optlen);
void				pairMake(std::vector<int> &vec, std::vector<iter> &winners, int pair_size, int n);
void				mapStoVec(std::vector<iter> &S, std::vector<int> &vec, int pair_size);

#endif