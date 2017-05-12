#ifndef MATHUTILITY_HPP
#define MATHUTILITY_HPP

#include <random>

int randb(int min, int max)
{
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x;

	do
	{
		x = std::rand();
	}
	while (x >= RAND_MAX - remainder);

	return min + x % n;
}

#endif // MATHUTILITY_HPP
