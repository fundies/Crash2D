#include "circle.hpp"
#include "polygon.hpp"
#include "segment.hpp"
#include "projection.hpp"
#include "collision.hpp"

#include <cmath>
#include <algorithm>

Circle::Circle() : ShapeImpl(Vector2(0, 0)), _radius(0)
{
}

Circle::Circle(const Vector2 c, const Precision_t r) : ShapeImpl(c), _radius(r)
{
}

const Projection Circle::Project(const Shape &s, const Axis &a) const
{
	return s.Project(a);
}

void Circle::SetRadius(const Precision_t r)
{
	_radius = r;
}

const Precision_t& Circle::GetRadius() const
{
	return _radius;
}

const Projection Circle::Project(const Axis &a) const
{
	const Precision_t v = a.Dot(GetCenter());
	return Projection(v - GetRadius(), v + GetRadius());
}

const bool Circle::Contains(const Vector2 &p) const
{
	const Vector2 v = (GetCenter()) - p;
	const Precision_t dist = v.Length();

	return (dist <= GetRadius());
}

const bool Circle::Contains(const Polygon &p) const
{
	for (auto && pt : p.GetPoints())
	{
		if (!Contains(pt))
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
		const Vector2 v = (c.GetCenter()) - (GetCenter());

		const Precision_t dist = v.Length();
		const Precision_t radiiDif = std::abs(GetRadius() - c.GetRadius());

		return (dist <= radiiDif);
	}
}

const bool Circle::Contains(const Segment &s) const
{
	return (Contains(s.GetPoint(0)) && Contains(s.GetPoint(1)));
}

const bool Circle::Overlaps(const Segment &s) const
{
	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetCenter()) - GetCenter()).Normalize();

	return (CalcDisplacement(axes, *this, s) != Vector2(0, 0));
}

const bool Circle::Overlaps(const Circle &c) const
{
	const Vector2 v = (c.GetCenter()) - (GetCenter());

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t dist = v.Length();

	return (dist <= radiiSum);
}

const bool Circle::Overlaps(const Polygon &p) const
{
	const Axis ax = (p.NearestVertex(GetCenter()) - GetCenter()).Normalize();

	AxesVec axes(p.GetAxes());
	axes.push_back(ax);

	return (CalcDisplacement(axes, *this, p) != Vector2(0, 0));
}

const std::vector<Vector2> Circle::GetIntersects(const Segment &s) const
{
	std::vector<Vector2> intersections(0);

	Vector2 circlePosition = GetCenter();
	Precision_t r2 = GetRadius() * GetRadius();

	Vector2 ba = s.GetPoint(1) - s.GetPoint(0);
	Vector2 ca = (circlePosition) - s.GetPoint(0);

	Precision_t dot = ba.Dot(ca);
	Vector2 proj1 = ba * (dot / ba.LengthSq());

	Vector2 midpt = s.GetPoint(0) + proj1;
	Vector2 cm = midpt - circlePosition;

	Precision_t distCenterSq = cm.LengthSq();

	if (distCenterSq > r2)
		return intersections;

	if (distCenterSq == r2)
	{
		if (Contains(midpt))
			intersections.push_back(midpt);

		return intersections;
	}

	Precision_t disIntercept;

	if (distCenterSq == 0)
		disIntercept = GetRadius();

	else
		disIntercept = std::sqrt(r2 - distCenterSq);

	ba = ba.Normalize() * disIntercept;

	const Vector2 sol1 = midpt + ba;
	const Vector2 sol2 = midpt - ba;

	if (s.Contains(sol1))
		intersections.push_back(sol1);

	if (s.Contains(sol2))
		intersections.push_back(sol2);

	return intersections;
}

const std::vector<Vector2> Circle::GetIntersects(const Circle &c) const
{
	std::vector<Vector2> intersections(0);

	if (!Overlaps(c))
		return intersections;

	const Vector2 c1Pos = GetCenter();
	const Vector2 c2Pos = c.GetCenter();

	const Precision_t c1r2 = GetRadius() * GetRadius();
	const Precision_t c2r2 = c.GetRadius() * c.GetRadius();

	const Vector2 c2c1 = c2Pos - c1Pos;
	const Precision_t dist2 = c2c1.LengthSq();
	const Precision_t dist = std::sqrt(dist2);

	const Precision_t a = ((c1r2 - c2r2) + dist2) / (2.0 * dist);
	const Precision_t h = std::sqrt(c1r2 - a * a);

	const Vector2 p = c1Pos + (c2c1 * a) / dist;

	const Vector2 d = (c2c1 * h  / dist);

	const Vector2 i1(p.x + d.y, p.y - d.x);
	const Vector2 i2(p.x - d.y, p.y + d.x);

	intersections.push_back(i1);

	if (i1 != i2)
		intersections.push_back(i2);

	return intersections;
}

