#include "projection.hpp"
#include "segment.hpp"
#include "circle.hpp"
#include "polygon.hpp"
#include "collision.hpp"

#include <limits>
#include <iostream>
#include <cmath>
#include <algorithm>

Segment::Segment() : ShapeImpl(), _slope(0), _length(0), _axis(Vector2())
{
	SetPointCount(2);
	_points[0] = Vector2(0, 0);
	_points[1] = Vector2(0, 0);
	_center = Vector2();
}

Segment::Segment(const Vector2 &a, const Vector2 &b) : ShapeImpl()
{
	SetPointCount(2);
	SetPoint(0, a);
	SetPoint(1, b);

	Vector2 s = GetPoint(1) - GetPoint(0);

	if (AreEqual(s.x, 0))
		_slope = std::numeric_limits<Precision_t>::infinity();

	else
		_slope = s.y / s.x;

	_length = GetPoint(0).GetDistance(GetPoint(1));

	_center = Vector2(GetPoint(0) + GetPoint(1)) / 2;

	const Vector2 edge = GetPoint(0) - GetPoint(1);
	const Axis normal = edge.Perpendicular().Normal();
	_axis = normal;
}

const Precision_t& Segment::GetLength() const
{
	return _length;
}

const Precision_t Segment::DistancePoint(const Vector2 &p) const
{
	return std::abs(SignedDistancePoint(p));
}

const Precision_t Segment::SignedDistancePoint(const Vector2 &p) const
{
	const Vector2 vec = GetTransformedPoint(1) - GetTransformedPoint(0);
	const Vector2 pa = p - GetTransformedPoint(0);

	if (std::abs(vec.x) < EPS)
	{
		return vec.y >= 0 ? pa.x : -pa.x;
	}

	else if (std::abs(vec.y) < EPS)
	{
		return vec.x >= 0 ? -pa.y : pa.y;
	}

	const Precision_t l = vec.Length();

	return (vec.y * pa.x - vec.x * pa.y) / l;
}

const Precision_t& Segment::GetSlope() const
{
	return _slope;
}


const Axis& Segment::GetAxis() const
{
	return _axis;
}

const Vector2 Segment::GetNearestPoint(const Vector2 &p) const
{
	const Vector2 s = GetTransformedPoint(1) - GetTransformedPoint(0);
	const Vector2 ap = p - GetTransformedPoint(0);

	const Precision_t vs = ap.Dot(s);
	const Precision_t ss = s.Dot(s);

	const Precision_t q = vs / ss;


	if (q < 0)
		return GetTransformedPoint(0);

	else if (q > 1)
		return GetTransformedPoint(1);

	else
		return GetTransformedPoint(0) + (s * q);
}

const Vector2 Segment::NearestVertex(const Vector2 &p) const
{
	Precision_t dist = std::numeric_limits<Precision_t>::infinity();
	Vector2 v;

	for (unsigned i = 0; i < GetPointCount(); i++)
	{
		Precision_t temp = p.GetDistance(GetTransformedPoint(i));

		if (temp < dist)
		{
			dist = temp;
			v = GetTransformedPoint(i);
		}
	}

	return v;
}

const bool Segment::IsPerpendicular(const Segment &l) const
{
	const Precision_t s1 = l.GetSlope();
	const Precision_t s2 = GetSlope();
	const Precision_t max = std::numeric_limits<Precision_t>::infinity();

	if ((AreEqual(s1, 0) && s2 == max) || (s1 == max && AreEqual(s2, 0)))
		return true;

	else
	{
		return AreEqual(l.GetSlope() * GetSlope(), -1);
	}
}

const bool Segment::IsParallel(const Segment &l) const
{
	return AreEqual(l.GetSlope(), GetSlope());
}

const Projection Segment::Project(const Axis &a) const
{
	const Precision_t dot0 = a.Dot(GetTransformedPoint(0));
	const Precision_t dot1 = a.Dot(GetTransformedPoint(1));

	return Projection(std::min(dot0, dot1), std::max(dot0, dot1));
}

