#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "vector2.hpp"

class Projection : public Vector2
{
public:
	Projection() : Vector2(0 ,0) {}
	Projection(Precision_t min, Precision_t max) : Vector2(min, max) {}
	Projection(const Vector2 &v);
	bool overlaps(Projection p);
	Precision_t getOverlap(Projection p);
};

#endif
