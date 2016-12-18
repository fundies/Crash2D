#include "circle.hpp"
#include "polygon.hpp"
#include "segment.hpp"
#include "projection.hpp"
#include "collision.hpp"

#include <cmath>
#include <iostream>
#include <limits>

Circle::Circle(const Precision_t &r) : Shape(), _radius(r)
{
	_center = Vector2(r, r);
}

const Precision_t& Circle::GetRadius() const
{
	return _radius;
}

const Projection Circle::Project(const Axis &a) const
{
	const Precision_t v = a.Dot(GetPos());
	return Projection(v - GetRadius(), v + GetRadius());
}

const bool Circle::Contains(const Vector2 &p) const
{
	const Vector2 v = GetPos() - p;
	const Precision_t dist = v.Magnitude();

	return (dist < GetRadius());
}

const bool Circle::Contains(const Polygon &p) const
{
	for (auto && pt : p.GetPoints())
	{
		if (!Contains(pt + p.GetPos()))
			return false;
	}

	return true;
}

const bool Circle::Contains(const Circle &c) const
{
	if (c.GetRadius() > GetRadius())
		return false;

	else
	{
		Vector2 v = c.GetPos() - GetPos();

		Precision_t dist = v.Magnitude();
		Precision_t radiiDif = std::abs(GetRadius() - c.GetRadius());

		return (dist <= radiiDif);
	}
}

const bool Circle::Contains(const Segment &s) const
{
	return (Contains(s.GetTransformedPoint(0)) && Contains(s.GetTransformedPoint(1)));
}


const bool Circle::Intersects(const Segment &s) const
{
	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetPos()) - GetPos()).Normal();

	for (auto && axis : axes)
	{
		const Projection pA = s.Project(axis);
		const Projection pB = Project(axis);

		if (!pA.IsOverlap(pB))
			return false;
	}

	return true;
}

const bool Circle::Intersects(const Circle &c) const
{
	const Vector2 v = c.GetPos() - GetPos();

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t dist = v.Magnitude();

	return (dist < radiiSum);
}

const bool Circle::Intersects(const Polygon &p) const
{
	const Axis ax = (p.NearestVertex(GetPos()) - GetPos()).Normal();

	AxesVec axes(p.GetAxes());
	axes.push_back(ax);

	for (auto && axis : axes)
	{
		const Projection pA = p.Project(axis);
		const Projection pB = Project(axis);

		if (!pA.IsOverlap(pB))
			return false;
	}

	return true;
}

const std::vector<Vector2> Circle::GetIntersections(const Segment &s) const
{
	std::vector<Vector2> intersections(0);

	// compute the euclidean distance between A and B
	const Precision_t LAB = s.GetLength();

	// compute the direction vector D from A to B
	const Vector2 ba = s.GetTransformedPoint(1) - s.GetTransformedPoint(0);
	const Vector2 dir = ba / LAB;

	// compute the value t of the closest point to the circle center (Cx, Cy)
	const Precision_t t = dir.x * (GetPos().x - s.GetTransformedPoint(0).x)
	                      + dir.y * (GetPos().y - s.GetTransformedPoint(0).y);

	// compute the coordinates of the point E on line and closest to C
	const Vector2 e = (dir * t) + s.GetTransformedPoint(0);

	// compute the euclidean distance from E to C
	const Precision_t LEC = e.GetDistance(GetPos());

	// test if the line intersects the circle
	if (LEC < GetRadius())
	{
		// compute distance from t to circle intersection point
		const Precision_t dt = std::sqrt(GetRadius() * GetRadius() - LEC * LEC);

		// compute first intersection point
		const Vector2 i1 = dir * (t - dt) + s.GetTransformedPoint(0);

		// compute second intersection point
		const Vector2 i2 = dir * (t + dt) + s.GetTransformedPoint(0);

		if (s.Contains(i1))
			intersections.push_back(i1);

		if (s.Contains(i2))
			intersections.push_back(i2);
	}

	// else test if the line is tangent to circle
	else if (LEC == GetRadius())
	{
		intersections.push_back(s.GetNearestPoint(GetPos()));
	}

	return intersections;
}

