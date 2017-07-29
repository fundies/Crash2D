#include "projection.hpp"

#include <iostream>

namespace Crash2D
{
Projection::Projection() : min(0), max(0)
{
}

Projection::Projection(const Precision_t min, const Precision_t max)
	: min(min), max(max)
{
}

const bool Projection::IsOverlap(const Projection &p) const
{
	return !(min > p.max || p.min > max);
}

const Precision_t Projection::GetOverlap(const Projection &p) const
{
	int sign = -1;

	if ((max - p.min) > (p.max - min))
		sign = 1;

	return sign * std::min(max - p.min, p.max - min);
}
}
