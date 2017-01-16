#include "projection.hpp"
#include "collision.hpp"
#include "polygon.hpp"
#include "segment.hpp"
#include "circle.hpp"

#include <limits>
#include <algorithm>

Polygon::Polygon() : ShapeImpl(), _side(0)
{
}

const Projection Polygon::Project(const Shape &s, const Axis &a) const
{
	return s.Project(a);
}

const AxesVec& Polygon::GetAxes() const
{
	return _axes;
}

const std::vector<Segment>& Polygon::GetSides() const
{
	return _side;
}

const Vector2 Polygon::NearestVertex(const Vector2 &p) const
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

void Polygon::ReCalc()
{
	Precision_t x = 0;
	Precision_t y = 0;

	_axes.clear();
	_side.clear();

	for (unsigned i = 0; i < GetPointCount(); i++)
	{
		x += _points[i].x;
		y += _points[i].y;

		const Vector2 p1 = GetPoint(i);
		const Vector2 p2 =  GetPoint(i + 1 == GetPointCount() ? 0 : i + 1);

		const Segment l(p1, p2);

		bool parallel = false;

		for (auto && ln : _side)
		{
			if (l.IsParallel(ln))
			{
				parallel = true;
				break;
			}
		}

		_side.push_back(l);

		if (!parallel)
		{
			const Vector2 edge = p1 - p2;
			const Axis normal = edge.Perpendicular().Normalize();
			_axes.push_back(normal);
		}
	}

	_center = Vector2(x / GetPointCount(), y / GetPointCount());
}

const Projection Polygon::Project(const Axis &a) const
{
	Precision_t min = a.Dot(GetPoint(0));
	Precision_t max = min;

	for (unsigned i = 1; i < GetPointCount(); i++)
	{
		Precision_t prj = a.Dot(GetPoint(i));

		if (prj < min)
			min = prj;

		else if (prj > max)
			max = prj;
	}

	return Projection(min, max);
}

const bool Polygon::TriangleContains(const Vector2 &p, const Vector2 &a, const Vector2 &b, const Vector2 &c) const
{
	// Compute vectors
	Vector2 v0 = c - a;
	Vector2 v1 = b - a;
	Vector2 v2 = p - a;

	// Compute dot products
	Precision_t dot00 = v0.Dot(v0);
	Precision_t dot01 = v0.Dot(v1);
	Precision_t dot02 = v0.Dot(v2);
	Precision_t dot11 = v1.Dot(v1);
	Precision_t dot12 = v1.Dot(v2);

	// Compute barycentric coordinates
	Precision_t invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	Precision_t u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	Precision_t v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	return (u >= 0) && (v >= 0) && (u + v <= 1);
}


const bool Polygon::Contains(const Vector2 &v) const
{
	if (GetPointCount() == 3)
		return TriangleContains(v, GetPoint(0), GetPoint(1), GetPoint(2));

	else
	{
		for (unsigned i = 0; i < GetPointCount(); i++)
		{
			int c;

			if (i != GetPointCount() - 1)
				c = i + 1;

			else
				c = 0;

			if (TriangleContains(v, GetPoint(i), GetCenter(), GetPoint(c)))
				return true;
		}
	}

	return false;
}

const bool Polygon::Contains(const Shape &s) const
{
	return s.IsInside(*this);
}

const bool Polygon::Contains(const Segment &s) const
{
	return (Contains(s.GetPoint(0)) && Contains(s.GetPoint(1)));
}

const bool Polygon::Contains(const Circle &c) const
{
	const Vector2 center = c.GetCenter();

	if (!Contains(center))
		return false;

	for(auto && s : GetSides())
	{
		const Precision_t dist = s.DistancePoint(center);

		if (c.GetRadius() > dist)
			return false;
	}

	return true;

}

const bool Polygon::Contains(const Polygon &p) const
{
	for (unsigned v = 0; v < p.GetPointCount(); v++)
	{
		if (!Contains(p.GetPoint(v)))
			return false;
	}

	return true;
}

const bool Polygon::IsInside(const Shape &s) const
{
	return s.Contains(*this);
}

const bool Polygon::IsInside(const Segment &s) const
{
	return false;
}

const bool Polygon::IsInside(const Circle &c) const
{
	return c.Contains(*this);
}

const bool Polygon::IsInside(const Polygon &p) const
{
	return p.Contains(*this);
}

const bool Polygon::Overlaps(const Shape &s) const
{
	return s.Overlaps(*this);
}

const bool Polygon::Overlaps(const Segment &s) const
{
	auto axes = GetAxes();
	axes.push_back(s.GetAxis());

	return (CalcDisplacement(axes, *this, s) != Vector2(0, 0));
}

const bool Polygon::Overlaps(const Circle &c) const
{
	auto axes = GetAxes();
	axes.push_back((NearestVertex(c.GetCenter()) - c.GetCenter()).Normalize());

	return (CalcDisplacement(axes, *this, c) != Vector2(0, 0));
}

const bool Polygon::Overlaps(const Polygon &p) const
{
	const AxesVec &A = GetAxes();
	const AxesVec &B = p.GetAxes();

	AxesVec axes;

	axes.reserve(A.size() + B.size());
	axes.insert(axes.end(), A.begin(), A.end());
	axes.insert(axes.end(), B.begin(), B.end());

	return (CalcDisplacement(axes, *this, p) != Vector2(0, 0));
}

const std::vector<Vector2> Polygon::GetIntersects(const Shape &s) const
{
	return s.GetIntersects(*this);
}

