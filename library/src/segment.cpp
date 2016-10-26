#include "segment.hpp"

#include <limits>
#include <iostream>
#include <cmath>
#include <algorithm>

Segment::Segment() : Shape(), _axis(Vector2())
{
	SetPointCount(2);
	_points[0] = Vector2(0, 0);
	_points[1] = Vector2(0, 0);
	_center = Vector2();
}

Segment::Segment(const Vector2 &a, const Vector2 &b) : Shape()
{
	SetPointCount(2);
	SetPoint(0, a);
	SetPoint(1, b);

	Vector2 s = GetPoint(1) - GetPoint(0);

	_center = Vector2(GetPoint(0) + GetPoint(1)) / 2;

	const Vector2 edge = -s;
	_axis = edge.Perpendicular().Normal();
}

const Precision_t Segment::GetLength(const Transform &t) const
{
	return GetTransformedPoint(0, t).GetDistance(GetTransformedPoint(1, t));
}

const Precision_t Segment::DistancePoint(const Vector2 &p, const Transform &t) const
{
	return std::abs(SignedDistancePoint(p, t));
}

// Fixme: This function treats the segment as a line for calculations
const Precision_t Segment::SignedDistancePoint(const Vector2 &p, const Transform &t) const
{
	const Precision_t EPS = 1e-12;
	const Vector2 vec = GetTransformedPoint(1, t) - GetTransformedPoint(0, t);
	const Vector2 pa = p - GetTransformedPoint(0, t);

	if (std::abs(vec.x) < EPS)
	{
		return vec.y >= 0 ? pa.x : -pa.x;
	}

	else if (std::abs(vec.y) < EPS)
	{
		return vec.x >= 0 ? -pa.y : pa.y;
	}

	const Precision_t l = vec.Magnitude();
	return (vec.y * pa.x - vec.x * pa.y) / l;
}

const Precision_t Segment::GetSlope(const Transform &t) const
{
	const Vector2 s = GetTransformedPoint(1, t) - GetTransformedPoint(0, t);

	if (AreEqual(s.x, 0))
		return std::numeric_limits<Precision_t>::infinity();

	else
		return s.y / s.x;
}

const Precision_t Segment::GetSlope() const
{
	const Vector2 s = GetPoint(1) - GetPoint(0);

	if (AreEqual(s.x, 0))
		return std::numeric_limits<Precision_t>::infinity();

	else
		return s.y / s.x;
}

void Segment::Recalc()
{
	_center = Vector2(GetPoint(0) + GetPoint(1)) / 2;

	const Vector2 edge = GetPoint(0) - GetPoint(1);
	_axis = edge.Perpendicular().Normal();
}

const bool Segment::IsPerpendicular(const Segment &l, const Transform &t1, const Transform &t2) const
{
	const Precision_t s1 = l.GetSlope(t2);
	const Precision_t s2 = GetSlope(t1);
	const Precision_t max = std::numeric_limits<Precision_t>::infinity();

	if ((AreEqual(s1, 0) && s2 == max) || (s1 == max && AreEqual(s2, 0)))
		return true;

	else
	{
		return AreEqual(l.GetSlope(t2) * GetSlope(t1), -1);
	}
}

const bool Segment::IsParallel(const Segment &l, const Transform &t1, const Transform &t2) const
{
	return AreEqual(l.GetSlope(t2), GetSlope(t1));
}

const bool Segment::IsParallel(const Segment &l) const
{
	return AreEqual(l.GetSlope(), GetSlope());
}

const bool Segment::ContainsPoint(const Vector2 &p, const Transform &t) const
{
	const Vector2 ba = (GetTransformedPoint(1, t) - GetTransformedPoint(0, t));
	const Vector2 ca = p - GetTransformedPoint(0, t);

	const Precision_t cross = ba.Cross(ca);
	const Precision_t dot = ba.Dot(ca);

	return (AreEqual(cross, 0) && dot >= 0 && dot < GetLength(t) * GetLength(t));
}

void Segment::SetPoint(const unsigned &i, const Vector2 &p)
{
	Shape::SetPoint(i, p);
	Recalc();
}

const bool Segment::Intersects(const Segment &l, const Transform &t1, const Transform &t2) const
{
	if (IsParallel(l, t1, t2))
		return (ContainsPoint(l.GetTransformedPoint(0, t2), t1) || ContainsPoint(l.GetTransformedPoint(1, t2), t1));

	else
	{
		const Vector2 i = GetIntersect(l, t1, t2);
		return (ContainsPoint(i, t1) && l.ContainsPoint(i, t2));
	}
}

const Vector2 Segment::GetIntersect(const Segment &l, const Transform &t1, const Transform &t2) const
{
	const Precision_t x1 = GetTransformedPoint(0, t1).x;
	const Precision_t y1 = GetTransformedPoint(0, t1).y;

	const Precision_t x2 = GetTransformedPoint(1, t1).x;
	const Precision_t y2 = GetTransformedPoint(1, t1).y;

	const Precision_t x3 = l.GetTransformedPoint(0, t2).x;
	const Precision_t y3 = l.GetTransformedPoint(0, t2).y;

	const Precision_t x4 = l.GetTransformedPoint(1, t2).x;
	const Precision_t y4 = l.GetTransformedPoint(1, t2).y;

	const Precision_t Bottom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	const Precision_t xTop = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
	const Precision_t yTop = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

	const Precision_t x = xTop / Bottom;
	const Precision_t y = yTop / Bottom;

	return Vector2(x, y);
}

const Vector2 Segment::GetTranslation(const Segment &l, const Transform &t1, const Transform &t2) const
{
	std::vector<Precision_t> dist(4);
	dist[0] = SignedDistancePoint(l.GetTransformedPoint(0, t2), t1);
	dist[1] = SignedDistancePoint(l.GetTransformedPoint(1, t2), t1);
	dist[2] = l.SignedDistancePoint(GetTransformedPoint(0, t1), t2);
	dist[3] = l.SignedDistancePoint(GetTransformedPoint(1, t1), t2);

	auto it = std::min_element(std::begin(dist), std::end(dist), [](const double & a, const double & b)
	{
		return std::abs(a) < std::abs(b);
	} );

	Precision_t min = *it;
	const unsigned pos = std::distance(std::begin(dist), it);

	Vector2 axis;

	if (pos == 2 || pos == 3)
	{
		axis = l.GetAxis() * -1;
		//min = -min;
	}

	else
	{
		axis = GetAxis();
	}

	return -axis * (std::abs(min) + 1);
}

const Axis& Segment::GetAxis() const
{
	return _axis;
}
