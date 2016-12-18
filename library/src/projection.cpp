#include "projection.hpp"

Projection::Projection() : Vector2(0 , 0)
{
}

Projection::Projection(const Precision_t &min, const Precision_t &max)
	: Vector2(min, max)
{
}

const bool Projection::IsOverlap(const Projection &p) const
{
	// x = min & y = max
	return !(x > p.y || p.x > y);
}

const Precision_t Projection::GetOverlap(const Projection &p) const
{
	// x = min & y = max
	//return std::min(y, p.y) - std::max(x, p.x);
	return std::min(y - p.x, p.y - x);
}