const std::vector<Vector2> Polygon::GetIntersects(const Segment &s) const
{
	std::vector<Vector2> intersects(0);

	for (auto && side : GetSides())
	{
		auto vec = s.GetIntersects(side);

		if (vec.size() > 0)
		{
			auto it = std::find(std::begin(intersects), std::end(intersects), vec[0]);

			if (it == std::end(intersects))
				intersects.push_back(vec[0]);
		}
	}

	return intersects;
}

const std::vector<Vector2> Polygon::GetIntersects(const Circle &c) const
{
	std::vector<Vector2> intersections(0);

	std::vector<Segment> sides;

	for (auto && side : GetSides())
	{
		const Segment seg(side.GetPoint(0), side.GetPoint(1));

		const std::vector<Vector2> intercepts = c.GetIntersects(seg);

		for (auto && pt : intercepts)
		{
			auto it = std::find(std::begin(intersections), std::end(intersections), pt);

			if (it == std::end(intersections))
				intersections.push_back(pt);
		}
	}

	return intersections;
}

const std::vector<Vector2> Polygon::GetIntersects(const Polygon &p) const
{
	std::vector<Vector2> intersects(0);

	std::vector<Segment> sidesA;
	std::vector<Segment> sidesB;

	for (auto s : GetSides())
	{
		Segment sT(s.GetPoint(0), s.GetPoint(1));
		sidesA.push_back(sT);
	}

	for (auto s : p.GetSides())
	{
		Segment sT(s.GetPoint(0), s.GetPoint(1));
		sidesB.push_back(sT);
	}

	for (auto sA : sidesA)
	{
		for (auto sB : sidesB)
		{
			auto i = sA.GetIntersects(sB);

			if (i.size() > 0)
			{
				auto it = std::find(std::begin(intersects), std::end(intersects), i[0]);

				if (it == std::end(intersects))
					intersects.push_back(i[0]);
			}
		}
	}

	return intersects;
}

const Vector2 Polygon::GetDisplacement(const Shape &s) const
{
	return -s.GetDisplacement(*this);
}

const Vector2 Polygon::GetDisplacement(const Segment &s) const
{
	auto axes = GetAxes();
	axes.push_back(s.GetAxis());

	return CalcDisplacement(axes, *this, s);
}

const Vector2 Polygon::GetDisplacement(const Circle &c) const
{
	auto axes = GetAxes();
	axes.push_back((NearestVertex(c.GetCenter()) - c.GetCenter()).Normalize());

	return CalcDisplacement(axes, *this, c);
}

const Vector2 Polygon::GetDisplacement(const Polygon &p) const
{
	const AxesVec &A = GetAxes();
	const AxesVec &B = p.GetAxes();

	AxesVec axes;
	axes.reserve(A.size() + B.size());
	axes.insert(axes.end(), A.begin(), A.end());
	axes.insert(axes.end(), B.begin(), B.end());

	return CalcDisplacement(axes, *this, p);
}

const Collision Polygon::GetCollision(const Shape &s) const
{
	return -s.GetCollision(*this);
}

const Collision Polygon::GetCollision(const Segment &s) const
{
	// Check if polygon contains segment
	bool contains = false;

	// Segments cannot contain polygons
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	auto axes = GetAxes();
	axes.push_back(s.GetAxis());

	// Displacement is the vector to be applied to segment "s"
	// in order to seperate it from the circle
	const Vector2 displacement = CalcDisplacement(axes, *this, s);

	bool doesOverlap = (displacement != Vector2(0, 0));

	if (doesOverlap)
	{
		contains = Contains(s);
		intersects = GetIntersects(s);
	}

	return Collision(doesOverlap, intersects, contains, contained, displacement);
}

const Collision Polygon::GetCollision(const Circle &c) const
{
	// Determine if this polygon contains
	// the circle "c"
	bool contains = false;

	// Determine if the circle "c"
	// contains this polygon
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	const Axis ax = (NearestVertex(c.GetCenter()) - (c.GetCenter())).Normalize();

	auto axes = GetAxes();
	axes.push_back(ax);

	// Displacement is the vector to be applied to segment "s"
	// in order to seperate it from the circle
	const Vector2 displacement = CalcDisplacement(axes, *this, c);

	bool doesOverlap = (displacement != Vector2(0, 0));

	if (doesOverlap)
	{
		contains = Contains(c);
		contained = c.Contains(*this);
		intersects = GetIntersects(c);
	}

	return Collision(doesOverlap, intersects, contains, contained, displacement);
}

const Collision Polygon::GetCollision(const Polygon &p) const
{
	// Check if this contains p
	bool contains = false;

	// Check if p contains this
	bool contained = false;

	// Intersection points
	std::vector<Vector2> intersects(0);

	const AxesVec &A = GetAxes();
	const AxesVec &B = p.GetAxes();

	AxesVec axes;
	axes.reserve(A.size() + B.size());
	axes.insert(axes.end(), A.begin(), A.end());
	axes.insert(axes.end(), B.begin(), B.end());

	// Displacement is the vector to be applied to polygo "p"
	// in order to seperate it from this
	const Vector2 displacement = CalcDisplacement(axes, *this, p);

	bool doesOverlap = (displacement != Vector2(0, 0));

	if (doesOverlap)
	{
		contains = Contains(p);
		contained = p.Contains(*this);
		intersects = GetIntersects(p);
	}

	return Collision(doesOverlap, intersects, contains, contained, displacement);
}

void Polygon::Transform(const Transformation &t)
{
	ShapeImpl::Transform(t);
	ReCalc();
}
