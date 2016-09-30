#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include "vector2.hpp"

//!  A class representing a two-dimensional projection. */
class Projection : public Vector2
{
public:
	//! Constructs a default projection.
	/*!
	*/
	Projection() : Vector2(0 , 0) {}

	Projection(const Precision_t &min, const Precision_t &max) : Vector2(min, max) {}
	Projection(const Vector2 &v);
	const bool IsOverlap(const Projection &p) const;
	const Precision_t GetOverlap(const Projection &p) const;
};

#endif