const std::vector<Vector2> Circle::GetIntersections(const Circle & c) const
{
	std::vector<Vector2> intersections(0);

	if (Contains(c) || c.Contains(*this) || !Intersects(c))
		return intersections;

	else
	{
		const Precision_t dist = GetPos().GetDistance(c.GetPos());

		const Precision_t a = (GetRadius() * GetRadius() - c.GetRadius() * c.GetRadius() + dist * dist) / (2.0 * dist);
		const Precision_t h = std::sqrt(GetRadius() * GetRadius() - a * a);

		const Vector2 p(GetPos().x + (a * (c.GetPos().x - GetPos().x)) / dist,
		                GetPos().y + (a * (c.GetPos().y - GetPos().y)) / dist);

		const Vector2 i1(p.x + (h * (c.GetPos().y - GetPos().y) / dist),
		                 p.y - (h * (c.GetPos().x - GetPos().x) / dist));

		const Vector2 i2(p.x - (h * (c.GetPos().y - GetPos().y) / dist),
		                 p.y + (h * (c.GetPos().x - GetPos().x) / dist));

		intersections.push_back(i1);
		intersections.push_back(i2);
	}

	return intersections;
}

const std::vector<Vector2> Circle::GetIntersections(const Polygon & p) const
{
	std::vector<Vector2> intersections(0);

	if (!Contains(p) && !p.Contains(*this))
	{
		std::vector<Segment> sides;

		for (auto && side : p.GetSides())
		{
			const Segment seg(side.GetPoint(0) + p.GetPos(), side.GetPoint(1) + p.GetPos());

			if (Intersects(seg) && !Contains(seg))
				sides.push_back(seg);
		}

		for (auto && side : sides)
		{
			const std::vector<Vector2> intercepts = GetIntersections(side);

			for (auto && p : intercepts)
				intersections.push_back(p);
		}

	}

	return intersections;
}

const Vector2 Circle::GetTranslation(const Segment &s) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetPos()) - GetPos()).Normal();

	for (auto && axis : axes)
	{
		const Projection pA = s.Project(axis);
		const Projection pB = Project(axis);

		if (pA.IsOverlap(pB))
		{
			const Precision_t o = pA.GetOverlap(pB);

			if (o < Overlap)
			{
				Overlap = o;
				smallest = axis;
			}
		}
	}

	translation = smallest * (Overlap + 1);

	const Vector2 distance = s.NearestVertex(GetPos()) - GetPos();

	if (translation.Dot(distance) < 0)
		translation = -translation;

	return translation;
}

const Vector2 Circle::GetTranslation(const Circle &c) const
{
	const Vector2 v = c.GetPos() - GetPos();

	const Precision_t theta = atan2(v.y, v.x);

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t dist = v.Magnitude();
	const Precision_t tDist = radiiSum - dist;

	const Precision_t x = tDist * std::cos(theta);
	const Precision_t y = tDist * std::sin(theta);

	Vector2 translation(x, y);

	if (translation.Dot(v) < 0)
		translation = -translation;

	return translation;
}

const Vector2 Circle::GetTranslation(const Polygon &p) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	const Axis ax = (p.NearestVertex(GetPos()) - GetPos()).Normal();

	AxesVec axes(p.GetAxes());
	axes.push_back(ax);

	for (auto && axis : axes)
	{
		const Projection pA = p.Project(axis);
		const Projection pB = Project(axis);

		if (pA.IsOverlap(pB))
		{
			const Precision_t o = pA.GetOverlap(pB);

			if (o < Overlap)
			{
				Overlap = o;
				smallest = axis;
			}
		}
	}

	translation = smallest * (Overlap + 1);

	Vector2 distance = GetPos() - (p.GetCenter() + p.GetPos());

	if (translation.Dot(distance) < 0)
		translation = -translation;

	return translation;
}

