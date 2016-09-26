#include "line.hpp"

#include <limits>
#include <iostream>
#include <cmath>
#include <algorithm>

Line::Line() : Shape(), _slope(0), _axis(Vector2()), _length(0)
{
	SetPointCount(2);
	_points[0] = Vector2(0, 0);
	_points[1] = Vector2(0, 0);
	_center = Vector2();
}

Line::Line(const Vector2 &a, const Vector2 &b) : Shape()
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

	const Vector2 edge = -s;
	_axis = edge.Perpendicular().Normal();
}

const Precision_t& Line::GetLength() const
{
	return _length;
}

const Precision_t Line::DistancePoint(const Vector2 &p) const
{
	return std::abs(SignedDistancePoint(p));
}

const Precision_t Line::SignedDistancePoint(const Vector2 &p) const
{
	const Precision_t EPS = 1e-12;
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

	const Precision_t l = vec.Magnitude();
	return (vec.y * pa.x - vec.x * pa.y) / l;

	/*const Precision_t l2 = GetLength() * GetLength();
	const Vector2 vec = GetTransformedPoint(1) - GetTransformedPoint(0);
	const Vector2 pa = p - GetTransformedPoint(0);

	const Precision_t t = std::max(0.d, std::min(1.d, pa.Dot(vec) / l2));

	const Vector2 projection = (vec * t) + GetTransformedPoint(0);

	return p.GetDistance(projection);*/
}


const Precision_t& Line::GetSlope() const
{
	return _slope;
}

void Line::Recalc()
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

const bool Line::IsPerpendicular(const Line &l) const
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

const bool Line::IsParallel(const Line &l) const
{
	return AreEqual(l.GetSlope(), GetSlope());
}

const bool Line::ContainsPoint(const Vector2 &p) const
{
	const Vector2 ba = (GetTransformedPoint(1) - GetTransformedPoint(0));
	const Vector2 ca = p - GetTransformedPoint(0);

	const Precision_t cross = ba.Cross(ca);
	const Precision_t dot = ba.Dot(ca);

	return (AreEqual(cross, 0) && dot >= 0 && dot < GetLength() * GetLength());
}

void Line::SetPoint(const unsigned &i, const Vector2 &p)
{
	Shape::SetPoint(i, p);
	Recalc();
}

const bool Line::Intersects(const Line &l) const
{
	if (IsParallel(l))
		return (ContainsPoint(l.GetTransformedPoint(0)) || ContainsPoint(l.GetTransformedPoint(1)));

	else
	{
		const Vector2 i = GetIntersect(l);
		return (ContainsPoint(i) && l.ContainsPoint(i));
	}
}

const Vector2 Line::GetIntersect(const Line &l) const
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

	return Vector2(x, y);
}

void Line::Rotate(const Precision_t &a)
{
	Shape::Rotate(a);
}

const Vector2 Line::GetTranslation(const Line &l) const
{
	std::vector<Precision_t> dist(4);
	dist[0] = SignedDistancePoint(l.GetTransformedPoint(0));
	dist[1] = SignedDistancePoint(l.GetTransformedPoint(1));
	dist[2] = l.SignedDistancePoint(GetTransformedPoint(0));
	dist[3] = l.SignedDistancePoint(GetTransformedPoint(1));

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

const Axis& Line::GetAxis() const
{
	return _axis;
}
