#include <Crash2D/shape_impl.hpp>
#include <Crash2D/projection.hpp>
#include <Crash2D/collision.hpp>
#include <Crash2D/segment.hpp>
#include <Crash2D/circle.hpp>
#include <Crash2D/polygon.hpp>

#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

namespace Crash2D
{
ShapeImpl::ShapeImpl()
{
}


ShapeImpl::ShapeImpl(const Vector2 c) : _center(c)
{
}


const Vector2& ShapeImpl::GetCenter() const
{
	return _center;
}

void ShapeImpl::SetPointCount(const unsigned &c)
{
	_points.resize(c);
}

void ShapeImpl::SetPoint(const unsigned &i, const Vector2 &p)
{
	_points[i] = p;
}

const unsigned ShapeImpl::GetPointCount() const
{
	return _points.size();
}

const Vector2& ShapeImpl::GetPoint(const unsigned &i) const
{
	return _points[i];
}

const std::vector<Vector2>& ShapeImpl::GetPoints() const
{
	return _points;
}

const Vector2 ShapeImpl::CalcDisplacement(const AxesVec &axes, const Shape &a, const Shape &b) const
{
	Vector2 displacement;
	Precision_t Overlap = std::numeric_limits<Precision_t>::infinity();
	Axis smallest;

	for (auto && axis : axes)
	{
		const Projection pA = b.Project(axis);
		const Projection pB = a.Project(axis);

		// No Collision
		if (!pA.IsOverlap(pB))
			return Vector2(0, 0);

		else
		{
			const Precision_t o = pA.GetOverlap(pB);

			if (std::abs(o) < std::abs(Overlap))
			{
				Overlap = o;
				smallest = axis;
			}
		}

	}

	/*if (Overlap > 0)
		Overlap++;

	else
		Overlap--;*/

	displacement = smallest * Overlap;

	return displacement;
}

void ShapeImpl::Transform(const Transformation &t)
{
	for (unsigned i = 0; i < GetPointCount(); ++i)
	{
		Vector2 pt = GetPoint(i);

		// Scale
		pt -= GetCenter();
		pt *= t.GetScale();
		pt += GetCenter();

		// Rotate
		const Precision_t radians = (t.GetRotation() * M_PI ) / 180;
		const Precision_t s = std::sin(radians);
		const Precision_t c = std::cos(radians);

		Vector2 p = pt - t.GetPivot();

		const Precision_t nx = (p.x * c) - (p.y * s);
		const Precision_t ny = (p.x * s) + (p.y * c);

		p = Vector2(nx, ny) + t.GetPivot();

		// Translate
		p += t.GetTranslation();

		SetPoint(i, p);
	}
}

void ShapeImpl::ReCalc()
{
}
}
