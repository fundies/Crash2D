#include "projection.hpp"
#include "segment.hpp"
#include "circle.hpp"
#include "polygon.hpp"
#include "collision.hpp"

#include <limits>
#include <cmath>

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

const bool Segment::Overlaps(const Segment &s) const
{
	if (IsParallel(s))
		return (Contains(s.GetTransformedPoint(0)) || Contains(s.GetTransformedPoint(1)));

	else
		return (GetIntersects(s).size() > 0);
}

const bool Segment::Overlaps(const Circle &c) const
{
	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = (NearestVertex(c.GetCenter() + c.GetPos()) - c.GetCenter() + c.GetPos()).Normalize();

	return (CalcDisplacement(axes, *this, c) != Vector2(0, 0));
}

const bool Segment::Overlaps(const Polygon &p) const
{
	auto axes = p.GetAxes();
	axes.push_back(GetAxis());

	return (CalcDisplacement(axes, *this, p) != Vector2(0, 0));
}

const std::vector<Vector2> Segment::GetIntersects(const Segment &s) const
{
	const Precision_t x1 = GetTransformedPoint(0).x;
	const Precision_t y1 = GetTransformedPoint(0).y;

	const Precision_t x2 = GetTransformedPoint(1).x;
	const Precision_t y2 = GetTransformedPoint(1).y;

	const Precision_t x3 = s.GetTransformedPoint(0).x;
	const Precision_t y3 = s.GetTransformedPoint(0).y;

	const Precision_t x4 = s.GetTransformedPoint(1).x;
	const Precision_t y4 = s.GetTransformedPoint(1).y;

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

	ba = ba.Normalize() * disIntercept;

	Vector2 sol1 = midpt + ba;
	Vector2 sol2 = midpt - ba;

	if (Contains(sol1))
		intersections.push_back(sol1);

	if (Contains(sol2))
		intersections.push_back(sol2);

	return intersections;
}

const std::vector<Vector2> Segment::GetIntersects(const Polygon &p) const
{
	return p.GetIntersects(*this);
}

const Vector2 Segment::GetDisplacement(const Segment &s) const
{
	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = s.GetAxis();

	return CalcDisplacement(axes, *this, s);
}

const Vector2 Segment::GetDisplacement(const Circle &c) const
{
	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = (NearestVertex(c.GetCenter() + c.GetPos()) - c.GetCenter() + c.GetPos()).Normalize();

	return CalcDisplacement(axes, *this, c);
}

const Vector2 Segment::GetDisplacement(const Polygon &p) const
{
	auto axes = p.GetAxes();
	axes.push_back(GetAxis());

	return CalcDisplacement(axes, *this, p);
}

const Collision Segment::GetCollision(const Shape &s) const
{
	return -s.GetCollision(*this);
}

const Collision Segment::GetCollision(const Segment &s) const
{
	const Vector2 displacement = GetDisplacement(s);

	return Collision((displacement != Vector2(0, 0)), GetIntersects(s), Contains(s), s.Contains(*this), displacement);
}

const Collision Segment::GetCollision(const Circle &c) const
{
	bool doesOverlap = false;

	// Segments cannot contain circles
	bool contains = false;

	// Check if circle contains segment
	bool contained = c.Contains(*this);

	// Intersection points
	std::vector<Vector2> intersects(0);

	AxesVec axes(2);
	axes[0] = GetAxis();
	axes[1] = (NearestVertex(c.GetCenter() + c.GetPos()) - (c.GetCenter() + c.GetPos())).Normalize();

	// Displacement is the vector to be applied to segment "s"
	// in order to seperate it from the circle
	Vector2 displacement = CalcDisplacement(axes, *this, c);

	doesOverlap = (displacement != Vector2(0, 0));

	if (!contains)
		intersects = GetIntersects(c);

	return Collision(doesOverlap, intersects, contains, contained, displacement);
}

const Collision Segment::GetCollision(const Polygon &p) const
{
	// Check if segment contained inside polygon
	bool contained = false;

	//A segment cannot contain a polygon
	bool contains = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	auto axes = p.GetAxes();
	axes.push_back(GetAxis());

	const Vector2 displacement = CalcDisplacement(axes, *this, p);

	bool doesOverlap = (displacement != Vector2(0, 0));

	if (doesOverlap)
	{
		contained = p.Contains(*this);
		intersects = GetIntersects(p);
	}

	return Collision(doesOverlap, intersects, contains, contained, displacement);
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
