#include "projection.hpp"

Projection::Projection(const Vector2 &v)
{
	x = v.x;
	y = v.y;
}

bool Projection::overlaps(Projection p)
{
	// x = min & y = max
	return !(x > p.y || p.x > y);
}

Precision_t Projection::getOverlap(Projection p)
{
	// x = min & y = max
	return std::min(y, p.y) - std::max(x, p.x);
}
