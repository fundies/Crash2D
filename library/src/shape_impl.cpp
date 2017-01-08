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

ShapeImpl::ShapeImpl() :  _rotation(0)
{
}


ShapeImpl::ShapeImpl(const Vector2 c) : _center(c)
{
}

void ShapeImpl::SetPos(const Vector2& p)
{
	_pos = p;
}

const Vector2& ShapeImpl::GetPos() const
{
	return _pos;
}

void ShapeImpl::Move(const Vector2 &o)
{
	_pos += o;
}

const Precision_t& ShapeImpl::GetRotation() const
{
	return _rotation;
}

void ShapeImpl::Rotate(const Precision_t& a)
{
	_rotation += a;

	_rotation = std::fmod(_rotation, 360.0);

	if (_rotation < 0)
		_rotation += 360;

	Precision_t radians = (a * M_PI ) / 180;
	Vector2 o = GetCenter();

	Precision_t s = std::sin(radians);
	Precision_t c = std::cos(radians);

	for (unsigned v = 0; v < GetPointCount(); ++v)
	{
		Vector2 p = GetPoint(v);

		p -= o;

		Precision_t x = p.x * c + p.y * s;
		Precision_t y = -p.x * s + p.y * c;

		p = Vector2(x, y);

		p += o;

		SetPoint(v, p);
	}

	//ReCalc();
}

void ShapeImpl::SetRotation(const Precision_t& a)
{
	Rotate(a - _rotation);
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

Vector2 const ShapeImpl::GetTransformedPoint(const unsigned &i) const
{
	return GetPoint(i) + GetPos();
}

const std::vector<Vector2>& ShapeImpl::GetPoints() const
{
	return _points;
}
