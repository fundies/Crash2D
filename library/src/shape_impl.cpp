#include "shape_impl.hpp"
#include "projection.hpp"
#include "collision.hpp"
#include "segment.hpp"
#include "circle.hpp"
#include "polygon.hpp"

#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

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

	if (Overlap > 0)
		Overlap++;

	else
		Overlap--;

	displacement = smallest * Overlap;

	return displacement;
}

void ShapeImpl::ReCalc()
{
}