const std::vector<Vector2> Circle::GetIntersects(const Polygon &p) const
{
	std::vector<Vector2> intersections(0);

	std::vector<Segment> sides;

	for (auto && side : p.GetSides())
	{
		const Segment seg(side.GetPoint(0), side.GetPoint(1));

		const std::vector<Vector2> intercepts = GetIntersects(seg);

		for (auto && pt : intercepts)
		{
			auto it = std::find(std::begin(intersections), std::end(intersections), pt);

			if (it == std::end(intersections))
				intersections.push_back(pt);
		}
	}

	return intersections;
}

const Vector2 Circle::GetDisplacement(const Segment &s) const
{
	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetCenter()) - (GetCenter())).Normalize();

	return CalcDisplacement(axes, *this, s);
}

const Vector2 Circle::GetDisplacement(const Circle &c) const
{
	const Vector2 v = (c.GetCenter()) - (GetCenter());

	const Precision_t theta = atan2(v.y, v.x);

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t dist = v.Length();
	const Precision_t tDist = (radiiSum - dist) + 1;

	const Precision_t x = tDist * std::cos(theta);
	const Precision_t y = tDist * std::sin(theta);

	const Vector2 displacement(x, y);

	return displacement;
}

const Vector2 Circle::GetDisplacement(const Polygon &p) const
{
	const Axis ax = (p.NearestVertex(GetCenter()) - (GetCenter())).Normalize();

	auto axes = p.GetAxes();
	axes.push_back(ax);

	return CalcDisplacement(axes, *this, p);
}

const Collision Circle::GetCollision(const Shape &s) const
{
	return -s.GetCollision(*this);
}

const Collision Circle::GetCollision(const Segment &s) const
{
	// Check if circle contains segment
	bool contains = false;

	// Segments cannot contain circles
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetCenter()) - GetCenter()).Normalize();

	const Vector2 displacement = CalcDisplacement(axes, *this, s);

	bool doesOverlap = (displacement != Vector2(0, 0));

	if (doesOverlap)
	{
		contains = Contains(s);
		intersects = GetIntersects(s);
	}

	return Collision(doesOverlap, intersects, contains, contained, displacement);
}

const Collision Circle::GetCollision(const Circle &c) const
{
	const Vector2 v = (c.GetCenter()) - (GetCenter());

	const Precision_t theta = atan2(v.y, v.x);

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t dist = v.Length();
	const Precision_t tDist = (radiiSum - dist) + 1;

	bool doesOverlap = (dist <= radiiSum);

	// Determine if this circle contains
	// the circle "c"
	bool contains = Contains(c);//(dist <= radiiDif);

	// Determine if the circle "c"
	// contains this circle
	bool contained = c.Contains(*this);

	// Intersection points
	std::vector<Vector2> intersects(0);

	// Displacement is the vector to be applied to circle "c"
	// in order to seperate it from the circle
	Vector2 displacement;

	if (doesOverlap)
	{

		const Precision_t x = tDist * std::cos(theta);
		const Precision_t y = tDist * std::sin(theta);

		displacement = Vector2(x, y);
		intersects = GetIntersects(c);
	}

	return Collision(doesOverlap, intersects, contains, contained, displacement);
}

const Collision Circle::GetCollision(const Polygon &p) const
{
	// Check if circle contains polygon
	bool contains = false;

	// Check if circle is contained by the polygon
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	auto axes = p.GetAxes();
	axes.push_back((p.NearestVertex(GetCenter()) - (GetCenter())).Normalize());

	const Vector2 displacement = CalcDisplacement(axes, *this, p);

	const bool doesOverlap = (displacement != Vector2(0, 0));

	if (doesOverlap)
	{
		contains = Contains(p);
		contained = p.Contains(*this);
		intersects = GetIntersects(p);
	}

	return Collision(doesOverlap, intersects, contains, contained, displacement);
}
