int	j(unsigned int x)
{
	if (!x)
		return (0);

	if (x == 1)
		return (1);
	
	return (j(x - 1) + 2 * j(x - 2));
}

int	ft_log2(int x)
{
	int count = 0;

	while (x > 1)
	{
		x = x / 2;
		++count;
	}

	return (count);
}

int	ft_pow(int x, int y)
{
	int res = x;

	while (y - 1)
	{
		res *= x;
		--y;
	}

	return (res);
}