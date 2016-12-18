#include "shape.hpp"
#include "projection.hpp"
#include "collision.hpp"

#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

Shape::Shape() : _rotation(0)
{
	//_color = sf::Color::White;
}

void Shape::SetPos(const Vector2& p)
{
	_pos = p;
}

const Vector2& Shape::GetPos() const
{
	return _pos;
}

void Shape::Move(const Vector2 &o)
{
	_pos += o;
}

const Precision_t& Shape::GetRotation() const
{
	return _rotation;
}

void Shape::Rotate(const Precision_t& a)
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

void Shape::SetRotation(const Precision_t& a)
{
	Rotate(a - _rotation);
}

const Vector2& Shape::GetCenter() const
{
	return _center;
}

void Shape::SetPointCount(const unsigned &c)
{
	_points.resize(c);
}

void Shape::SetPoint(const unsigned &i, const Vector2 &p)
{
	_points[i] = p;
}

const unsigned Shape::GetPointCount() const
{
	return _points.size();
}

const Vector2& Shape::GetPoint(const unsigned &i) const
{
	return _points[i];
}

Vector2 const Shape::GetTransformedPoint(const unsigned &i) const
{
	return GetPoint(i) + GetPos();
}

const std::vector<Vector2>& Shape::GetPoints() const
{
	return _points;
}

const Projection Shape::Project(const Axis &a) const
{
	return Projection(0, 0);
}

const bool Shape::Contains(const Vector2 &v) const
{
	return false;
}

const bool Shape::Contains(const Segment &s) const
{
	return false;
}

const bool Shape::Contains(const Circle &c) const
{
	return false;
}

const bool Shape::Contains(const Polygon &p) const
{
	return false;
}

const bool Shape::Intersects(const Segment &s) const
{
	return false;
}

const bool Shape::Intersects(const Circle &c) const
{
	return false;
}

const bool Shape::Intersects(const Polygon &p) const
{
	return false;
}

const std::vector<Vector2> Shape::GetIntersections(const Segment &s) const
{
	return std::vector<Vector2>(0);
}

const std::vector<Vector2> Shape::GetIntersections(const Circle &c) const
{
	return std::vector<Vector2>(0);
}

const std::vector<Vector2> Shape::GetIntersections(const Polygon &p) const
{
	return std::vector<Vector2>(0);
}

const Vector2 Shape::GetTranslation(const Segment &s) const
{
	return Vector2(0, 0);
}

const Vector2 Shape::GetTranslation(const Circle &c) const
{
	return Vector2(0, 0);
}

const Vector2 Shape::GetTranslation(const Polygon &p) const
{
	return Vector2(0, 0);
}

const Collision Shape::GetCollision(const Segment &s) const
{
	return Collision(false, std::vector<Vector2>(0), false, false, Vector2(0, 0));
}

const Collision Shape::GetCollision(const Circle &c) const
{
	return Collision(false, std::vector<Vector2>(0), false, false, Vector2(0, 0));
}

const Collision Shape::GetCollision(const Polygon &p) const
{
	return Collision(false, std::vector<Vector2>(0), false, false, Vector2(0, 0));
}