const bool Segment::Contains(const Vector2 &p) const
{
	const Vector2 ba = (GetTransformedPoint(1) - GetTransformedPoint(0));
	const Vector2 ca = p - GetTransformedPoint(0);

	const Precision_t cross = ba.Cross(ca);
	const Precision_t dot = ba.Dot(ca);

	return (AreEqual(cross, 0) && dot >= 0 && dot < GetLength() * GetLength());
}

const bool Segment::Contains(const Segment &s) const
{
	if (s.GetLength() > GetLength())
		return false;

	else
		return (Contains(s.GetTransformedPoint(0)) && Contains(s.GetTransformedPoint(1)));
}

const bool Segment::Contains(const Circle &c) const
{
	return false;
}

const bool Segment::Contains(const Polygon &p) const
{
	return false;
}

const bool Segment::Intersects(const Segment &l) const
{
	if (IsParallel(l))
		return (Contains(l.GetTransformedPoint(0)) || Contains(l.GetTransformedPoint(1)));

	else
		return (GetIntersections(l).size() > 0);
}

const bool Segment::Intersects(const Circle &c) const
{
	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = (NearestVertex(c.GetCenter() + c.GetPos()) - c.GetCenter() + c.GetPos()).Normal();

	for (auto && axis : axes)
	{
		const Projection pA = c.Project(axis);
		const Projection pB = Project(axis);

		if (!pA.IsOverlap(pB))
			return false;
	}

	return true;
}

const bool Segment::Intersects(const Polygon &p) const
{
	AxesVec axes(p.GetAxes());
	axes.push_back(GetAxis());

	for (auto && axis : axes)
	{
		const Projection pA = p.Project(axis);
		const Projection pB = Project(axis);

		if (!pA.IsOverlap(pB))
			return false;
	}

	return true;
}

const std::vector<Vector2> Segment::GetIntersections(const Segment &l) const
{
	const Precision_t x1 = GetTransformedPoint(0).x;
	const Precision_t y1 = GetTransformedPoint(0).y;

	const Precision_t x2 = GetTransformedPoint(1).x;
	const Precision_t y2 = GetTransformedPoint(1).y;

	const Precision_t x3 = l.GetTransformedPoint(0).x;
	const Precision_t y3 = l.GetTransformedPoint(0).y;

	const Precision_t x4 = l.GetTransformedPoint(1).x;
	const Precision_t y4 = l.GetTransformedPoint(1).y;

	const Precision_t Bottom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	const Precision_t xTop = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
	const Precision_t yTop = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

	const Precision_t x = xTop / Bottom;
	const Precision_t y = yTop / Bottom;

	std::vector<Vector2> intersects(0);

	const Vector2 i = Vector2(x, y);

	if (Contains(i) && l.Contains(i))
		intersects.push_back(i);

	return intersects;
}

const std::vector<Vector2> Segment::GetIntersections(const Circle &c) const
{
	std::vector<Vector2> intersections(0);

	Vector2 circlePosition = c.GetCenter() + c.GetPos();
	Precision_t r2 = c.GetRadius() * c.GetRadius();

	Vector2 ba = GetTransformedPoint(1) - GetTransformedPoint(0);
	Vector2 ca = (circlePosition) - GetTransformedPoint(0);

	Precision_t dot = ba.Dot(ca);
	Vector2 proj1 = ba * (dot / ba.LengthSq());

	Vector2 midpt = GetTransformedPoint(0) + proj1;
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
		disIntercept = c.GetRadius();

	else
		disIntercept = std::sqrt(r2 - distCenterSq);

	ba = ba.Normal() * disIntercept;

	Vector2 sol1 = midpt + ba;
	Vector2 sol2 = midpt - ba;

	if (Contains(sol1))
		intersections.push_back(sol1);

	if (Contains(sol2))
		intersections.push_back(sol2);

	return intersections;
}

