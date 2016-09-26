#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
	Circle(const Precision_t &r);
	const Projection Project(const Axis &a) const;
	const Collision GetCollision(const Circle &c) const;
	const Collision GetCollision(const Polygon &p) const;
	const Precision_t& GetRadius() const;
	const bool Contains(const Vector2 &p) const;
	const bool Contains(const Polygon &p) const;

private:
	Precision_t _radius;
};

#endif
