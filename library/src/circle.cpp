#include "circle.hpp"
#include "polygon.hpp"
#include "segment.hpp"
#include "projection.hpp"
#include "collision.hpp"

#include <cmath>
#include <iostream>
#include <limits>

/** Begin Constructor **/

Circle::Circle() : ShapeImpl(Vector2(0, 0)), _radius(0)
{
}

Circle::Circle(const Vector2 c, const Precision_t r) : ShapeImpl(c), _radius(r)
{
}

/** End Constructor **/

/** Circle Specific **/

void Circle::SetRadius(const Precision_t r)
{
	_radius = r;
}

const Precision_t& Circle::GetRadius() const
{
	return _radius;
}

/** End Circle Specific **/

const Projection Circle::Project(const Axis &a) const
{
	const Precision_t v = a.Dot(GetCenter() + GetPos());
	return Projection(v - GetRadius(), v + GetRadius());
}


/** Begin Contains **/

const bool Circle::Contains(const Vector2 &p) const
{
	const Vector2 v = GetCenter() + GetPos() - p;
	const Precision_t dist = v.Length();

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
		Vector2 v = c.GetCenter() + c.GetPos() - GetCenter() + GetPos();

		Precision_t dist = v.Length();
		Precision_t radiiDif = std::abs(GetRadius() - c.GetRadius());

		return (dist <= radiiDif);
	}
}

const bool Circle::Contains(const Segment &s) const
{
	return (Contains(s.GetTransformedPoint(0)) && Contains(s.GetTransformedPoint(1)));
}

/** End Contains **/

/** Begin Intersects **/

const bool Circle::Intersects(const Segment &s) const
{
	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetCenter() + GetPos()) - GetCenter() + GetPos()).Normal();

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
	const Vector2 v = c.GetCenter() + c.GetPos() - GetCenter() + GetPos();

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t dist = v.Length();

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

/** End Intersects **/

/** Begin GetIntersections **/

const std::vector<Vector2> Circle::GetIntersections(const Segment & s) const
{
	std::vector<Vector2> intersections(0);

	Vector2 circlePosition = GetCenter() + GetPos();
	Precision_t r2 = GetRadius() * GetRadius();

	Vector2 ba = s.GetTransformedPoint(1) - s.GetTransformedPoint(0);
	Vector2 ca = (circlePosition) - s.GetTransformedPoint(0);

	Precision_t dot = ba.Dot(ca);
	Vector2 proj1 = ba * (dot / ba.LengthSq());

	Vector2 midpt = s.GetTransformedPoint(0) + proj1;
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

	ba = ba.Normal() * disIntercept;

	Vector2 sol1 = midpt + ba;
	Vector2 sol2 = midpt - ba;

	if (s.Contains(sol1))
		intersections.push_back(sol1);

	if (s.Contains(sol2))
		intersections.push_back(sol2);

	return intersections;
}

const std::vector<Vector2> Circle::GetIntersections(const Circle & c) const
{
	std::vector<Vector2> intersections(0);

	const Vector2 c1Pos = GetCenter() + GetPos();
	const Vector2 c2Pos = c.GetCenter() + c.GetPos();

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
	intersections.push_back(i2);

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

/** End GetIntersections **/

/** Begin GetTranslation **/

const Vector2 Circle::GetTranslation(const Segment & s) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	AxesVec axes(2);
	axes[0] = s.GetAxis();
	axes[1] = (s.NearestVertex(GetCenter() + GetPos()) - GetCenter() + GetPos()).Normal();

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

	const Vector2 distance = s.NearestVertex(GetCenter() + GetPos()) - GetCenter() + GetPos();

	if (translation.Dot(distance) < 0)
		translation = -translation;

	return translation;
}

const Vector2 Circle::GetTranslation(const Circle & c) const
{
	const Vector2 v = c.GetCenter() + c.GetPos() - GetCenter() + GetPos();

	const Precision_t theta = atan2(v.y, v.x);

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t dist = v.Length();
	const Precision_t tDist = radiiSum - dist;

	const Precision_t x = tDist * std::cos(theta);
	const Precision_t y = tDist * std::sin(theta);

	Vector2 translation(x, y);

	if (translation.Dot(v) < 0)
		translation = -translation;

	return translation;
}

const Vector2 Circle::GetTranslation(const Polygon & p) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	const Axis ax = (p.NearestVertex(GetCenter() + GetPos()) - GetCenter() + GetPos()).Normal();

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

	Vector2 distance = GetCenter() + GetPos() - (p.GetCenter() + p.GetPos());

	if (translation.Dot(distance) > 0)
		translation = -translation;

	return translation;
}

const Collision Circle::GetCollision(const Shape &s) const
{
	return -s.GetCollision(*this);
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
	intersects = GetIntersections(s);

	translation = smallest * (Overlap + 1);

	const Vector2 distance = s.NearestVertex(GetCenter() + GetPos()) - (GetCenter() + GetPos());

	if (translation.Dot(distance) < 0)
		translation = -translation;

	if (!contains)
		intersects = GetIntersections(s);

	return Collision(doesIntersect, intersects, contains, contained, translation);
}

const Collision Circle::GetCollision(const Circle &c) const
{
	const Vector2 v = (c.GetCenter() + c.GetPos()) - (GetCenter() + GetPos());

	const Precision_t theta = atan2(v.y, v.x);

	const Precision_t radiiSum = GetRadius() + c.GetRadius();
	const Precision_t radiiDif = std::abs(GetRadius() - c.GetRadius());
	const Precision_t dist = v.Length();
	const Precision_t tDist = radiiSum - dist;

	bool doesIntersect = (dist < radiiSum);

	// Determine if this circle contains
	// the circle "c"
	bool contains = Contains(c);//(dist <= radiiDif);

	// Determine if the circle "c"
	// contains this circle
	bool contained = c.Contains(*this);

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

		translation = Vector2(x, y);

		if (translation.Dot(v) < 0)
			translation = -translation;

		intersects = GetIntersections(c);
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

	const Axis ax = (p.NearestVertex(GetCenter() + GetPos()) - (GetCenter() + GetPos())).Normal();

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

	Vector2 distance = (GetCenter() + GetPos()) - (p.GetCenter() + p.GetPos());

	if ((translation.Dot(distance) > 0) && !contained)
		translation = -translation;

	if (!contains)
		intersects = GetIntersections(p);

	return Collision(doesIntersect, intersects, contains, contained, translation);
}