const Collision Circle::GetCollision(const Segment &s) const
{
	bool doesIntersect = false;

	// Determine if the circle contains
	// the segment "s"
	bool contains = false;

	// The segment "s" cannot
	// contain this circle
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	// Translation is the vector to be applied to segment "s"
	// in order to seperate it from the circle
	Vector2 translation(0, 0);
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;

	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetPos()) - GetPos()).Normal();

	for (auto && axis : axes)
	{
		const Projection pA = s.Project(axis);
		const Projection pB = Project(axis);

		// No Collision
		if (!pA.IsOverlap(pB))
			return Collision(doesIntersect, intersects, contains, contained, translation);

		else
		{
			const Precision_t o = pA.GetOverlap(pB);

			if (o < Overlap)
			{
				Overlap = o;
				smallest = axis;
			}
		}
	}

	doesIntersect = true;
	contains = Contains(s);

	translation = smallest * (Overlap + 1);

	const Vector2 distance = s.NearestVertex(GetPos()) - GetPos();

	if (translation.Dot(distance) < 0)
		translation = -translation;

	if (!contains)
		intersects = GetIntersections(s);

	return Collision(doesIntersect, intersects, contains, contained, translation);
}

const Collision Circle::GetCollision(const Circle &c) const
{
	const Vector2 v = c.GetPos() - GetPos();

	const Precision_t theta = atan2(v.y, v.x);

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t radiiDif = std::abs(GetRadius() - c.GetRadius());
	const Precision_t dist = v.Magnitude();
	const Precision_t tDist = radiiSum - dist;

	bool doesIntersect = (dist < radiiSum);

	// Determine if this circle contains
	// the circle "c"
	bool contains = (dist <= radiiDif);

	// FIXME: implement this //
	// Determine if the circle "c"
	// contains this circle
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	// Translation is the vector to be applied to circle "c"
	// in order to seperate it from the circle
	Vector2 translation(0, 0);

	if (doesIntersect)
	{
		intersects = GetIntersections(c);

		const Precision_t x = tDist * std::cos(theta);
		const Precision_t y = tDist * std::sin(theta);

		Vector2 translation(x, y);

		if (translation.Dot(v) < 0)
			translation = -translation;
	}

	return Collision(doesIntersect, intersects, contains, contained, translation);
}

const Collision Circle::GetCollision(const Polygon &p) const
{
	bool doesIntersect = false;

	// Determine if this circle contains
	// the polygon "p"
	bool contains = false;

	// Determine if the polygon "p"
	// contains this circle
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	// Translation is the vector to be applied to segment "s"
	// in order to seperate it from the circle
	Vector2 translation(0, 0);
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;

	const Axis ax = (p.NearestVertex(GetPos()) - GetPos()).Normal();

	AxesVec axes = p.GetAxes();
	axes.push_back(ax);

	for (auto && axis : axes)
	{
		const Projection pA = p.Project(axis);
		const Projection pB = Project(axis);

		// No Collision
		if (!pA.IsOverlap(pB))
			return Collision(doesIntersect, intersects, contains, contained, translation);

		else
		{
			const Precision_t o = pA.GetOverlap(pB);

			if (o < Overlap)
			{
				Overlap = o;
				smallest = axis;
			}
		}
	}

	doesIntersect = true;
	contains = Contains(p);
	contained = p.Contains(*this);

	translation = smallest * (Overlap + 1);

	Vector2 distance = GetPos() - (p.GetCenter() + p.GetPos());

	if (translation.Dot(distance) < 0)
		translation = -translation;

	if (!contains)
		intersects = GetIntersections(p);

	return Collision(doesIntersect, intersects, contains, contained, translation);
}
