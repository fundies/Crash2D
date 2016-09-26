#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "shape.hpp"

class Polygon : public Shape
{
public:
	Polygon();

	const AxesVec& GetAxes() const;
	void ReCalc();

	const Projection Project(const Axis &a) const;
	const Collision GetCollision(const Polygon &p) const;
	const Collision GetCollision(const Circle &c) const;

	const bool Contains(const Vector2 &p) const;
	const bool Contains(const Polygon &p) const;
	const bool Contains(const Circle &c) const;

	const std::vector<Line>& GetSides() const;
	const Vector2 NearestVertex(const Vector2 &point) const;

private:
	const bool TriangleContains(const Vector2 &p, const Vector2 &a, const Vector2 &b, const Vector2 &c) const;

	AxesVec _axes;
	std::vector<Line> _side;
};

#endif