const std::vector<Vector2> Segment::GetIntersections(const Polygon &p) const
{
	return std::vector<Vector2>(0);
}

const Vector2 Segment::GetTranslation(const Segment &s) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = s.GetAxis();

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

	const Vector2 distance = (s.GetCenter() + s.GetPos()) - (GetCenter() + GetPos());

	//if (translation.Dot(distance) < 0)
	translation = -translation;

	return translation;
}

const Vector2 Segment::GetTranslation(const Circle &c) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = (NearestVertex(c.GetCenter() + c.GetPos()) - c.GetCenter() + c.GetPos()).Normal();

	for (auto && axis : axes)
	{
		const Projection pA = c.Project(axis);
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

	const Vector2 distance = (c.GetCenter() + c.GetPos()) - (GetCenter() + GetPos());

	if (translation.Dot(distance) < 0)
		translation = -translation;

	return translation;
}

const Vector2 Segment::GetTranslation(const Polygon &p) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	AxesVec axes(p.GetAxes());
	axes.push_back(GetAxis());

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

	return translation;
}

const Collision Segment::GetCollision(const Shape &s) const
{
	return -s.GetCollision(*this);
}

const Collision Segment::GetCollision(const Segment &s) const
{
	return Collision(Intersects(s), GetIntersections(s), Contains(s), s.Contains(*this), GetTranslation(s));
}

const Collision Segment::GetCollision(const Circle &c) const
{
	bool doesIntersect = false;

	// Determine if the circle contains
	// the segment "s"
	bool contains = false;

	// The segment "s" cannot
	// contain this circle
	bool contained = c.Contains(*this);

	// Intersection points
	std::vector<Vector2> intersects(0);

	// Translation is the vector to be applied to segment "s"
	// in order to seperate it from the circle
	Vector2 translation(0, 0);
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;

	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = (NearestVertex(c.GetCenter() + c.GetPos()) - (c.GetCenter() + c.GetPos())).Normal();

	for (auto && axis : axes)
	{
		const Projection pA = c.Project(axis);
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

	translation = smallest * (Overlap + 1);

	const Vector2 distance = NearestVertex(c.GetCenter() + c.GetPos()) - (c.GetCenter() + c.GetPos());

	if (translation.Dot(distance) > 0)
		translation = -translation;

	if (!contains)
		intersects = GetIntersections(c);

	return Collision(doesIntersect, intersects, contains, contained, translation);
}

const Collision Segment::GetCollision(const Polygon &p) const
{
	bool doesIntersect = false;

	// Determine if this polygon contains
	// the segment "s"
	bool contains = false;//Contains(s);

	// The segment "s" cannot
	// contain this polygon
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	// Translation is the vector to be applied to segment "s"
	// in order to seperate it from the circle
	Vector2 translation(0, 0);
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;

	AxesVec axes(p.GetAxes());
	axes.push_back(GetAxis());

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

	translation = smallest * (Overlap + 1);

	Vector2 distance = (GetCenter() + GetPos()) - (p.GetCenter() + p.GetPos());

	if (translation.Dot(distance) > 0)
		translation = -translation;

	doesIntersect = true;
	contained = p.Contains(*this);

	return Collision(doesIntersect, intersects, contains, contained, translation);
}

void Segment::ReCalc()
{
	const Vector2 s = GetPoint(1) - GetPoint(0);

	if (AreEqual(s.x, 0))
		_slope = std::numeric_limits<Precision_t>::infinity();

	else
		_slope = s.y / s.x;

	_length = GetPoint(0).GetDistance(GetPoint(1));
	_center = Vector2(GetPoint(0) + GetPoint(1)) / 2;

	const Vector2 edge = GetPoint(0) - GetPoint(1);
	_axis = edge.Perpendicular().Normal();
}
