#include "shape.hpp"
#include "transform.hpp"

#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

Shape::Shape()
{
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

Vector2 const Shape::GetTransformedPoint(const unsigned &i, const Transform &t) const
{
	Vector2 p = GetPoint(i);

	// Scale
	p *= t.GetScale();

	// Rotate
	Precision_t radians = (t.GetRotation() * M_PI ) / 180;

	Precision_t s = std::sin(radians);
	Precision_t c = std::cos(radians);

	p -= GetTransformedCenter(t);

	Precision_t x = p.x * c + p.y * s;
	Precision_t y = -p.x * s + p.y * c;
	p = Vector2(x, y);

	p += GetTransformedCenter(t);

	//Translate
	p += t.GetTranslation();

	return p;
}

Vector2 const Shape::GetTransformedCenter(const Transform &t) const
{
	return GetCenter() + t.GetTranslation();
}

const std::vector<Vector2>& Shape::GetPoints() const
{
	return _points;
}
