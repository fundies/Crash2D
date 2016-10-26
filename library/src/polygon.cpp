#include "projection.hpp"
#include "polygon.hpp"
#include "segment.hpp"
#include "circle.hpp"
#include "transform.hpp"


#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>

Polygon::Polygon() : Shape(), _side(0)
{
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
			const Axis normal = edge.Perpendicular().Normal();
			_axes.push_back(normal);
		}
	}

	_center = Vector2(x / GetPointCount(), y / GetPointCount());
}

const Projection Polygon::Project(const Axis &a, const Transform &t) const
{
	Precision_t min = a.Dot(GetTransformedPoint(0, t));
	Precision_t max = min;

	for (unsigned i = 1; i < GetPointCount(); i++)
	{
		Precision_t prj = a.Dot(GetTransformedPoint(i, t));

		if (prj < min)
		{
			min = prj;
		}

		else if (prj > max)
		{
			max = prj;
		}
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


const bool Polygon::Contains(const Vector2 &v, const Transform &t) const
{
	if (GetPointCount() == 3)
		return TriangleContains(v, GetTransformedPoint(0, t), GetTransformedPoint(1, t), GetTransformedPoint(2, t));

	else
	{
		for (unsigned i = 0; i < GetPointCount(); i++)
		{
			int c;

			if (i != GetPointCount() - 1)
				c = i + 1;

			else
				c = 0;

			if (TriangleContains(v, GetTransformedPoint(i, t), GetTransformedCenter(t), GetTransformedPoint(c, t)))
				return true;
		}
	}

	return false;
}

const bool Polygon::Contains(const Polygon &p, const Transform &t1, const Transform &t2) const
{
	for (unsigned v = 0; v < p.GetPointCount(); v++)
	{
		if (!Contains(p.GetTransformedPoint(v, t2), t1))
			return false;
	}

	return true;
}

const bool Polygon::Contains(const Circle &c, const Transform &t1, const Transform &t2) const
{
	const Vector2 center = c.GetTransformedCenter(t2);

	if (!Contains(center, t1))
		return false;

	for(auto && s : GetSides())
	{
		const Segment l(s.GetTransformedPoint(0, t1), s.GetTransformedPoint(1, t1));
		const Precision_t dist = l.DistancePoint(center, t2);

		if (dist <= c.GetRadius())
			return false;
	}

	return true;
}


const Collision Polygon::GetCollision(const Polygon &p, const Transform &t1, const Transform &t2) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;
	Vector2 translation;

	AxesVec axes(GetAxesCount() + p.GetAxesCount());

	for (unsigned i = 0; i < GetAxesCount(); ++i)
	{
		axes[i] = GetTransformedAxis(i, t1);
	}

	for (unsigned i = GetAxesCount(); i < GetAxesCount() + p.GetAxesCount(); ++i)
	{
		axes[i] = p.GetTransformedAxis(i, t2);
	}

	bool contained = false;

	for (auto && axis : axes)
	{
		Projection pA = Project(axis, t1);
		Projection pB = p.Project(axis, t2);

		if (!pA.IsOverlap(pB))
		{
			return Collision(translation, false, false);
		}

		else
		{
			Precision_t o = pA.GetOverlap(pB);

			if (Contains(p, t1, t2))
			{
				contained = true;

				Precision_t mins = std::abs(pA.x - pB.x);
				Precision_t maxs = std::abs(pA.y - pB.y);

				if (mins < maxs)
					o += mins;

				else
					o += maxs;
			}

			if (o < Overlap)
			{
				Overlap = o;
				smallest = axis;
			}
		}
	}

	translation = smallest * (Overlap + 1);
	Vector2 distance = p.GetTransformedCenter(t2) - GetTransformedCenter(t1);

	if (translation.Dot(distance) < 0)
		translation = -translation;

	return Collision(translation, true, contained);
}

const Collision Polygon::GetCollision(const Circle &c, const Transform &t1, const Transform &t2) const
{
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();// really large value;
	Axis smallest;

	Vector2 a = NearestVertex(c.GetTransformedCenter(t2), t1);
	Vector2 b = GetTransformedCenter(t1);
	Axis ax = a - b;
	ax = ax.Perpendicular().Normal();


	AxesVec axes = GetAxes();
	axes.push_back(ax);

	bool contained = false;
	Vector2 translation;

	for (auto && axis : axes)
	{
		const Projection pA = Project(axis, t1);
		const Projection pB = c.Project(axis, t2);

		if (!pA.IsOverlap(pB))
		{
			return Collision(translation, false, false);
		}

		else
		{
			Precision_t o = pA.GetOverlap(pB);

			contained = Contains(c, t1, t2);

			if (contained)
			{
				Precision_t mins = std::abs(pA.x - pB.x);
				Precision_t maxs = std::abs(pA.y - pB.y);

				if (mins < maxs)
					o += mins;

				else
					o += maxs;
			}

			if (o < Overlap)
			{
				Overlap = o;
				smallest = axis;
			}
		}
	}

	translation = smallest * (Overlap + 1);
	//Vector2 distance = a - b;
	Vector2 distance = c.GetTransformedCenter(t2) - GetTransformedCenter(t1);

	if (translation.Dot(distance) < 0)
		translation = -translation;

	return Collision(translation, true, contained);
}

const AxesVec& Polygon::GetAxes() const
{
	return _axes;
}

const Vector2 Polygon::NearestVertex(const Vector2 &p, const Transform &t) const
{
	Precision_t dist = std::numeric_limits<Precision_t>::infinity();
	Vector2 v;

	for (unsigned i = 0; i < GetPointCount(); i++)
	{
		Precision_t temp = p.GetDistance(GetTransformedPoint(i, t));

		if (temp < dist)
		{
			dist = temp;
			v = GetPoint(i);
		}
	}

	return v;
}

const std::vector<Segment>& Polygon::GetSides() const
{
	return _side;
}

const Axis Polygon::GetTransformedAxis(const unsigned i, const Transform &t) const
{
	Axis a = _axes[i];

	// Scale
	//a *= t.GetScale();

	// Rotate
	Precision_t radians = (t.GetRotation() * M_PI ) / 180;

	Precision_t s = std::sin(radians);
	Precision_t c = std::cos(radians);

	a -= GetTransformedCenter(t);

	Precision_t x = a.x * c + a.y * s;
	Precision_t y = -a.x * s + a.y * c;
	a = Vector2(x, y);

	a += GetTransformedCenter(t);

	//Translate
	//a += t.GetTranslation();

	return a;
}

const unsigned Polygon::GetAxesCount() const
{
	return _axes.size();
}
