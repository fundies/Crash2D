#include "projection.hpp"
#include "segment.hpp"
#include "circle.hpp"
#include "polygon.hpp"
#include "collision.hpp"

#include <limits>
#include <cmath>

namespace Crash2D
{
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
	const Axis normal = edge.Perpendicular().Normalize();
	_axis = normal;
}

const Projection Segment::Project(const Shape &s, const Axis &a) const
{
	return s.Project(a);
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
	const Vector2 vec = GetPoint(1) - GetPoint(0);
	const Vector2 pa = p - GetPoint(0);

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
	const Vector2 s = GetPoint(1) - GetPoint(0);
	const Vector2 ap = p - GetPoint(0);

	const Precision_t vs = ap.Dot(s);
	const Precision_t ss = s.Dot(s);

	const Precision_t q = vs / ss;


	if (q < 0)
		return GetPoint(0);

	else if (q > 1)
		return GetPoint(1);

	else
		return GetPoint(0) + (s * q);
}

const Vector2 Segment::NearestVertex(const Vector2 &p) const
{
	Precision_t dist = std::numeric_limits<Precision_t>::infinity();
	Vector2 v;

	for (unsigned i = 0; i < GetPointCount(); i++)
	{
		Precision_t temp = p.GetDistance(GetPoint(i));

		if (temp < dist)
		{
			dist = temp;
			v = GetPoint(i);
		}
	}

	return v;
}

const bool Segment::IsPerpendicular(const Segment &s) const
{
	const Precision_t s1 = s.GetSlope();
	const Precision_t s2 = GetSlope();
	const Precision_t max = std::numeric_limits<Precision_t>::infinity();

	if ((AreEqual(s1, 0) && s2 == max) || (s1 == max && AreEqual(s2, 0)))
		return true;

	else
	{
		return AreEqual(s.GetSlope() * GetSlope(), -1);
	}
}

const bool Segment::IsParallel(const Segment &s) const
{
	return AreEqual(s.GetSlope(), GetSlope());
}

const Projection Segment::Project(const Axis &a) const
{
	const Precision_t dot0 = a.Dot(GetPoint(0));
	const Precision_t dot1 = a.Dot(GetPoint(1));

	return Projection(std::min(dot0, dot1), std::max(dot0, dot1));
}

const bool Segment::Contains(const Vector2 &p) const
{
	const Vector2 ba = (GetPoint(1) - GetPoint(0));
	const Vector2 ca = p - GetPoint(0);

	const Precision_t cross = ba.Cross(ca);
	const Precision_t dot = ba.Dot(ca);

	return (AreEqual(cross, 0) && dot >= 0 && dot <= (GetLength() * GetLength()));
}

const bool Segment::Contains(const Shape &s) const
{
	return s.IsInside(*this);
}

const bool Segment::Contains(const Segment &s) const
{
	if (s.GetLength() > GetLength())
		return false;

	else
		return (Contains(s.GetPoint(0)) && Contains(s.GetPoint(1)));
}

const bool Segment::Contains(const Circle &c) const
{
	return false;
}

const bool Segment::Contains(const Polygon &p) const
{
	return false;
}

const bool Segment::IsInside(const Shape &s) const
{
	return s.Contains(*this);
}

const bool Segment::IsInside(const Segment &s) const
{
	return s.Contains(*this);
}

const bool Segment::IsInside(const Circle &c) const
{
	return c.Contains(*this);
}

const bool Segment::IsInside(const Polygon &p) const
{
	return p.Contains(*this);
}

const bool Segment::Overlaps(const Shape &s) const
{
	return s.Overlaps(*this);
}

const bool Segment::Overlaps(const Segment &s) const
{

	if (IsParallel(s))
		return (Contains(s.GetPoint(0)) || Contains(s.GetPoint(1)));

	else
		return (GetIntersects(s).size() > 0);
}

const bool Segment::Overlaps(const Circle &c) const
{
	return c.Overlaps(*this);
}

const bool Segment::Overlaps(const Polygon &p) const
{
	return p.Overlaps(*this);
}

const std::vector<Vector2> Segment::GetIntersects(const Shape &s) const
{
	return s.GetIntersects(*this);
}

const std::vector<Vector2> Segment::GetIntersects(const Segment &s) const
{
	const Precision_t x1 = GetPoint(0).x;
	const Precision_t y1 = GetPoint(0).y;

	const Precision_t x2 = GetPoint(1).x;
	const Precision_t y2 = GetPoint(1).y;

	const Precision_t x3 = s.GetPoint(0).x;
	const Precision_t y3 = s.GetPoint(0).y;

	const Precision_t x4 = s.GetPoint(1).x;
	const Precision_t y4 = s.GetPoint(1).y;

	const Precision_t Bottom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	const Precision_t xTop = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
	const Precision_t yTop = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

	const Precision_t x = xTop / Bottom;
	const Precision_t y = yTop / Bottom;

	std::vector<Vector2> intersects(0);

	const Vector2 i = Vector2(x, y);

	if (Contains(i) && s.Contains(i))
		intersects.push_back(i);

	return intersects;
}

const std::vector<Vector2> Segment::GetIntersects(const Circle &c) const
{
	return c.GetIntersects(*this);
}

const std::vector<Vector2> Segment::GetIntersects(const Polygon &p) const
{
	return p.GetIntersects(*this);
}

const Vector2 Segment::GetDisplacement(const Shape &s) const
{
	return -s.GetDisplacement(*this);
}

const Vector2 Segment::GetDisplacement(const Segment &s) const
{
	if (!Overlaps(s))
		return Vector2(0, 0);

	else
	{
		AxesVec axes(2);
		axes[0] = GetAxis();
		axes[1] = s.GetAxis();

		return CalcDisplacement(axes, *this, s);
	}
}

const Vector2 Segment::GetDisplacement(const Circle &c) const
{
	return -c.GetDisplacement(*this);
}

const Vector2 Segment::GetDisplacement(const Polygon &p) const
{
	return -p.GetDisplacement(*this);
}

const Collision Segment::GetCollision(const Shape &s) const
{
	return -s.GetCollision(*this);
}

const Collision Segment::GetCollision(const Segment &s) const
{
	return Collision(Overlaps(s), GetIntersects(s), Contains(s), s.Contains(*this), GetDisplacement(s));
}

const Collision Segment::GetCollision(const Circle &c) const
{
	return -c.GetCollision(*this);
}

const Collision Segment::GetCollision(const Polygon &p) const
{
	return -p.GetCollision(*this);
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
	_axis = edge.Perpendicular().Normalize();
}

void Segment::Transform(const Transformation &t)
{
	ShapeImpl::Transform(t);
	ReCalc();
}
}
